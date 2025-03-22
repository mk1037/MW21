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

#ifndef REMOTEWIN_H
#define REMOTEWIN_H

#include <gtkmm.h>
#include "remoteconfig.h"
#include "remotearea.h"
#include "midiclient.h"

class SignalClient;
class MidiClient;

class RemoteWin : public Gtk::Window
{
public:
  RemoteWin(RemoteConfig *pconfig);
  virtual ~RemoteWin();

  // Called from the worker thread.
  void notify();
  void start_listen();
  int write_pid();

private:
  // Signal handlers.
  void on_quit_button_clicked();

  void on_notification_from_worker_thread();

  RemoteConfig *chooserConfig;
  RemoteArea *m_area;
  Gtk::Box *m_VBox;

  MidiClient *client;

  Glib::Dispatcher m_Dispatcher;
  SignalClient *signalClient;
  Glib::Threads::Thread *signal_client_thread;
};

#endif // CHOOSERWIN_H
