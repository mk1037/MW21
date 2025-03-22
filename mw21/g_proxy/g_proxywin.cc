/*
 * Copyright (C) 2017-2025 Marek Momot
 *
 * This file is part of MW21.
 *
 * MW21 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MW21 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MW21.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "g_proxywin.h"
#include "proxyarea.h"
#include "midiclient.h"
#include "signalclient.h"
#include <unistd.h>
#include <iostream>
#include <gtkmm.h>

extern SignalClient * global_sclient;

GProxyWin::GProxyWin(ProxyConfig* pconfig, int p_atype)
{
  proxyConfig = pconfig;
  m_atype = p_atype;
  client_thread = nullptr;
  client_thread2 = nullptr;
  set_title(pconfig->getProxyLabel());
  set_border_width(0);
  set_default_size(AREA_WIDTH, AREA_HEIGHT);
  m_open = true;
  m_Dispatcher.connect(sigc::mem_fun(*this, &GProxyWin::on_notification_from_worker_thread));
  m_Dispatcher2.connect(sigc::mem_fun(*this, &GProxyWin::on_notification_from_worker_thread2));

  m_VBox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
  this->add(*m_VBox);

  m_area = new ProxyArea(true);
  m_VBox->pack_start(*m_area);
  m_area->show();
  m_area->render();

  m_VBox->show();
}

GProxyWin::~GProxyWin()
{
  delete m_VBox;
  delete m_area;
  delete client;
}

void GProxyWin::update_widgets()
{
  //client->get_data(&m_open);
}

void GProxyWin::update_widgets2()
{
  client2->get_data(&m_open);
  client->set_open(m_open);

  m_VBox->remove(*m_area);
  delete m_area;

  m_area = new ProxyArea(m_open);
  m_VBox->pack_start(*m_area);
  m_area->render();
  m_area->show();

}

void GProxyWin::start_listen()
{
  //Create port and run listener
  client = new MidiClient(proxyConfig);
  client->open_client(proxyConfig->getProxyLabel());
  if(!client->get_client_success_info())
  {
    std::cout << "Couldn't open sequencer!" << std::endl;
  }
  client->new_port_write(proxyConfig->getProxyLabel());
  if(client->get_port_write() < 0)
  {
    std::cout << "Couldn't open port write!" << std::endl;
  }

  client->new_port_read(proxyConfig->getProxyLabel());
  if(client->get_port_read() < 0)
  {
    std::cout << "Couldn't open port read!" << std::endl;
  }

  if (client_thread)
  {
    std::cout << "Can't start a worker thread while another one is running." << std::endl;
  }
  else
  {
    // Start a new worker thread.
    if(m_atype == MAIN_PR)
      client_thread = Glib::Threads::Thread::create(
        sigc::bind(sigc::mem_fun(client, &MidiClient::listen0), this));
    else
      client_thread = Glib::Threads::Thread::create(
        sigc::bind(sigc::mem_fun(client, &MidiClient::listen2), this));
  }

  client2 = new SignalClient(proxyConfig->getInstructionPath());
  global_sclient = client2;
  if (client_thread2)
  {
    std::cout << "Can't start a worker thread 2 while another one is running." << std::endl;
  }
  else
  {
    // Start a new worker thread.
    client_thread2 = Glib::Threads::Thread::create(
      sigc::bind(sigc::mem_fun(client2, &SignalClient::listen), this));
  }
}

void GProxyWin::set_config(ProxyConfig *config)
{
  proxyConfig = config;
}

void GProxyWin::set_switch(bool p_value)
{
  m_open = p_value;
}


void GProxyWin::on_quit_button_clicked()
{
  client->stop_work();
  hide();
}


void GProxyWin::notify()
{
  m_Dispatcher.emit();
}

void GProxyWin::notify2()
{
  m_Dispatcher2.emit();
}

void GProxyWin::on_notification_from_worker_thread()
{
  if (client_thread && client->has_stopped())
  {
    // Work is done.
    client_thread->join();
    client_thread = nullptr;
    //update_start_stop_buttons();
  }
  update_widgets();
}



void GProxyWin::on_notification_from_worker_thread2()
{
  if (client_thread2 && client2->has_stopped())
  {
    // Work is done.
    client_thread2->join();
    client_thread2 = nullptr;
    //update_start_stop_buttons();
  }
  update_widgets2();
}

int GProxyWin::write_pid()
{
  Gio::init();
  try
  {
    pid_t pid = getpid();
    std::cout << "Will be writing pid " << pid << " to " << proxyConfig->getPidPath() << std::endl;

    auto f = Gio::File::create_for_path(proxyConfig->getPidPath());
    if(!f)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    Glib::RefPtr<Gio::FileOutputStream> stream;

    //If the file exists already then replace it.
    //Otherwise, create it:
    if(f->query_exists())
      stream = f->replace();
    else
      stream = f->create_file();
    if(!stream)
      std::cerr << "Gio::File::create_file() returned an empty RefPtr." << std::endl;

    char *mypid = NULL;
    if (asprintf(&mypid, "%jd", (intmax_t) pid) != -1)
    {
      const gsize bytes_read = stream->write(mypid);
      free(mypid); // cleanup when done.

      if(bytes_read)
        std::cout << "File contents written: " << getpid() << std::endl;
      else
        std::cerr << "Gio::InputStream::write() wrote 0 bytes." << std::endl;
    }
    const gsize bytes_read = stream->write("\n");
    if(bytes_read)
      std::cout << "File contents written: " << "<newline>" << std::endl;
    else
      std::cerr << "Gio::InputStream::write() wrote 0 bytes." << std::endl;
    stream->close();
    stream.reset(); //Stream can't be used after we have closed it.
    return 0;
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
    return 1;
  }
}
