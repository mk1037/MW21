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

#ifndef DISPLAY_MIDICLIENT_H
#define DISPLAY_MIDICLIENT_H

#include <alsa/asoundlib.h>
#include <gtkmm.h>
#include "displaywin.h"


class MidiClient
{
  public:
    MidiClient( unsigned int p_channel, unsigned int p_note_geq,
      unsigned int p_note_lt, unsigned int p_vel_geq, unsigned int p_vel_lt,
      unsigned int p_ctrl_num_4fw, unsigned int p_ctrl_val_4fw,
      unsigned int p_ctrl_num_4bw, unsigned int p_ctrl_val_4bw,
      unsigned int p_note_read, unsigned int p_vel_read,
      unsigned int p_note_back, unsigned int p_vel_back,
      unsigned int p_note_theme_1, unsigned int p_vel_theme_1,
      unsigned int p_note_theme_2, unsigned int p_vel_theme_2,
      unsigned int p_note_theme_3, unsigned int p_vel_theme_3,
      unsigned int p_note_pckbd_enable, unsigned int p_note_pckbd_disable,
      unsigned int p_note_home, unsigned int p_vel_home,
      bool p_read_text );
    ~MidiClient();
    void listen(DisplayWin * caller);
    void stop_work();
    bool has_stopped() const;
    void get_data(bool *read_text, unsigned int *p_theme_id, bool *p_go_back, bool *p_increment, bool *p_4fw, bool *p_4bw, bool *p_home, unsigned int *p_pckbd_action) const;
    void open_client();
    bool get_client_success_info();
    void new_port_write();
    int get_port();
    void clear_read_flag();
    void set_theme(unsigned int p_idx);
  private:
    mutable Glib::Threads::Mutex m_Mutex;
    bool m_shall_stop;
    bool m_has_stopped;
    Glib::ustring m_message;
    snd_seq_t *r;
    int port_id;
    unsigned int channel;
    unsigned int note_geq;
    unsigned int note_lt;
    unsigned int vel_geq;
    unsigned int vel_lt;
    unsigned int ctrl_num_4fw;
    unsigned int ctrl_val_4fw;
    unsigned int ctrl_num_4bw;
    unsigned int ctrl_val_4bw;
    unsigned int note_read;
    unsigned int vel_read;
    unsigned int note_back;
    unsigned int vel_back;
    unsigned int note_theme_1;
    unsigned int vel_theme_1;
    unsigned int note_theme_2;
    unsigned int vel_theme_2;
    unsigned int note_theme_3;
    unsigned int vel_theme_3;
    unsigned int note_pckbd_enable;
    unsigned int note_pckbd_disable;
    unsigned int note_home;
    unsigned int vel_home;
    bool m_read_text;
    unsigned int m_color_theme;
    bool m_go_back;
    bool m_increment;
    bool m_home;
    unsigned int m_pckbd_action;
    bool m_4fw;
    bool m_4bw;
};

#endif // DISPLAY_MIDICLIENT_H
