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

#include "remotewin.h"
#include <unistd.h>

void printSeparator(std::string name)
{
  std::cout << "------------------- " << name << " --------------------" << std::endl;
  
}

void printRemoteConfig(RemoteConfig * config)
{
  std::cout << "Remote instruction path:     " << config->getRemoteInstructionPath() << std::endl;
  std::cout << "Remote pid path:             " << config->getRemotePidPath()         << std::endl;

  std::cout << "Modeline control channel:    " << config->getModelineControlChannel() << std::endl;

  std::cout << "Note load:                   " << config->getNoteLoad()               << std::endl;
  std::cout << "Note play:                   " << config->getNotePlay()               << std::endl;
  std::cout << "Note stop:                   " << config->getNoteStop()               << std::endl;
}

int test1(int argc, char* argv[])
{
  printSeparator("test1");

  RemoteConfig config;

  printRemoteConfig(&config);

  return 0;
}

int test2(int argc, char* argv[])
{
  printSeparator("test2");

  RemoteConfig config;
  config.readConfig("/tmp/mw2_config");
  printRemoteConfig(&config);

  return 0;
}

int test3(int argc, char* argv[])
{
  printSeparator("test3");

  RemoteConfig config;
  config.readConfig("/tmp/mw2_config");
  printRemoteConfig(&config);

  auto app = Gtk::Application::create(argc, argv, "remote.app");

  RemoteWin window(&config);
  if(window.write_pid()) return 1;

  window.start_listen();
//   std::cout << getpid() << std::endl;
  return app->run(window);

}


// int test4(int argc, char* argv[])
// {
//   printSeparator("test4");
// 
//   Glib::ustring t_label = "PR1100";
//   ProxyConfig config(t_label);
//   config.readConfig("/home/user2/work/displayconfig");
//   printProxyConfig(&config);
// 
//   auto app = Gtk::Application::create(argc, argv, "PR1100.app");
// 
//   GProxyWin window(&config, PR1100);
//   if(window.write_pid()) return 1;
//   window.start_listen();
// 
//   return app->run(window);
// 
// }


//#################################################

int main(int argc, char* argv[])
{
  return test3(argc, argv);
}
