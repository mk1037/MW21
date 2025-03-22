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

MidiClient::MidiClient(ProxyConfig * p_pconfig)
{
  pressed = 0;
  open = true;
  textChannel = p_pconfig->getTextChannel();
  controlChannel = p_pconfig->getControlChannel();

  noteGEQ = p_pconfig->getNoteGEQ();
  noteLT = p_pconfig->getNoteLT();
  velGEQ = p_pconfig->getVelGEQ();
  velLT = p_pconfig->getVelLT();
  noteBack = p_pconfig->getNoteBack();
  velBack = p_pconfig->getVelBack();
  noteHome = p_pconfig->getNoteHome();
  velHome = p_pconfig->getVelHome();
}

MidiClient::~MidiClient()
{
  snd_seq_close(r);
  std::cout << "Closing sequencer" << std::endl;
}

void MidiClient::open_client(Glib::ustring p_name)
{
  r_port_id = -1;
  w_port_id = -1;
  int err;
  err = snd_seq_open ( &r, "default", SND_SEQ_OPEN_DUPLEX, 0 );
  if ( err < 0 )
    return;
  snd_seq_set_client_name ( r, p_name.c_str() );
}

void MidiClient::new_port_write(Glib::ustring p_name)
{
  Glib::ustring port_name = p_name + "_write";
  w_port_id = snd_seq_create_simple_port ( r, port_name.c_str(),
                                       SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
                                       SND_SEQ_PORT_TYPE_MIDI_GENERIC );
}

int MidiClient::get_port_write()
{
  return w_port_id;
}

void MidiClient::new_port_read(Glib::ustring p_name)
{
  Glib::ustring port_name = p_name + "_read";
  r_port_id = snd_seq_create_simple_port ( r, port_name.c_str(),
                                       SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
                                       SND_SEQ_PORT_TYPE_MIDI_GENERIC );
}

int MidiClient::get_port_read()
{
  return r_port_id;
}
/*
void MidiClient::get_data(bool *p_open) const
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  *p_open = open;
}
*/
void MidiClient::stop_work()
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  std::cout << "Stopping listener" << std::endl;
  m_shall_stop = true;
}

void MidiClient::set_open(bool p_open)
{
  Glib::Threads::Mutex::Lock lock(m_Mutex);
  open = p_open;
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

// MAIN PROXY
void MidiClient::listen0(GProxyWin * caller)
{
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    m_has_stopped = false;
    m_message = "";
  } // The mutex is unlocked here by lock's destructor.

  snd_seq_event_t *ev;
  snd_seq_event_t event_on_send;

  while(snd_seq_event_input ( r, &ev ) >= 0 && !m_shall_stop)
  {
//    std::cout << "algo 0" << std::endl;

    if ( ev->type == SND_SEQ_EVENT_NOTEON )
    {
      Glib::Threads::Mutex::Lock lock(m_Mutex);
      if(open || (int)( ev->data ).note.velocity == 0 )
      {
      //std::cout << "Received an event: channel = " << (int)( ev->data ).note.channel
      //      << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
        memcpy ( ( void * ) &(event_on_send), ( void * ) ev, sizeof ( *ev ) );
        snd_seq_ev_set_source ( &event_on_send, r_port_id );
        snd_seq_ev_set_subs ( &event_on_send );
        snd_seq_event_output_direct ( r, &event_on_send );
        snd_seq_drain_output ( r );
      }
    }

    if ( ev->type == SND_SEQ_EVENT_NOTEOFF )
    {
      memcpy ( ( void * ) &(event_on_send), ( void * ) ev, sizeof ( *ev ) );
      snd_seq_ev_set_source ( &event_on_send, r_port_id );
      snd_seq_ev_set_subs ( &event_on_send );
      snd_seq_event_output_direct ( r, &event_on_send );
      snd_seq_drain_output ( r );
    }
    if ( ev->type == SND_SEQ_EVENT_CONTROLLER )
    {
//       std::cout << "Main proxy dostal controllera" << std::endl;
      Glib::Threads::Mutex::Lock lock(m_Mutex);
      if(open)
      {
//       std::cout << "Received controller in MAIN_PR: channel = " << (int)( ev->data ).control.channel
//             << " ctrl_number = " << (int)( ev->data ).control.param << " value " << (int)( ev->data ).control.value << std::endl;
        memcpy ( ( void * ) &(event_on_send), ( void * ) ev, sizeof ( *ev ) );
        snd_seq_ev_set_source ( &event_on_send, r_port_id );
        snd_seq_ev_set_subs ( &event_on_send );
//         event_on_send.dest.port = 253;
//         event_on_send.flags = 0;
//         event_on_send.tag = 0;
//         event_on_send.queue = 253;
        snd_seq_event_output_direct ( r, &event_on_send );
        snd_seq_drain_output ( r );
      }
    }
    if ( ev->type == SND_SEQ_EVENT_PGMCHANGE )
    {
      Glib::Threads::Mutex::Lock lock(m_Mutex);
      if(open)
      {
        memcpy ( ( void * ) &(event_on_send), ( void * ) ev, sizeof ( *ev ) );
        snd_seq_ev_set_source ( &event_on_send, r_port_id );
        snd_seq_ev_set_subs ( &event_on_send );
        snd_seq_event_output_direct ( r, &event_on_send );
        snd_seq_drain_output ( r );
      }
    }
  }

  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_shall_stop = false;
  m_has_stopped = true;
  lock.release();
  caller->notify();
}




