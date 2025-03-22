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

#include "timeoutclient.h"

TimeoutClient::TimeoutClient(unsigned int p_timeout)
{
  timeout = p_timeout;
}


void TimeoutClient::countdown(ModelineWin* caller)
{
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    m_has_stopped = false;
  } // The mutex is unlocked here by lock's destructor.

  Glib::usleep(1000 * timeout);
  
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_has_stopped = true;
  lock.release();
  caller->notify_timeout();
}

bool TimeoutClient::has_stopped() const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  return m_has_stopped;
}
