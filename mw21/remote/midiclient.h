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

#ifndef REMOTE_MIDICLIENT_H
#define REMOTE_MIDICLIENT_H

#include <alsa/asoundlib.h>
#include <gtkmm.h>
#include "remotewin.h"

class MidiClient
{
  public:
    MidiClient(RemoteConfig * p_pconfig);
    ~MidiClient();
    void send(Glib::ustring p_instruction);
    void open_client(Glib::ustring p_name);
    bool get_client_success_info();
    void new_port_read();
    int get_port_read();
  private:
    snd_seq_t *r;
    int r_port_id;

    unsigned int modelineControlChannel;

    unsigned int noteLoad;
    unsigned int notePlay;
    unsigned int noteStop;

};

#endif // REMOTE_MIDICLIENT_H
