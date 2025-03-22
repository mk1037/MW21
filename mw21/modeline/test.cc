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

#include "modelinewin.h"
#include "filesqueue.h"

void printSeparator(std::string name)
{
  std::cout << "------------------- " << name << " --------------------" << std::endl;
  
}

void printModelineConfig(ModelineConfig * config)
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

  std::cout << "Modeline background color neutral_1:  " << config->getModelineBackgroundColor_neutral1() << std::endl;
  std::cout << "Modeline background color neutral_2:  " << config->getModelineBackgroundColor_neutral2() << std::endl;
  std::cout << "Modeline background color blink_1:    " << config->getModelineBackgroundColor_blink1()   << std::endl;
  std::cout << "Modeline background color blink_2:    " << config->getModelineBackgroundColor_blink2()   << std::endl;
  std::cout << "Modeline background color ok:         " << config->getModelineBackgroundColor_ok()       << std::endl;
  std::cout << "Modeline background color search:     " << config->getModelineBackgroundColor_search()   << std::endl;
  std::cout << "Modeline background color found:      " << config->getModelineBackgroundColor_found()    << std::endl;

  std::cout << "Modeline font color neutral_1:        " << config->getModelineFontColor_neutral1()       << std::endl;
  std::cout << "Modeline font color neutral_2:        " << config->getModelineFontColor_neutral2()       << std::endl;
  std::cout << "Modeline font color blink_1:          " << config->getModelineFontColor_blink1()         << std::endl;
  std::cout << "Modeline font color blink_2:          " << config->getModelineFontColor_blink2()         << std::endl;
  std::cout << "Modeline font color ok:               " << config->getModelineFontColor_ok()             << std::endl;
  std::cout << "Modeline font color search:           " << config->getModelineFontColor_search()         << std::endl;
  std::cout << "Modeline font color found:            " << config->getModelineFontColor_found()          << std::endl;

  std::cout << "Modeline outline color neutral_1:     " << config->getModelineOutlineColor_neutral1()    << std::endl;
  std::cout << "Modeline outline color neutral_2:     " << config->getModelineOutlineColor_neutral2()    << std::endl;
  std::cout << "Modeline outline color blink_1:       " << config->getModelineOutlineColor_blink1()      << std::endl;
  std::cout << "Modeline outline color blink_2:       " << config->getModelineOutlineColor_blink2()      << std::endl;
  std::cout << "Modeline outline color ok:            " << config->getModelineOutlineColor_ok()          << std::endl;
  std::cout << "Modeline outline color search:        " << config->getModelineOutlineColor_search()      << std::endl;
  std::cout << "Modeline outline color found:         " << config->getModelineOutlineColor_found()       << std::endl;

  std::cout << std::endl;
  
  std::cout << "Instruction path:                     " << config->getInstructionPath()                  << std::endl;
  std::cout << "Pid path:                             " << config->getPidPath()                          << std::endl;

  std::cout << "Seq controller instruction:           " << config->getSeqControllerInstruction()         << std::endl;
  std::cout << "sc_trap pid path:                     " << config->getSCTrapPidPath()                    << std::endl;

  std::cout << "Outline width              " << config->getOutlineWidth()           << std::endl;
  std::cout << "Font dir prefix:           " << config->getFontDirPrefix()          << std::endl;
  std::cout << "Font name:                 " << config->getFontName()               << std::endl;
  std::cout << "Font size:                 " << config->getFontSize()               << std::endl;

  std::cout << "Modeline area width:       " << config->getModelineAreaWidth()      << std::endl;
  std::cout << "Modeline area height:      " << config->getModelineAreaHeight()     << std::endl;

  std::cout << "Blink counter:             " << config->getBlinkCounter()           << std::endl;
  std::cout << "Blink period:              " << config->getBlinkPeriod()            << std::endl;
  std::cout << "Timeout:                   " << config->getTimeout()                << std::endl;

  std::cout << "Modeline control channel:  " << config->getModelineControlChannel() << std::endl;

  std::cout << "Text pointer path:         " << config->getTextPointerPath()        << std::endl;
  std::cout << "Data directory:            " << config->getDataDir()                << std::endl;




}

int test1(int argc, char* argv[])
{
  printSeparator("test1");

  ModelineConfig config;

  printModelineConfig(&config);

  return 0;
}

int test2(int argc, char* argv[])
{
  printSeparator("test2");

  ModelineConfig config;

  config.readConfig("/tmp/mw2_config");
  printModelineConfig(&config);

  return 0;
}


int test3(int argc, char* argv[])
{

  printSeparator("test3");

  ModelineConfig config;
  config.readConfig("/tmp/mw2_config");

  auto app = Gtk::Application::create(argc, argv, "modeline.app");

  ModelineWin window(&config);
  if(window.initialize())
  {
    std::cout << "Failed to initialize ... exiting" << std::endl;
    return 1;
  }
  if(window.write_pid()) return 1;
  window.start_listen();

  //Shows the window and returns when it is closed.
  return app->run(window);
}
/*
int test4(int argc, char* argv[])
{
  std::cout << (int)get_red_value("010203") << std::endl;
  std::cout << (int)get_green_value("010203") << std::endl;
  std::cout << (int)get_blue_value("010203") << std::endl;
  std::cout << (int)get_alpha_value("01020304") << std::endl;

  return 0;
}
*/
int test5(int argc, char* argv[])
{
  FilesQueue my_queue;
  if(my_queue.readDir("/tmp/teksty"))
  {
    std::cout << "Couldn't read directory" << std::endl;
    return 1;
  }
  my_queue.print();

  my_queue.setAtChar('a');
  my_queue.print();
  //my_queue.get_frame();

  return 0;
}
/*
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
*/
//#################################################

int main(int argc, char* argv[])
{
  return test3(argc, argv);
}
