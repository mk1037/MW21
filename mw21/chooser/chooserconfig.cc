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

#include "chooserconfig.h"
#include <glibmm/keyfile.h>

ChooserConfig::ChooserConfig()
{
  chooserInstructionPath = "/tmp/chooser_instruction";
  chooserPidPath         = "/tmp/chooser_pid";
  textChannel            = 0;
  noteRead               = 1;
  velRead                = 4;
  noteTheme1             = 6;
  velTheme1              = 1;
  noteTheme2             = 7;
  velTheme2              = 1;
  noteTheme3             = 8;
  velTheme3              = 1;
  noteHome               = 9;
  velHome                = 1;
  notePCKbdEnable        = 10; // vel positive
  notePCKbdDisable       = 11; // vel positive
}

Glib::ustring ChooserConfig::getChooserInstructionPath()
{
  return chooserInstructionPath;
}

Glib::ustring ChooserConfig::getChooserPidPath()
{
  return chooserPidPath;
}

unsigned int ChooserConfig::getNoteRead()
{
  return noteRead;
}

unsigned int ChooserConfig::getVelRead()
{
  return velRead;
}

unsigned int ChooserConfig::getNoteHome()
{
  return noteHome;
}

unsigned int ChooserConfig::getVelHome()
{
  return velHome;
}

unsigned int ChooserConfig::getTextChannel()
{
  return textChannel;
}

unsigned int ChooserConfig::getNoteTheme1()
{
  return noteTheme1;
}

unsigned int ChooserConfig::getVelTheme1()
{
  return velTheme1;
}

unsigned int ChooserConfig::getNoteTheme2()
{
  return noteTheme2;
}

unsigned int ChooserConfig::getVelTheme2()
{
  return velTheme2;
}

unsigned int ChooserConfig::getNoteTheme3()
{
  return noteTheme3;
}

unsigned int ChooserConfig::getVelTheme3()
{
  return velTheme3;
}

unsigned int ChooserConfig::getNotePCKbdEnable()
{
  return notePCKbdEnable;
}

unsigned int ChooserConfig::getNotePCKbdDisable()
{
  return notePCKbdDisable;
}

int ChooserConfig::readConfig(Glib::ustring filename)
{
  bool result = false;
  Glib::KeyFile keyfile;

  try
  {
    result = keyfile.load_from_file(filename);
  }
  catch (Glib::Error ex)
  {
    std::cout << "Exception cought during reading config" << std::endl;
  }

  if(!result) return 1;

  textChannel = atoi(keyfile.get_value("MAIN", "channel").c_str());

  noteRead = atoi(keyfile.get_value("MAIN", "noteRead").c_str());
  velRead = atoi(keyfile.get_value("MAIN", "velRead").c_str());

  noteTheme1 = atoi(keyfile.get_value("MAIN", "noteTheme1").c_str());
  velTheme1 = atoi(keyfile.get_value("MAIN", "velTheme1").c_str());

  noteTheme2 = atoi(keyfile.get_value("MAIN", "noteTheme2").c_str());
  velTheme2 = atoi(keyfile.get_value("MAIN", "velTheme2").c_str());

  noteTheme3 = atoi(keyfile.get_value("MAIN", "noteTheme3").c_str());
  velTheme3 = atoi(keyfile.get_value("MAIN", "velTheme3").c_str());

  noteHome = atoi(keyfile.get_value("MAIN", "noteHome").c_str());
  velHome = atoi(keyfile.get_value("MAIN", "velHome").c_str());

  notePCKbdEnable = atoi(keyfile.get_value("MAIN", "notePCKbdEnable").c_str());
  notePCKbdDisable = atoi(keyfile.get_value("MAIN", "notePCKbdDisable").c_str());

  chooserInstructionPath = keyfile.get_value("MAIN", "chooser_instruction_path");
  chooserPidPath = keyfile.get_value("MAIN", "chooser_pid_path");

  return 0;
}
