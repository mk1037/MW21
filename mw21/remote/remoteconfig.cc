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

#include "remoteconfig.h"
#include <glibmm/keyfile.h>

RemoteConfig::RemoteConfig()
{
  remoteInstructionPath = "/tmp/remote_instruction";
  remotePidPath         = "/tmp/remote_pid";
  modelineControlChannel = 1;
  noteLoad               = 82;
  notePlay               = 80;
  noteStop               = 73;
}

Glib::ustring RemoteConfig::getRemoteInstructionPath()
{
  return remoteInstructionPath;
}

Glib::ustring RemoteConfig::getRemotePidPath()
{
  return remotePidPath;
}

unsigned int RemoteConfig::getNoteLoad()
{
  return noteLoad;
}

unsigned int RemoteConfig::getNotePlay()
{
  return notePlay;
}

unsigned int RemoteConfig::getNoteStop()
{
  return noteStop;
}

unsigned int RemoteConfig::getModelineControlChannel()
{
  return modelineControlChannel;
}

int RemoteConfig::readConfig(Glib::ustring filename)
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

  modelineControlChannel = atoi(keyfile.get_value("MAIN", "modelineControlChannel").c_str());

  remoteInstructionPath = keyfile.get_value("MAIN", "remote_instruction_path");
  remotePidPath = keyfile.get_value("MAIN", "remote_pid_path");

  return 0;
}
