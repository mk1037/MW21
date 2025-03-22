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

#include "displayconfig.h"
#include "displaywin.h"
#include "textqueue.h"

void printSeparator(std::string name)
{
  std::cout << "------------------- " << name << " --------------------" << std::endl;
  
}

void printDisplayConfig(DisplayConfig * config)
{
  std::cout << "Background color:          " << config->getBackgroundColor(0)         << std::endl;
  std::cout << "Sung background color:     " << config->getSungBackgroundColor(0)     << std::endl;
  std::cout << "Lyrics color:              " << config->getLyricsColor(0)             << std::endl;
  std::cout << "Sung lyrics color:         " << config->getSungLyricsColor(0)         << std::endl;
  std::cout << "Lyrics outline color:      " << config->getLyricsOutlineColor(0)      << std::endl;
  std::cout << "Sung lyrics outline color: " << config->getSungLyricsOutlineColor(0)  << std::endl;

  std::cout << "Hints background color:    " << config->getHintsBackgroundColor(0)    << std::endl;
  std::cout << "Active hints bckgr. color: " << config->getActiveHintsBackgroundColor(0) << std::endl;
  std::cout << "Hints color:               " << config->getHintsColor(0)              << std::endl;
  std::cout << "Active hints color:        " << config->getActiveHintsColor(0)        << std::endl;
  std::cout << "Hints outline color:       " << config->getHintsOutlineColor(0)       << std::endl;
  std::cout << "ActiveHints outline color: " << config->getActiveHintsOutlineColor(0) << std::endl;

  std::cout << std::endl;

  std::cout << "Background color2:         " << config->getBackgroundColor(1)         << std::endl;
  std::cout << "Sung background color2:    " << config->getSungBackgroundColor(1)     << std::endl;
  std::cout << "Lyrics color2:             " << config->getLyricsColor(1)             << std::endl;
  std::cout << "Sung lyrics color2:        " << config->getSungLyricsColor(1)         << std::endl;
  std::cout << "Lyrics outline color2:     " << config->getLyricsOutlineColor(1)      << std::endl;
  std::cout << "Sung lyrics outline color2:" << config->getSungLyricsOutlineColor(1)  << std::endl;

  std::cout << "Hints background color2:   " << config->getHintsBackgroundColor(1)    << std::endl;
  std::cout << "Active hints bckgr. color2:" << config->getActiveHintsBackgroundColor(1) << std::endl;
  std::cout << "Hints color2:              " << config->getHintsColor(1)              << std::endl;
  std::cout << "Active hints color2:       " << config->getActiveHintsColor(1)        << std::endl;
  std::cout << "Hints outline color2:      " << config->getHintsOutlineColor(1)       << std::endl;
  std::cout << "ActiveHints outline color2:" << config->getActiveHintsOutlineColor(1) << std::endl;

  std::cout << std::endl;

  std::cout << "Background color3:         " << config->getBackgroundColor(2)         << std::endl;
  std::cout << "Sung background color3:    " << config->getSungBackgroundColor(2)     << std::endl;
  std::cout << "Lyrics color3:             " << config->getLyricsColor(2)             << std::endl;
  std::cout << "Sung lyrics color3:        " << config->getSungLyricsColor(2)         << std::endl;
  std::cout << "Lyrics outline color3:     " << config->getLyricsOutlineColor(2)      << std::endl;
  std::cout << "Sung lyrics outline color3:" << config->getSungLyricsOutlineColor(2)  << std::endl;

  std::cout << "Hints background color3:   " << config->getHintsBackgroundColor(2)    << std::endl;
  std::cout << "Active hints bckgr. color3:" << config->getActiveHintsBackgroundColor(2) << std::endl;
  std::cout << "Hints color3:              " << config->getHintsColor(2)              << std::endl;
  std::cout << "Active hints color3:       " << config->getActiveHintsColor(2)        << std::endl;
  std::cout << "Hints outline color3:      " << config->getHintsOutlineColor(2)       << std::endl;
  std::cout << "ActiveHints outline color3:" << config->getActiveHintsOutlineColor(2) << std::endl;

  std::cout << std::endl;





  std::cout << "Outline width              " << config->getOutlineWidth()           << std::endl;
  std::cout << "Font dir prefix:           " << config->getFontDirPrefix()          << std::endl;
  std::cout << "Font name:                 " << config->getFontName()               << std::endl;
  std::cout << "Font size:                 " << config->getFontSize()               << std::endl;

  std::cout << "Text pointer path:         " << config->getTextPointerPath()        << std::endl;
  std::cout << "Data directory:            " << config->getDataDir()                << std::endl;

  std::cout << "Channel:                   " << config->getChannel()                << std::endl;
  std::cout << "NoteGEQ:                   " << config->getNoteGEQ()                << std::endl;
  std::cout << "NoteLT:                    " << config->getNoteLT()                 << std::endl;
  std::cout << "VelGEQ:                    " << config->getVelGEQ()                 << std::endl;
  std::cout << "VelLT:                     " << config->getVelLT()                  << std::endl;

  std::cout << "CtrlNum4Fw:                " << config->getCtrlNum4Fw()             << std::endl;
  std::cout << "CtrlVal4Fw:                " << config->getCtrlVal4Fw()             << std::endl;
  std::cout << "CtrlNum4Bw:                " << config->getCtrlNum4Bw()             << std::endl;
  std::cout << "CtrlVal4Bw:                " << config->getCtrlVal4Bw()             << std::endl;

  std::cout << "NoteRead:                  " << config->getNoteRead()               << std::endl;
  std::cout << "VelRead:                   " << config->getVelRead()                << std::endl;

  std::cout << "NoteBack:                  " << config->getNoteBack()               << std::endl;
  std::cout << "VelBack:                   " << config->getVelBack()                << std::endl;

  std::cout << "NoteTheme1:                " << config->getNoteTheme1()             << std::endl;
  std::cout << "VelTheme1:                 " << config->getVelTheme1()              << std::endl;

  std::cout << "NoteTheme2:                " << config->getNoteTheme2()             << std::endl;
  std::cout << "VelTheme2:                 " << config->getVelTheme2()              << std::endl;

  std::cout << "NoteTheme3:                " << config->getNoteTheme3()             << std::endl;
  std::cout << "VelTheme3:                 " << config->getVelTheme3()              << std::endl;

  std::cout << "NotePCKbdEnable:           " << config->getNotePCKbdEnable()        << std::endl;
  std::cout << "NotePCKbdDisable:          " << config->getNotePCKbdDisable()       << std::endl;

  std::cout << "Area width:                " << config->getAreaWidth()              << std::endl;
  std::cout << "Area height:               " << config->getAreaHeight()             << std::endl;

  std::cout << "NoteHome:                  " << config->getNoteHome()               << std::endl;
  std::cout << "VelHome:                   " << config->getVelHome()                << std::endl;
}

