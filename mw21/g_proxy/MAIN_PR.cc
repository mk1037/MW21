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

#include "g_proxywin.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
  bool display_border = true;
  if (argc > 1)
  {
    Glib::ustring argument1(argv[1]);
    Glib::ustring noborder("-noborder");
    if ( argument1 == noborder )
      display_border = false;
  }

  Glib::ustring t_label = "MAIN_PR";
  ProxyConfig config(t_label);
  config.readConfig("/tmp/mw2_config");

  auto app = Gtk::Application::create("MAIN_PR.app");

  GProxyWin window(&config, MAIN_PR);
  window.set_decorated(display_border);
  if(window.write_pid()) return 1;
  window.start_listen();
  std::cout << "MAIN_PR pid is " << getpid() << std::endl;
  return app->run(window);
}
