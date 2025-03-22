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

#ifndef G_PROXYWIN_H
#define G_PROXYWIN_H

#include <gtkmm.h>
#include "proxyconfig.h"
#include "proxyarea.h"

#define MAIN_PR 0
#define PR3000 2

class MidiClient;
class SignalClient;

class GProxyWin : public Gtk::Window
{
public:
  GProxyWin(ProxyConfig *pconfig, int p_atype);
  virtual ~GProxyWin();

  // Called from the worker thread.
  void notify();
  void notify2();
  void set_config(ProxyConfig *config);
  void start_listen();
  void set_switch(bool p_value);
  int write_pid();

private:
  // Signal handlers.
  void on_quit_button_clicked();

  void update_widgets();
  void on_notification_from_worker_thread();
  void update_widgets2();
  void on_notification_from_worker_thread2();

  ProxyConfig *proxyConfig;
  ProxyArea *m_area;
  Gtk::Box *m_VBox;

  Glib::Dispatcher m_Dispatcher;
  MidiClient *client;
  Glib::Threads::Thread *client_thread;

  Glib::Dispatcher m_Dispatcher2;
  SignalClient *client2;
  Glib::Threads::Thread *client_thread2;

  bool m_open;
  int m_atype;
};

#endif // G_PROXYWIN_H

