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

#ifndef MODELINE_TIMEOUTCLIENT_H
#define MODELINE_TIMEOUTCLIENT_H

#include <gtkmm.h>
#include "modelinewin.h"

class ModelineWin;

class TimeoutClient
{
  public:
    TimeoutClient(unsigned int p_timeout);
    bool has_stopped() const;
    void countdown(ModelineWin * caller);
  private:
    mutable Glib::Threads::Mutex m_Mutex;
    bool m_has_stopped;
    unsigned int timeout;

};

#endif // MODELINE_TIMEOUTCLIENT_H
