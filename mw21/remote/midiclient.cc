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

MidiClient::MidiClient(RemoteConfig * p_pconfig)
{
  modelineControlChannel  = p_pconfig->getModelineControlChannel();
  noteLoad = p_pconfig->getNoteLoad();
  notePlay = p_pconfig->getNotePlay();
  noteStop = p_pconfig->getNoteStop();
}

MidiClient::~MidiClient()
{
  snd_seq_close(r);
  std::cout << "Closing sequencer" << std::endl;
}

void MidiClient::open_client(Glib::ustring p_name)
{
  r_port_id = -1;
  int err;
  err = snd_seq_open ( &r, "default", SND_SEQ_OPEN_DUPLEX, 0 );
  if ( err < 0 )
    return;
  snd_seq_set_client_name ( r, p_name.c_str() );
}

void MidiClient::new_port_read()
{
  r_port_id = snd_seq_create_simple_port ( r, "Remote_read",
                                       SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
                                       SND_SEQ_PORT_TYPE_MIDI_GENERIC );
}

int MidiClient::get_port_read()
{
  return r_port_id;
}

bool MidiClient::get_client_success_info()
{
  if(r) return true;
  else return false;
}

void MidiClient::send(Glib::ustring p_instruction)
{
  std::cout  << "Sending from remote ... p_instruction " << p_instruction << std::endl;
  if(p_instruction == "LOAD")
  {
    std::cout  << "load  ..." << std::endl;
    snd_seq_event_t l_event_read;
    l_event_read.type = SND_SEQ_EVENT_NOTEON;
    l_event_read.data.note.channel = (unsigned char) modelineControlChannel;
    l_event_read.data.note.note = noteLoad;
    l_event_read.data.note.velocity = 10; // anything positive ...
    l_event_read.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_read.dest.port = 253;
    l_event_read.flags = 0;
    l_event_read.tag = 0;
    l_event_read.queue = 253;

    snd_seq_ev_set_source ( &l_event_read, r_port_id );
    snd_seq_ev_set_subs ( &l_event_read );
    snd_seq_event_output_direct ( r, &l_event_read);
    snd_seq_drain_output ( r );
  }

  if(p_instruction == "ARM")
  {
    std::cout  << "arm  ..." << std::endl;
    snd_seq_event_t l_event_read;
    l_event_read.type = SND_SEQ_EVENT_NOTEON;
    l_event_read.data.note.channel = (unsigned char) modelineControlChannel;
    l_event_read.data.note.note = 97; // hardcoded aligned to modeline
    l_event_read.data.note.velocity = 10; // anything positive ...
    l_event_read.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_read.dest.port = 253;
    l_event_read.flags = 0;
    l_event_read.tag = 0;
    l_event_read.queue = 253;

    snd_seq_ev_set_source ( &l_event_read, r_port_id );
    snd_seq_ev_set_subs ( &l_event_read );
    snd_seq_event_output_direct ( r, &l_event_read);
    snd_seq_drain_output ( r );
  }

  if(p_instruction == "DISARM")
  {
    std::cout  << "arm  ..." << std::endl;
    snd_seq_event_t l_event_read;
    l_event_read.type = SND_SEQ_EVENT_NOTEON;
    l_event_read.data.note.channel = (unsigned char) modelineControlChannel;
    l_event_read.data.note.note = 98; // hardcoded aligned to modeline
    l_event_read.data.note.velocity = 10; // anything positive ...
    l_event_read.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_read.dest.port = 253;
    l_event_read.flags = 0;
    l_event_read.tag = 0;
    l_event_read.queue = 253;

    snd_seq_ev_set_source ( &l_event_read, r_port_id );
    snd_seq_ev_set_subs ( &l_event_read );
    snd_seq_event_output_direct ( r, &l_event_read);
    snd_seq_drain_output ( r );
  }

  if(p_instruction == "PLAY")
  {
    std::cout  << "play  ..." << std::endl;
    snd_seq_event_t l_event_read;
    l_event_read.type = SND_SEQ_EVENT_NOTEON;
    l_event_read.data.note.channel = (unsigned char) modelineControlChannel;
    l_event_read.data.note.note = notePlay;
    l_event_read.data.note.velocity = 10; // anything positive ...
    l_event_read.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_read.dest.port = 253;
    l_event_read.flags = 0;
    l_event_read.tag = 0;
    l_event_read.queue = 253;

    snd_seq_ev_set_source ( &l_event_read, r_port_id );
    snd_seq_ev_set_subs ( &l_event_read );
    snd_seq_event_output_direct ( r, &l_event_read);
    snd_seq_drain_output ( r );
  }

  if(p_instruction == "STOP")
  {
    std::cout  << "stop  ..." << std::endl;
    snd_seq_event_t l_event_read;
    l_event_read.type = SND_SEQ_EVENT_NOTEON;
    l_event_read.data.note.channel = (unsigned char) modelineControlChannel;
    l_event_read.data.note.note = noteStop;
    l_event_read.data.note.velocity = 10; // anything positive ...
    l_event_read.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_read.dest.port = 253;
    l_event_read.flags = 0;
    l_event_read.tag = 0;
    l_event_read.queue = 253;

    snd_seq_ev_set_source ( &l_event_read, r_port_id );
    snd_seq_ev_set_subs ( &l_event_read );
    snd_seq_event_output_direct ( r, &l_event_read);
    snd_seq_drain_output ( r );
  }

}
