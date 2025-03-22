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

#ifndef MODELINE_MIDICLIENT_H
#define MODELINE_MIDICLIENT_H

#define BANKS_NUM 3

#define NOTE_CHAR_LEFT 61
#define NOTE_LEFT 63

#define NOTE_RIGHT_1 66
#define NOTE_RIGHT_2 68
#define NOTE_CHAR_RIGHT 70

#define NOTE_STOP_A 73
#define NOTE_STOP_B 75

#define NOTE_LOAD_A 78
#define NOTE_PLAY 80
#define NOTE_LOAD_B 82

#define NOTE_SEARCH 85
#define NOTE_OK 87

#define NOTE_BANK_1 90
#define NOTE_BANK_2 92
#define NOTE_BANK_3 94

#define NOTE_ARM    97
#define NOTE_DISARM 98

#define NOTE_A 60
#define NOTE_B 62
#define NOTE_C 64

#define NOTE_D 65
#define NOTE_E 67
#define NOTE_F 69
#define NOTE_G 71

#define NOTE_H 72
#define NOTE_I 74
#define NOTE_J 76

#define NOTE_K 77
#define NOTE_L 79
#define NOTE_M 81
#define NOTE_N 83

#define NOTE_O 84
#define NOTE_P 86
#define NOTE_R 88

#define NOTE_S 89
#define NOTE_T 91
#define NOTE_U 93
#define NOTE_W 95
#define NOTE_Z 96

#define ACTION_STOP_1        130
#define ACTION_STOP_2        131
#define ACTION_LOAD_1        132
#define ACTION_PLAY          133
#define ACTION_LOAD_2        134

#define ACTION_SET_FILE_1    135
#define ACTION_SET_FILE_2    136
#define ACTION_INFO_OK       137
#define ACTION_INFO_SEARCH   138
#define ACTION_INFO_CLEAR    139
#define ACTION_ARM           140
#define ACTION_DISARM        141


#define SUBSET1_CTRL         20
#define SUBSET2_CTRL         21
#define SUBSET3_CTRL         22
#define SUBSET4_CTRL         23
#define SUBSET5_CTRL         24
#define SUBSET6_CTRL         25
#define SUBSET7_CTRL         26
#define SUBSET8_CTRL         27


#include <alsa/asoundlib.h>
#include <gtkmm.h>
#include "modelinewin.h"
#include "modelineconfig.h"
#include "filesqueue.h"

class ModelineWin;

class MidiClient
{
  public:
    MidiClient();
    ~MidiClient();
    void configure(ModelineConfig * pconfig);
    void listen(ModelineWin * caller);
    void stop_work();
    bool has_stopped() const;
    void get_data(Glib::ustring* current_item_1, Glib::ustring* current_item_2,
                          Glib::ustring* prev_item_1, Glib::ustring* next_item_1,
                          int* p_action, int* p_theme_idx, int * p_character_pressed) const;
    void open_client();
    bool get_client_success_info();
    void new_port_write();
    int get_port();
//    void set_theme(unsigned int p_idx);
    int readBanks(Glib::ustring p_prefix);
  private:
    mutable Glib::Threads::Mutex m_Mutex;
    bool m_shall_stop;
    bool m_has_stopped;
    Glib::ustring m_message;
    snd_seq_t *r;
    int port_id;
    bool ok_pressed;
    bool search_pressed;

    int m_action;
    int m_character_pressed;
    int m_set_bank_theme;

    FilesQueue queue_a[BANKS_NUM];

    unsigned int cqueue_a;

    unsigned int control_channel;

    unsigned int m_color_theme;
    unsigned int m_keynum;
};

#endif // MODELINE_MIDICLIENT_H
