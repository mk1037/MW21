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

MidiClient::MidiClient(ChooserConfig * p_pconfig)
{
  textChannel = p_pconfig->getTextChannel();
  noteRead = p_pconfig->getNoteRead();
  velRead = p_pconfig->getVelRead();
  noteHome = p_pconfig->getNoteHome();
  velHome = p_pconfig->getVelHome();
  notePCKbdEnable = p_pconfig->getNotePCKbdEnable();
  notePCKbdDisable = p_pconfig->getNotePCKbdDisable();

  noteTheme1 = p_pconfig->getNoteTheme1();
  velTheme1 = p_pconfig->getVelTheme1();
  noteTheme2 = p_pconfig->getNoteTheme2();
  velTheme2 = p_pconfig->getVelTheme2();
  noteTheme3 = p_pconfig->getNoteTheme3();
  velTheme3 = p_pconfig->getVelTheme3();

  bank_1_pattern = "K1E";
  bank_2_pattern = "WR[Xx]";
  bank_3_pattern = "K3[Yy]";
  bank_1_patternRegex = Glib::Regex::create(bank_1_pattern);
  bank_2_patternRegex = Glib::Regex::create(bank_2_pattern);
  bank_3_patternRegex = Glib::Regex::create(bank_3_pattern);
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
  r_port_id = snd_seq_create_simple_port ( r, "Chooser_read",
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

void MidiClient::send(Glib::ustring p_instruction, Glib::ustring p_item)
{
  std::cout  << "Sending ... p_instruction " << p_instruction << " p_item " << p_item << std::endl;
  if(p_instruction == "LOAD")
  {
    std::cout  << "load  ..." << std::endl;
    snd_seq_event_t l_event_read;
    l_event_read.type = SND_SEQ_EVENT_NOTEON;
    l_event_read.data.note.channel = (unsigned char) textChannel;
    l_event_read.data.note.note = noteRead;
    l_event_read.data.note.velocity = velRead;
    l_event_read.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_read.dest.port = 253;
    l_event_read.flags = 0;
    l_event_read.tag = 0;
    l_event_read.queue = 253;

    snd_seq_ev_set_source ( &l_event_read, r_port_id );
    snd_seq_ev_set_subs ( &l_event_read );
    snd_seq_event_output_direct ( r, &l_event_read);
    snd_seq_drain_output ( r );
    usleep(50000);

    snd_seq_event_t l_event_theme;
    l_event_theme.type = SND_SEQ_EVENT_NOTEON;
    l_event_theme.data.note.channel = (unsigned char) textChannel;
    if(bank_1_patternRegex->match(p_item))
    {
      l_event_theme.data.note.note = noteTheme1;
      l_event_theme.data.note.velocity = velTheme1;
    }
    else if(bank_2_patternRegex->match(p_item))
    {
      l_event_theme.data.note.note = noteTheme2;
      l_event_theme.data.note.velocity = velTheme2;
    }
    else
    {
      l_event_theme.data.note.note = noteTheme3;
      l_event_theme.data.note.velocity = velTheme3;
    }

    l_event_theme.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_theme.dest.port = 253;
    l_event_theme.flags = 0;
    l_event_theme.tag = 0;
    l_event_theme.queue = 253;

    snd_seq_ev_set_source ( &l_event_theme, r_port_id );
    snd_seq_ev_set_subs ( &l_event_theme );
    snd_seq_event_output_direct ( r, &l_event_theme);
    snd_seq_drain_output ( r );
    usleep(50000);

    snd_seq_event_t l_event_pckbd;
    l_event_pckbd.type = SND_SEQ_EVENT_NOTEON;
    l_event_pckbd.data.note.channel = (unsigned char) textChannel;
    l_event_pckbd.data.note.velocity = 20;
    l_event_pckbd.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_pckbd.dest.port = 253;
    l_event_pckbd.flags = 0;
    l_event_pckbd.tag = 0;
    l_event_pckbd.queue = 253;

    l_event_pckbd.data.note.note = notePCKbdDisable;

    snd_seq_ev_set_source ( &l_event_pckbd, r_port_id );
    snd_seq_ev_set_subs ( &l_event_pckbd );
    snd_seq_event_output_direct ( r, &l_event_pckbd);
    snd_seq_drain_output ( r );
    usleep(50000);
  }

  if(p_instruction == "PLAY")
  {
    std::cout  << "play ..." << std::endl;
    snd_seq_event_t l_event_home;
    l_event_home.type = SND_SEQ_EVENT_NOTEON;
    l_event_home.data.note.channel = (unsigned char) textChannel;
    l_event_home.data.note.note = noteHome;
    l_event_home.data.note.velocity = velHome;
    l_event_home.dest.client = SND_SEQ_ADDRESS_SUBSCRIBERS;
    l_event_home.dest.port = 253;
    l_event_home.flags = 0;
    l_event_home.tag = 0;
    l_event_home.queue = 253;

    snd_seq_ev_set_source ( &l_event_home, r_port_id );
    snd_seq_ev_set_subs ( &l_event_home );
    snd_seq_event_output_direct ( r, &l_event_home);
    snd_seq_drain_output ( r );
    usleep(50000);
  }
}
