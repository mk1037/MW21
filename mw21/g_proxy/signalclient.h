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

#ifndef PROXY_SIGNALCLIENT_H
#define PROXY_SIGNALCLIENT_H

#include <alsa/asoundlib.h>
#include <gtkmm.h>
#include "g_proxywin.h"


class SignalClient
{
  public:
    SignalClient(Glib::ustring p_instpath);
    ~SignalClient();
    void listen(GProxyWin * p_caller);
    void stop_work();
    bool has_stopped() const;
    void get_data(bool *p_open) const;
    void open_client();
    void mb_sighandler();
  private:
    GProxyWin * caller;
    mutable Glib::Threads::Mutex m_Mutex;
    bool m_shall_stop;
    bool m_has_stopped;
    Glib::ustring m_message;
    Glib::ustring m_instruction_path;
    bool open;
};

void wrapperOf_MemberFn(int p);



#endif // PROXY_SIGNALCLIENT_H
