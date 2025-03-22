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

MidiClient::MidiClient()
{
  m_color_theme = 0;
  cqueue_a = 2;
//  cqueue_b = 0;
  ok_pressed = false;
  search_pressed = false;
  m_set_bank_theme = THEME_BANK_3;
  r = nullptr;
}

MidiClient::~MidiClient()
{
  if(r) snd_seq_close(r);
  std::cout << "Closing sequencer" << std::endl;
}

int MidiClient::readBanks(Glib::ustring p_prefix)
{
  //if(queue_a[0].readDir(p_prefix + "/bank_1/text/")) return 1;
  //if(queue_a[1].readDir(p_prefix + "/bank_2/text/")) return 1;
  if(queue_a[2].readDir(p_prefix + "/bank_3/text/")) return 1;

  return 0;
}

void MidiClient::configure(ModelineConfig* pconfig)
{
  control_channel = pconfig->getModelineControlChannel();
}


void MidiClient::open_client()
{
  port_id = -1;
  int err;
  err = snd_seq_open ( &r, "default", SND_SEQ_OPEN_DUPLEX, 0 );
  if ( err < 0 )
    return;
  snd_seq_set_client_name ( r, "Modeline" );
}

void MidiClient::new_port_write()
{
  port_id = snd_seq_create_simple_port ( r, "Modeline_write",
                                       SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
                                       SND_SEQ_PORT_TYPE_MIDI_GENERIC );
}

int MidiClient::get_port()
{
  return port_id;
}

void MidiClient::get_data(Glib::ustring* current_item_1, Glib::ustring* current_item_2,
                          Glib::ustring* prev_item_1, Glib::ustring* next_item_1,
                          int* p_action, int* p_theme_idx, int * p_character_pressed) const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  *current_item_1 = queue_a[cqueue_a].getItem(queue_a[cqueue_a].getPointer());
