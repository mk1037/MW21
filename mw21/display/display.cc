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

#include "displaywin.h"
// #include <gtkmm/application.h>

int main (int argc, char* argv[])
{
  bool display_border = true;
  if (argc > 1)
  {
    Glib::ustring argument1(argv[1]);
    Glib::ustring noborder("-noborder");
    if ( argument1 == noborder )
      display_border = false;
  }

  DisplayConfig config;
  config.readConfig("/tmp/mw2_config");

  auto app = Gtk::Application::create("midi_display.app");

  DisplayWin window(&config);
  window.set_decorated(display_border);
  window.initialize();
  window.render_frame();

  window.start_listen();

  return app->run(window);
}
