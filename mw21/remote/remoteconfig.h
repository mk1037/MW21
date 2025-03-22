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

#ifndef REMOTECONFIG_H
#define REMOTECONFIG_H

#include <gtkmm.h>
#include <iostream>

class RemoteConfig
{
public:
  RemoteConfig();

private:
  Glib::ustring remoteInstructionPath; // LOAD >>, PLAY, STOP
  Glib::ustring remotePidPath;

  unsigned int modelineControlChannel;

  unsigned int noteLoad;
  unsigned int notePlay;
  unsigned int noteStop;

public:

  Glib::ustring getRemoteInstructionPath();
  Glib::ustring getRemotePidPath();

  unsigned int getModelineControlChannel();

  unsigned int getNoteLoad();
  unsigned int getNotePlay();
  unsigned int getNoteStop();

  int readConfig(Glib::ustring filename);
  
};

#endif // REMOTECONFIG_H
