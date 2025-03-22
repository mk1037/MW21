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

#include "chooserwin.h"
#include "chooserarea.h"
#include "signalclient.h"
#include "midiclient.h"
#include <unistd.h>
#include <iostream>
#include <gtkmm.h>

extern SignalClient * global_sclient;

ChooserWin::ChooserWin(ChooserConfig* pconfig)
{
  chooserConfig = pconfig;
  signal_client_thread = nullptr;
  set_title("Chooser");
  set_border_width(5);
  set_default_size(AREA_WIDTH + 10, AREA_HEIGHT + 10);
  m_Dispatcher.connect(sigc::mem_fun(*this, &ChooserWin::on_notification_from_worker_thread));

  m_VBox = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
  this->add(*m_VBox);
  
  m_area = new ChooserArea();
  m_VBox->pack_start(*m_area);
  m_area->show();
  m_area->render();
  
  m_VBox->show();
}




ChooserWin::~ChooserWin()
{
  delete m_VBox;
  delete m_area;
  delete signalClient;
}


void ChooserWin::start_listen()
{
  client = new MidiClient(chooserConfig);
  client->open_client("Chooser");
  if(!client->get_client_success_info())
  {
    std::cout << "Couldn't open sequencer!" << std::endl;
  }

  client->new_port_read();
  if(client->get_port_read() < 0)
  {
    std::cout << "Couldn't open port read!" << std::endl;
  }


  signalClient = new SignalClient(client, chooserConfig->getChooserInstructionPath());
  global_sclient = signalClient;
  if (signal_client_thread)
  {
    std::cout << "Can't start a signal client thread while another one is running." << std::endl;
  }
  else
  {
    signal_client_thread = Glib::Threads::Thread::create(
      sigc::bind(sigc::mem_fun(signalClient, &SignalClient::listen), this));
  }
}


void ChooserWin::on_quit_button_clicked()
{
  signalClient->stop_work();
  hide();
}


void ChooserWin::notify()
{
  m_Dispatcher.emit();
}

void ChooserWin::on_notification_from_worker_thread()
{
  if (signal_client_thread && signalClient->has_stopped())
  {
    //Work is done.
    signal_client_thread->join();
    signal_client_thread = nullptr;
  }
//   update_widgets();
}


int ChooserWin::write_pid()
{
  Gio::init();
  try
  {
    pid_t pid = getpid();
    std::cout << "Will be writing pid " << pid << " to " << chooserConfig->getChooserPidPath() << std::endl;

    auto f = Gio::File::create_for_path(chooserConfig->getChooserPidPath());
    if(!f)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    Glib::RefPtr<Gio::FileOutputStream> stream;

    // If the file exists already then replace it.
    // Otherwise, create it:
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
