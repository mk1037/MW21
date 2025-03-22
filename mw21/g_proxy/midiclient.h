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

#ifndef PROXY_MIDICLIENT_H
#define PROXY_MIDICLIENT_H

#include <alsa/asoundlib.h>
#include <gtkmm.h>
#include "g_proxywin.h"

class MidiClient
{
  public:
    MidiClient(ProxyConfig * p_pconfig);
    ~MidiClient();
    void listen0(GProxyWin * caller);
    void listen2(GProxyWin * caller);
    void stop_work();
    bool has_stopped() const;
    //void get_data(bool *p_open) const;
    void open_client(Glib::ustring p_name);
    bool get_client_success_info();
    void new_port_write(Glib::ustring p_name);
    int get_port_write();
    void new_port_read(Glib::ustring p_name);
    int get_port_read();
    void set_open(bool p_open);
  private:
    bool is_trigger_note(unsigned int a);
    bool is_counted_note(unsigned int a);
    bool is_back_note(unsigned int a);
    void decrease();
    void increase();
    mutable Glib::Threads::Mutex m_Mutex;
    unsigned int pressed;
    bool m_shall_stop;
    bool m_has_stopped;
    Glib::ustring m_message;
    snd_seq_t *r;
    int r_port_id;
    int w_port_id;
    bool open;
    bool manual;
    unsigned int textChannel;
    unsigned int controlChannel;
    unsigned int noteGEQ;
    unsigned int noteLT;
    unsigned int velGEQ;
    unsigned int velLT;
    unsigned int noteBack;
    unsigned int velBack;
    unsigned int noteHome;
    unsigned int velHome;
};

#endif // DISPLAY_MIDICLIENT_H