// for PR3000
void MidiClient::listen2(GProxyWin * caller)
{
  {
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    m_has_stopped = false;
    m_message = "";
  } // The mutex is unlocked here by lock's destructor.

  snd_seq_event_t *ev;
  snd_seq_event_t event_on_send;

  while(snd_seq_event_input ( r, &ev ) >= 0 && !m_shall_stop)
  {
    if((unsigned int)( ev->data ).note.channel != textChannel) continue;

    if ( ev->type == SND_SEQ_EVENT_NOTEON )
    {
      Glib::Threads::Mutex::Lock lock(m_Mutex);
      if(open &&
      (
           ((unsigned int)( ev->data ).note.note >= noteGEQ && (unsigned int)( ev->data ).note.note < noteLT &&
            (unsigned int)( ev->data ).note.velocity >= velGEQ && (unsigned int)( ev->data ).note.velocity < velLT )
           ||
           ( (unsigned int)( ev->data ).note.note == noteHome && (unsigned int)( ev->data ).note.velocity == velHome )
      ) )
      {
      //std::cout << "Received an event: channel = " << (int)( ev->data ).note.channel
      //      << " note = " << (int)( ev->data ).note.note << " velocity " << (int)( ev->data ).note.velocity << std::endl;
        memcpy ( ( void * ) &(event_on_send), ( void * ) ev, sizeof ( *ev ) );
        snd_seq_ev_set_source ( &event_on_send, r_port_id );
        snd_seq_ev_set_subs ( &event_on_send );
        snd_seq_event_output_direct ( r, &event_on_send );
        snd_seq_drain_output ( r );
      }
    }
  }

  Glib::Threads::Mutex::Lock lock(m_Mutex);
  m_shall_stop = false;
  m_has_stopped = true;
  lock.release();
  caller->notify();
}

bool MidiClient::is_trigger_note(unsigned int a)
{
  if (
    a == 37 || // cis
    a == 39 ||

    a == 42 || // fis
    a == 44 ||
    a == 46 ||

    a == 49 || // cis
    a == 51 ||

    a == 54 || // fis
    a == 56 ||
    a == 58 ||

    a == 61 || // cis
    a == 63 ||

    a == 92 || // gis
    a == 94
  ) return true;
  return false;
}

bool MidiClient::is_counted_note(unsigned int a)
{
  if (!is_trigger_note(a)) return false;
  if ( a == 37 || a == 39 || a == 92 || a == 94 ) return false;
  return true;
}

bool MidiClient::is_back_note(unsigned int a)
{
  if ( a == 37 || a == 92 ) return true;
  return false;
}

void MidiClient::decrease()
{
  if(pressed > 0) pressed--;
}

void MidiClient::increase()
{
  pressed++;
}
