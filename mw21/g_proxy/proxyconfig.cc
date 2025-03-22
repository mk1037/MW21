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

#include "proxyconfig.h"
#include <glibmm/keyfile.h>

ProxyConfig::ProxyConfig(Glib::ustring p_label)
{
  proxyLabel = p_label;
  instructionPath = "/tmp/" + p_label + "_instruction";
  pidPath = "/tmp/" + p_label + "_pid";
  textChannel = 0;
  controlChannel = 1;
  noteGEQ                = 1;
  noteLT                 = 2;
  velGEQ            = 1;
  velLT             = 2;
  noteBack            = 5;
  velBack             = 1;
  noteHome            = 9;
  velHome             = 1;
}

Glib::ustring ProxyConfig::getInstructionPath()
{
  return instructionPath;
}

Glib::ustring ProxyConfig::getProxyLabel()
{
  return proxyLabel;
}

unsigned int ProxyConfig::getTextChannel()
{
  return textChannel;
}

unsigned int ProxyConfig::getControlChannel()
{
  return controlChannel;
}


unsigned int ProxyConfig::getNoteGEQ()
{
  return noteGEQ;
}

unsigned int ProxyConfig::getNoteLT()
{
  return noteLT;
}

unsigned int ProxyConfig::getVelGEQ()
{
  return velGEQ;
}

unsigned int ProxyConfig::getVelLT()
{
  return velLT;
}


unsigned int ProxyConfig::getNoteBack()
{
  return noteBack;
}

unsigned int ProxyConfig::getVelBack()
{
  return velBack;
}

unsigned int ProxyConfig::getNoteHome()
{
  return noteHome;
}

unsigned int ProxyConfig::getVelHome()
{
  return velHome;
}




Glib::ustring ProxyConfig::getPidPath()
{
  return pidPath;
}

int ProxyConfig::readConfig(Glib::ustring filename)
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
  controlChannel = atoi(keyfile.get_value("MAIN", "modelineControlChannel").c_str());

  noteGEQ = atoi(keyfile.get_value("MAIN", "noteGEQ").c_str());
  noteLT = atoi(keyfile.get_value("MAIN", "noteLT").c_str());
  velGEQ = atoi(keyfile.get_value("MAIN", "velGEQ").c_str());
  velLT = atoi(keyfile.get_value("MAIN", "velLT").c_str());

  noteBack = atoi(keyfile.get_value("MAIN", "noteBack").c_str());
  velBack = atoi(keyfile.get_value("MAIN", "velBack").c_str());

  noteHome = atoi(keyfile.get_value("MAIN", "noteHome").c_str());
  velHome = atoi(keyfile.get_value("MAIN", "velHome").c_str());

  instructionPath = keyfile.get_value("MAIN", proxyLabel + "_instruction");
  pidPath = keyfile.get_value("MAIN", proxyLabel + "_pid");

  return 0;
}
