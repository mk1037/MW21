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
  Glib::ustring t_label = "PR3000";
  ProxyConfig config(t_label);
  config.readConfig("/tmp/mw2_config");

  auto app = Gtk::Application::create(argc, argv, "PR3000.app");

  GProxyWin window(&config, PR3000);
  if(window.write_pid()) return 1;
  window.start_listen();
  std::cout << "PR3000 pid is " << getpid() << std::endl;
  return app->run(window);
}
