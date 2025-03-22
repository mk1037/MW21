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

#ifndef MODELINE_MODELINEWIN_H
#define MODELINE_MODELINEWIN_H

#define STATE_IDLE       0
#define STATE_PLAYING    1
#define STATE_LOADED_K1E 2
#define STATE_LOADED_WRX 3
#define STATE_LOADED_K3Y 4

#include <gtkmm.h>
#include "modelineconfig.h"
#include "modelinearea.h"
#include "modelineaction.h"
#include "filesqueue.h"
#include "midiclient.h"
// #include "signalclient.h"
#include "timeoutclient.h"

class MidiClient;
class BlinkClient;
class TimeoutClient;
class SignalClient;

class ModelineWin : public Gtk::Window
{
public:
  ModelineWin(ModelineConfig *pconfig);
  virtual ~ModelineWin();

  int initialize();

  // Called from the worker thread.
  void notify();
  void notify_timeout();
  void set_config(ModelineConfig *config);
  void start_listen();
  int write_pid();
  void notify2();


private:
  // Signal handlers.
  void on_quit_button_clicked();

  void update_widgets();
  void update_widgets2();	
  void on_notification_from_worker_thread();
  void on_notification_from_timeout_thread();
  void on_notification_from_signal_thread();
  void do_logic();
  
  
  Glib::ustring current_item, prev_item, next_item;
  int action, theme_idx, character;
  bool sensitive_actions_lock;
  unsigned int m_prompt_1_theme;
  unsigned int m_prompt_2_theme;

  Glib::ustring bank_1_pattern;
  Glib::RefPtr<Glib::Regex> bank_1_patternRegex;

  Glib::ustring bank_2_pattern;
  Glib::RefPtr<Glib::Regex> bank_2_patternRegex;

  Glib::ustring bank_3_pattern;
  Glib::RefPtr<Glib::Regex> bank_3_patternRegex;
  //Glib::ustring get_filename(Glib::ustring path);
  // Member data.
  Gtk::Grid *m_grid;

  ModelineConfig *modelineConfig;
  ModelineAction * modelineAction;

  Glib::Dispatcher m_Dispatcher;
  MidiClient *client;
  Glib::Threads::Thread *client_thread;

//   Glib::Dispatcher m_blinkDispatcher;
//   BlinkClient *blinkClient;
//   Glib::Threads::Thread *blink_client_thread;

  Glib::Dispatcher m_timeoutDispatcher;
  TimeoutClient *timeoutClient;
  Glib::Threads::Thread *timeout_client_thread;

  Glib::Dispatcher m_signalDispatcher;
  SignalClient *signalClient;
  Glib::Threads::Thread *signal_client_thread;

  Glib::ustring title_b;

  unsigned int prompt_width, side_item_width, item_width;

  ModelineArea * m_prompt_1;
  ModelineArea * m_prev;
  ModelineArea * m_curr;
  ModelineArea * m_next;

  ModelineArea * m_sep_1;
  ModelineArea * m_sep_2;
  ModelineArea * m_sep_3;
  ModelineArea * m_sep_4;

  ModelineArea * m_prompt_2;
  ModelineArea * m_space1;
  ModelineArea * m_space2;
  ModelineArea * m_curr2;

  FT_Face       face;
  FT_Library    library;
  unsigned char *fontBuffer;
  unsigned int last_loaded;
  unsigned int m_state;

  bool m_initialized;
};

#endif // MODELINE_MODELINEWIN_H

