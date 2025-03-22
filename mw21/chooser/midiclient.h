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

#ifndef CHOOSER_MIDICLIENT_H
#define CHOOSER_MIDICLIENT_H

#include <alsa/asoundlib.h>
#include <gtkmm.h>
#include "chooserwin.h"

class MidiClient
{
  public:
    MidiClient(ChooserConfig * p_pconfig);
    ~MidiClient();
    void send(Glib::ustring p_instruction, Glib::ustring p_item);
    void open_client(Glib::ustring p_name);
    bool get_client_success_info();
    void new_port_read();
    int get_port_read();
  private:
    snd_seq_t *r;
    int r_port_id;

    unsigned int textChannel;

    unsigned int noteRead;
    unsigned int velRead;

    unsigned int noteTheme1;
    unsigned int velTheme1;
    unsigned int noteTheme2;
    unsigned int velTheme2;
    unsigned int noteTheme3;
    unsigned int velTheme3;

    unsigned int noteHome;
    unsigned int velHome;

    unsigned int notePCKbdEnable;
    unsigned int notePCKbdDisable;

    Glib::ustring bank_1_pattern;
    Glib::RefPtr<Glib::Regex> bank_1_patternRegex;

    Glib::ustring bank_2_pattern;
    Glib::RefPtr<Glib::Regex> bank_2_patternRegex;

    Glib::ustring bank_3_pattern;
    Glib::RefPtr<Glib::Regex> bank_3_patternRegex;
};

#endif // CHOOSER_MIDICLIENT_H
