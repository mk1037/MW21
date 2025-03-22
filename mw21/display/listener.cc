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

#include "listener.h"
#include "displaywin.h"
#include <sstream>

Listener::Listener() :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false),
  m_fraction_done(0.0),
  m_message()
{
}

void Listener::get_data(double* fraction_done, Glib::ustring* message) const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);

  if (fraction_done)
    *fraction_done = m_fraction_done;

  if (message)
    *message = m_message;
}

void Listener::stop_work()
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_shall_stop = true;
}

bool Listener::has_stopped() const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  return m_has_stopped;
}

void Listener::do_work(DisplayWin* caller)
{
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    m_has_stopped = false;
    m_fraction_done = 0.0;
    m_message = "";
  } // The mutex is unlocked here by lock's destructor.

  // Simulate a long calculation.
  for (int i = 0; ; ++i) // do until break
  {
    Glib::usleep(250000); // microseconds

    Glib::Threads::Mutex::Lock lock(m_Mutex);

    m_fraction_done += 0.01;

    if (i % 4 == 3)
    {
      std::ostringstream ostr;
      ostr << (m_fraction_done * 100.0) << "% done\n";
      m_message += ostr.str();
    }

    if (m_fraction_done >= 1.0)
    {
      m_message += "Finished";
      break;
    }
    if (m_shall_stop)
    {
      m_message += "Stopped";
      break;
    }
    lock.release();
    caller->notify();
  }

  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_shall_stop = false;
  m_has_stopped = true;
  lock.release();
  caller->notify();
}