//  *current_item_2 = queue_b[cqueue_b].getItem(queue_b[cqueue_b].getPointer());

  *prev_item_1 = queue_a[cqueue_a].getItem(queue_a[cqueue_a].getPointer() - 1);
  *next_item_1 = queue_a[cqueue_a].getItem(queue_a[cqueue_a].getPointer() + 1);

  *p_action = m_action;
  *p_theme_idx = m_set_bank_theme; // non-negative value means - change
  *p_character_pressed = m_character_pressed;
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
/*
void MidiClient::set_theme(unsigned int p_idx)
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_color_theme = p_idx;
}
*/
void MidiClient::listen(ModelineWin * caller)
{
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    m_has_stopped = false;
    m_message = "";
  } // The mutex is unlocked here by lock's destructor.

  snd_seq_event_t *ev;

  while(snd_seq_event_input ( r, &ev ) >= 0 && !m_shall_stop)
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    //m_character_pressed = 0;
    m_action = 0;
    //m_set_bank_theme = -1;
    if ( ev->type == SND_SEQ_EVENT_NOTEON
       && (unsigned int) (ev->data).note.velocity > 0
       && ( 
         ( (unsigned int) (ev->data).note.note >= NOTE_A && (unsigned int) (ev->data).note.note <= NOTE_Z )
         ||
           (unsigned int) (ev->data).note.note == NOTE_ARM
         ||
           (unsigned int) (ev->data).note.note == NOTE_DISARM
       )
    )
    {
      std::cout << "Received an event: channel = " << (int)( ev->data ).note.channel
        << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      switch((int)( ev->data ).note.note)
      {
        case NOTE_CHAR_LEFT:
          queue_a[cqueue_a].decreaseChar();
          m_action = ACTION_SET_FILE_1;
          m_character_pressed = 0;
          break;
        case NOTE_LEFT:
          queue_a[cqueue_a].decrease();
          m_action = ACTION_SET_FILE_1;
          m_character_pressed = 0;
          break;
        case NOTE_RIGHT_1:
          queue_a[cqueue_a].increase();
          m_action = ACTION_SET_FILE_1;
          m_character_pressed = 0;
          break;
        case NOTE_RIGHT_2:
          queue_a[cqueue_a].increase();
          m_action = ACTION_SET_FILE_1;
          m_character_pressed = 0;
          break;
        case NOTE_CHAR_RIGHT:
          queue_a[cqueue_a].increaseChar();
          m_action = ACTION_SET_FILE_1;
          m_character_pressed = 0;
          break;

        case NOTE_STOP_A:
          m_action = ACTION_STOP_1;
          m_character_pressed = 0;
          break;
        case NOTE_STOP_B:
          m_action = ACTION_STOP_2;
          m_character_pressed = 0;
          break;
        case NOTE_LOAD_A:
          m_action = ACTION_LOAD_1;
          m_character_pressed = 0;
          break;
        case NOTE_PLAY:
          m_action = ACTION_PLAY;
          m_character_pressed = 0;
          break;
        case NOTE_LOAD_B:
          m_action = ACTION_LOAD_2;
          m_character_pressed = 0;
          break;

        case NOTE_ARM:
//          m_action = ACTION_ARM;
//          m_character_pressed = 0;
          break;
        case NOTE_DISARM:
//          m_action = ACTION_DISARM;
//          m_character_pressed = 0;
          break;

        case NOTE_OK:
          ok_pressed = true;
          if(search_pressed)
            m_action = ACTION_INFO_CLEAR;
          else
            m_action = ACTION_INFO_OK;
          m_character_pressed = 0;
          break;
        case NOTE_SEARCH:
          search_pressed = true;
          if(ok_pressed)
            m_action = ACTION_INFO_CLEAR;
          else
            m_action = ACTION_INFO_SEARCH;
          m_character_pressed = 0;
          break;
        case NOTE_BANK_1:
//          cqueue_a = 0;
//          m_set_bank_theme = THEME_BANK_1;
//          m_action = ACTION_SET_FILE_1;
//          m_character_pressed = 0;
          break;
        case NOTE_BANK_2:
//          cqueue_a = 1;
//          m_set_bank_theme = THEME_BANK_2;
//          m_action = ACTION_SET_FILE_1;
//          m_character_pressed = 0;
          break;
        case NOTE_BANK_3:
          cqueue_a = 2;
          m_set_bank_theme = THEME_BANK_3;
          m_action = ACTION_SET_FILE_1;
          m_character_pressed = 0;
          break;

        case NOTE_A:
          m_character_pressed = queue_a[cqueue_a].setAtChar('a');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_B:
          m_character_pressed = queue_a[cqueue_a].setAtChar('b');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_C:
          m_character_pressed = queue_a[cqueue_a].setAtChar('c');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_D:
          m_character_pressed = queue_a[cqueue_a].setAtChar('d');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_E:
          m_character_pressed = queue_a[cqueue_a].setAtChar('e');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_F:
          m_character_pressed = queue_a[cqueue_a].setAtChar('f');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_G:
          m_character_pressed = queue_a[cqueue_a].setAtChar('g');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_H:
          m_character_pressed = queue_a[cqueue_a].setAtChar('h');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_I:
          m_character_pressed = queue_a[cqueue_a].setAtChar('i');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_J:
          m_character_pressed = queue_a[cqueue_a].setAtChar('j');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_K:
          m_character_pressed = queue_a[cqueue_a].setAtChar('k');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_L:
          m_character_pressed = queue_a[cqueue_a].setAtChar('l');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_M:
          m_character_pressed = queue_a[cqueue_a].setAtChar('m');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_N:
          m_character_pressed = queue_a[cqueue_a].setAtChar('n');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_O:
          m_character_pressed = queue_a[cqueue_a].setAtChar('o');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_P:
          m_character_pressed = queue_a[cqueue_a].setAtChar('p');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_R:
          m_character_pressed = queue_a[cqueue_a].setAtChar('r');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_S:
          m_character_pressed = queue_a[cqueue_a].setAtChar('s');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_T:
          m_character_pressed = queue_a[cqueue_a].setAtChar('t');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_U:
          m_character_pressed = queue_a[cqueue_a].setAtChar('u');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_W:
          m_character_pressed = queue_a[cqueue_a].setAtChar('w');
          m_action = ACTION_SET_FILE_1;
          break;
        case NOTE_Z:
          m_character_pressed = queue_a[cqueue_a].setAtChar('z');
          m_action = ACTION_SET_FILE_1;
          break;
        default:
          continue;
          break;
      }

      caller->notify();
    }

    if (
         (
           ( ev->type == SND_SEQ_EVENT_NOTEON && (ev->data).note.velocity == 0 )
           ||
           ( ev->type == SND_SEQ_EVENT_NOTEOFF )
         )
         && (unsigned int) (ev->data).note.note >= NOTE_A
         && (unsigned int) (ev->data).note.note <= NOTE_Z
       )
    {
      //std::cout << "Received an event: channel = " << (int)( ev->data ).note.channel
      //  << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
      switch((int)( ev->data ).note.note)
      {
        case NOTE_OK:
          ok_pressed = false;
          break;
        case NOTE_SEARCH:
          search_pressed = false;
          break;
        default:
          break;
      }
    }
    if ( ev->type == SND_SEQ_EVENT_CONTROLLER
         && (unsigned int) (ev->data).control.param >= SUBSET1_CTRL
         && (unsigned int) (ev->data).control.param <= SUBSET8_CTRL
       )
    {
      queue_a[cqueue_a].setAtIndex(
        (unsigned int)(ev->data).control.value +
        ((((unsigned int) (ev->data).control.param) - SUBSET1_CTRL) * 128)
      );
      m_character_pressed = 0;
      m_action = ACTION_SET_FILE_1;
      caller->notify();
    }
  }


  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_shall_stop = false;
  m_has_stopped = true;
  lock.release();
  caller->notify();
}
