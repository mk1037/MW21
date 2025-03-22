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

#ifndef CHOOSERCONFIG_H
#define CHOOSERCONFIG_H

#include <gtkmm.h>
#include <iostream>

class ChooserConfig
{
public:
  ChooserConfig();

private:
  Glib::ustring chooserInstructionPath; // LOAD, PLAY
  Glib::ustring chooserPidPath;

  unsigned int textChannel;

  unsigned int noteRead;
  unsigned int velRead;

  unsigned int noteTheme1;
  unsigned int velTheme1;
  unsigned int noteTheme2;
  unsigned int velTheme2;
  unsigned int noteTheme3;
  unsigned int velTheme3;

  unsigned int notePCKbdEnable;
  unsigned int notePCKbdDisable;

  unsigned int noteHome;
  unsigned int velHome;

public:

  Glib::ustring getChooserInstructionPath();
  Glib::ustring getChooserPidPath();

  unsigned int getTextChannel();

  unsigned int getNoteRead();
  unsigned int getVelRead();

  unsigned int getNoteTheme1();
  unsigned int getVelTheme1();

  unsigned int getNoteTheme2();
  unsigned int getVelTheme2();

  unsigned int getNoteTheme3();
  unsigned int getVelTheme3();

  unsigned int getNotePCKbdEnable();
  unsigned int getNotePCKbdDisable();

  unsigned int getNoteHome();
  unsigned int getVelHome();

  int readConfig(Glib::ustring filename);
  
};

#endif // CHOOSERCONFIG_H
