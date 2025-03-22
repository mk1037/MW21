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

#include "chooserwin.h"
#include <unistd.h>

void printSeparator(std::string name)
{
  std::cout << "------------------- " << name << " --------------------" << std::endl;
  
}

void printChooserConfig(ChooserConfig * config)
{
  std::cout << "Chooser instruction path:     " << config->getChooserInstructionPath() << std::endl;
  std::cout << "Chooser pid path:             " << config->getChooserPidPath()         << std::endl;

  std::cout << "Text channel:                 " << config->getTextChannel()            << std::endl;

  std::cout << "NoteRead:                     " << config->getNoteRead()               << std::endl;
  std::cout << "VelRead:                      " << config->getVelRead()                << std::endl;

  std::cout << "NoteTheme1:                   " << config->getNoteTheme1()             << std::endl;
  std::cout << "VelTheme1:                    " << config->getVelTheme1()              << std::endl;

  std::cout << "NoteTheme2:                   " << config->getNoteTheme2()             << std::endl;
  std::cout << "VelTheme2:                    " << config->getVelTheme2()              << std::endl;

  std::cout << "NoteTheme3:                   " << config->getNoteTheme3()             << std::endl;
  std::cout << "VelTheme3:                    " << config->getVelTheme3()              << std::endl;

  std::cout << "NotePCKbdEnable:              " << config->getNotePCKbdEnable()        << std::endl;
  std::cout << "NotePCKbdDisable:             " << config->getNotePCKbdDisable()       << std::endl;

  std::cout << "NoteHome:                     " << config->getNoteHome()               << std::endl;
  std::cout << "VelHome:                      " << config->getVelHome()                << std::endl;
}

int test1(int argc, char* argv[])
{
  printSeparator("test1");

  ChooserConfig config;

  printChooserConfig(&config);

  return 0;
}

int test2(int argc, char* argv[])
{
  printSeparator("test2");

  ChooserConfig config;
  config.readConfig("/tmp/mw2_config");
  printChooserConfig(&config);

  return 0;
}

int test3(int argc, char* argv[])
{
  printSeparator("test3");

  ChooserConfig config;
  config.readConfig("/tmp/mw2_config");
  printChooserConfig(&config);

  auto app = Gtk::Application::create(argc, argv, "chooser.app");

  ChooserWin window(&config);
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