int test1(int argc, char* argv[])
{
  printSeparator("test1");

  DisplayConfig config;

  printDisplayConfig(&config);

  return 0;
}

int test2(int argc, char* argv[])
{
  printSeparator("test2");

  DisplayConfig config;

  config.readConfig("/tmp/mw2_config");
  printDisplayConfig(&config);

  return 0;
}

int test3(int argc, char* argv[])
{

  printSeparator("test3");

  DisplayConfig config;
  config.readConfig("/tmp/mw2_config");

  auto app = Gtk::Application::create(argc, argv, "display.app");

  DisplayWin window(&config);
  window.initialize();
  //window.read_lines("przyklad3.txt");
  //window.set_pointer(-1);
  window.render_frame();

  window.start_listen();

  //Shows the window and returns when it is closed.
  return app->run(window);
}

int test4(int argc, char* argv[])
{
  std::cout << (int)get_red_value("010203") << std::endl;
  std::cout << (int)get_green_value("010203") << std::endl;
  std::cout << (int)get_blue_value("010203") << std::endl;
  std::cout << (int)get_alpha_value("01020304") << std::endl;

  return 0;
}

int test5(int argc, char* argv[])
{
  TextQueue my_queue;
  my_queue.read_lines("przyklad.txt", "przyklad.txt");
  my_queue.set_pointer(12);
  my_queue.print();
  //my_queue.get_frame();
  std::cout << "queue size is: " << my_queue.get_size() << std::endl;

  return 0;
}

int test6(int argc, char* argv[])
{
  Glib::ustring my_str("||i");

  std::cout << "Occurence is :" << (int) my_str.find((gunichar)'|', 6) << std::endl;
  return 0;
}

int test7(int argc, char* argv[])
{
  TextLine my_line;
  my_line.push("ch1");
  my_line.push(" ch2");
  //my_line.push("ch3");
  //my_line.push("ch4");

  my_line.print();
  std::cout << std::endl << "Size of line chunks is " << my_line.get_size() << std::endl;
  std::cout << "\"" << my_line.get_left(0) << "\"" << std::endl;
  std::cout << "\"" << my_line.get_right(0) << "\"" << std::endl;

  return 0;
}


int test8(int argc, char* argv[])
{
  FrameContent frame;

  frame.set_content(1, "text_left", "Text_right", true, false);

  frame.print();

  return 0;
}

int test9(int argc, char* argv[])
{
  TextQueue queue;

  queue.get_frame().print();

  return 0;
}

int test10(int argc, char* argv[])
{
  TextQueue my_queue;
  my_queue.read_lines("przyklad2.txt", "przyklad2.txt");
  my_queue.set_pointer(5);
  my_queue.print();
  my_queue.get_frame().print();

  return 0;
}

Glib::ustring test_get_filename(Glib::ustring path)
{
  Glib::ustring result;
  Glib::ustring::reverse_iterator rit = path.rbegin();
  int counter = 0;
  while((gunichar)'/' != *rit)
  {
    rit++;
    counter++;
  }
  return path.substr(path.length() - counter, counter);
}

int test11(int argc, char* argv[])
{
  Glib::ustring my_string("/a/ghi/b/directory/plik.txt");
  std::cout << test_get_filename(my_string) << std::endl;

  return 0;
}

//#################################################

int main(int argc, char* argv[])
{
  return test2(argc, argv);
}
