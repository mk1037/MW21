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

#include "midiclient.h"
#include <iostream>

MidiClient::MidiClient( unsigned int p_channel, unsigned int p_note_geq,
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
    bool p_read_text ) :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false),
  m_message(),
  r(0),
  port_id(0),
  channel(p_channel),
  note_geq(p_note_geq),
  note_lt(p_note_lt),
  vel_geq(p_vel_geq),
  vel_lt(p_vel_lt),
  ctrl_num_4fw(p_ctrl_num_4fw),
  ctrl_val_4fw(p_ctrl_val_4fw),
  ctrl_num_4bw(p_ctrl_num_4bw),
  ctrl_val_4bw(p_ctrl_val_4bw),
  note_read(p_note_read),
  vel_read(p_vel_read),
  note_back(p_note_back),
  vel_back(p_vel_back),
  note_theme_1(p_note_theme_1),
  vel_theme_1(p_vel_theme_1),
  note_theme_2(p_note_theme_2),
  vel_theme_2(p_vel_theme_2),
  note_theme_3(p_note_theme_3),
  vel_theme_3(p_vel_theme_3),
  note_pckbd_enable(p_note_pckbd_enable),
  note_pckbd_disable(p_note_pckbd_disable),
  note_home(p_note_home),
  vel_home(p_vel_home),
  m_read_text(p_read_text)
{
  m_color_theme = 0;
  m_go_back = false;
  m_increment = true;
  m_home = false;
  m_pckbd_action = 0;
  m_4fw = 0;
  m_4bw = 0;
}

MidiClient::~MidiClient()
{
  snd_seq_close(r);
  std::cout << "Closing sequencer" << std::endl;
}

void MidiClient::open_client()
{
  port_id = -1;
  int err;
  err = snd_seq_open ( &r, "default", SND_SEQ_OPEN_DUPLEX, 0 );
  if ( err < 0 )
    return;
  snd_seq_set_client_name ( r, "MIDI_Display" );
}

void MidiClient::new_port_write()
{
  port_id = snd_seq_create_simple_port ( r, "Display_write",
                                       SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
                                       SND_SEQ_PORT_TYPE_MIDI_GENERIC );
}

int MidiClient::get_port()
{
  return port_id;
}

void MidiClient::get_data(bool *read_text, unsigned int *p_theme_id, bool *p_go_back, bool *p_increment, bool *p_4fw, bool *p_4bw, bool *p_home, unsigned int *p_pckbd_action) const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  *read_text = m_read_text;
  *p_theme_id = m_color_theme;
  *p_go_back = m_go_back;
  *p_increment = m_increment;
  *p_4fw = m_4fw;
  *p_4bw = m_4bw;
  *p_home = m_home;
  *p_pckbd_action = m_pckbd_action;
}

void MidiClient::stop_work()
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  std::cout << "Stopping listener" << std::endl;
  m_shall_stop = true;
}

bool MidiClient::has_stopped() const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  return m_has_stopped;
}

bool MidiClient::get_client_success_info()
{
  if(r) return true;
  else return false;
}

void MidiClient::clear_read_flag()
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
//  m_read_text;
}

void MidiClient::set_theme(unsigned int p_idx)
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_color_theme = p_idx;
}

void MidiClient::listen(DisplayWin * caller)
{
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    m_has_stopped = false;
    m_message = "";
  } // The mutex is unlocked here by lock's destructor.

  snd_seq_event_t *ev;

  while(snd_seq_event_input ( r, &ev ) >= 0 && !m_shall_stop)
  {
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note >= note_geq && ( ev->data ).note.note < note_lt &&
        ( ev->data ).note.velocity >= vel_geq && ( ev->data ).note.velocity < vel_lt )
    {
      //std::cout << "Received an event: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = true;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_read && ( ev->data ).note.velocity == vel_read )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = false;
      m_go_back = false;
      m_read_text = true;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_theme_1 && ( ev->data ).note.velocity == vel_theme_1 )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = false;
      m_color_theme = 0;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_theme_2 && ( ev->data ).note.velocity == vel_theme_2 )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = false;
      m_color_theme = 1;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_theme_3 && ( ev->data ).note.velocity == vel_theme_3 )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = false;
      m_color_theme = 2;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_back && ( ev->data ).note.velocity == vel_back )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = false;
      m_go_back = true;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_home && ( ev->data ).note.velocity == vel_home )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = true;
      m_increment = false;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_pckbd_enable && ( ev->data ).note.velocity > 0 )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = false;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 1;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.channel == channel &&
        ( ev->data ).note.note == note_pckbd_disable && ( ev->data ).note.velocity > 0 )
    {
      //std::cout << "Received an event second block: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      m_home = false;
      m_increment = false;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 2;
      m_4fw = false;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_CONTROLLER && (ev->data).control.channel == channel &&
        ( ev->data ).control.param == ctrl_num_4fw && (unsigned int)( ev->data ).control.value == ctrl_val_4fw )
    {
//       std::cout << "Received a controller: channel = " << (int)( ev->data ).control.channel
//         << " controller number = " << (int)( ev->data ).control.param << " value " << (int)( ev->data ).control.value << std::endl;
      m_home = false;
      m_increment = false;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = true;
      m_4bw = false;
      caller->notify();
    }
    if ( ev->type == SND_SEQ_EVENT_CONTROLLER && (ev->data).control.channel == channel &&
        ( ev->data ).control.param == ctrl_num_4bw && (unsigned int)( ev->data ).control.value == ctrl_val_4bw )
    {
//       std::cout << "Received a controller: channel = " << (int)( ev->data ).control.channel
//         << " controller number = " << (int)( ev->data ).control.param << " value " << (int)( ev->data ).control.value << std::endl;
      m_home = false;
      m_increment = false;
      m_go_back = false;
      m_read_text = false;
      m_pckbd_action = 0;
      m_4fw = false;
      m_4bw = true;
      caller->notify();
    }
  }


  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_shall_stop = false;
  m_has_stopped = true;
  lock.release();
  caller->notify();
}
