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

#include "signalclient.h"
#include "midiclient.h"
#include <iostream>
#include <signal.h>

SignalClient * global_sclient;

SignalClient::SignalClient(MidiClient * p_client, Glib::ustring p_instpath)
{
  m_instruction_path = p_instpath;
  mclient = p_client;
}

SignalClient::~SignalClient()
{
  std::cout << "Closing signal listener" << std::endl;
}

void SignalClient::open_client()
{
}


void SignalClient::stop_work()
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  std::cout << "Stopping signal client" << std::endl;
  m_shall_stop = true;
}

bool SignalClient::has_stopped() const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  return m_has_stopped;
}

// void SignalClient::get_data(bool* p_open) const
// {
//   Glib::Threads::Mutex::Lock lock(m_Mutex);
//   *p_open = open;
// }

void SignalClient::listen(ChooserWin * p_caller)
{
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    caller = p_caller;
    m_has_stopped = false;
  } // The mutex is unlocked here by lock's destructor.

   sigset_t mask, oldmask;

   sigemptyset(&mask);
   sigaddset(&mask, SIGUSR1);
   signal(SIGUSR1, wrapperOf_MemberFn);

   sigprocmask(SIG_BLOCK, &mask, &oldmask);
   while(1)
      sigsuspend (&oldmask);
   sigprocmask(SIG_UNBLOCK, &mask, NULL);

  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_shall_stop = false;
  m_has_stopped = true;
  lock.release();
//   caller->notify();
}

void wrapperOf_MemberFn(int p)
{
  global_sclient->mb_sighandler();
}


void SignalClient::mb_sighandler()
{
  //here open file and read instruction and switch
  Gio::init();
  auto f = Gio::File::create_for_path(m_instruction_path);

  try
  {
    auto file_stream = f->read();
    auto data_stream = Gio::DataInputStream::create(file_stream);

    std::string item, instruction;
    std::locale::global(std::locale(""));

    Glib::Threads::Mutex::Lock lock(m_Mutex);
    Glib::ustring t_instr;

    data_stream->read_line(instruction);
    data_stream->read_line(item);
    mclient->send(instruction, item);
    lock.release();
  }
  catch  (Glib::Error &err)
  {
    std::cerr << "Couldn't read file " << m_instruction_path << std::endl;
  }
}
