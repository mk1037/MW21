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

#ifndef DISPLAY_DISPLAYWIN_H
#define DISPLAY_DISPLAYWIN_H

#include <gtkmm.h>
#include "listener.h"
#include "displayconfig.h"
#include "displayarea.h"
#include "textqueue.h"
#include "midiclient.h"

class MidiClient;

class DisplayWin : public Gtk::Window
{
public:
  DisplayWin(DisplayConfig *pconfig);
  virtual ~DisplayWin();

  void initialize();
  // Called from the worker thread.
  void notify();
  void set_config(DisplayConfig *config);
  void read_lines(Glib::ustring path);
  void read_from_textpath();
  void set_pointer(int i);
  int get_pointer();
  void render_frame();
  void start_listen();
  void render_next_frame();
  void render_previous_frame();
  void render_4fw();
  void render_4bw();

private:
  // Signal handlers.
  void on_quit_button_clicked();
  void on_choose_file_clicked();

  void update_widgets(bool only_refresh = false);
  bool onKeyRelease(GdkEventKey* event);
  void on_notification_from_worker_thread();
  void write_textpath(std::string textpath);
  void set_title_label();
  void set_theme(unsigned int value);

  Glib::ustring get_filename(Glib::ustring path);
  // Member data.
  Gtk::Box *m_VBox;
  DisplayConfig *displayConfig;
  DisplayArea *displayArea[LINES_NUM];

  FrameContent frame;
  TextQueue queue;
  Glib::Dispatcher m_Dispatcher;
  MidiClient *client;
  Glib::Threads::Thread *client_thread;
  bool m_read_text_file;
  Glib::ustring text_title;
  unsigned int color_theme;
  bool go_back;
  bool increment;
  bool home;
  bool inc4;
  bool dec4;
  unsigned int pckbd_action;
  bool pckbd_enabled;
  bool select_group;
  unsigned int group;
  FT_Face       face;
  FT_Library    library;
  unsigned char *fontBuffer;

  Glib::ustring bank_1_pattern;
  Glib::RefPtr<Glib::Regex> bank_1_patternRegex;

  Glib::ustring bank_2_pattern;
  Glib::RefPtr<Glib::Regex> bank_2_patternRegex;

  Glib::ustring bank_3_pattern;
  Glib::RefPtr<Glib::Regex> bank_3_patternRegex;
};

#endif // DISPLAY_DISPLAYWIN_H

