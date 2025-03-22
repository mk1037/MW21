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

#ifndef PROXYCONFIG_H
#define PROXYCONFIG_H

#include <gtkmm.h>
#include <iostream>

class ProxyConfig
{
public:
  ProxyConfig(Glib::ustring p_label);

private:
  Glib::ustring proxyLabel;

  Glib::ustring instructionPath;
  Glib::ustring pidPath;

  unsigned int textChannel;
  unsigned int controlChannel;

  unsigned int noteGEQ;
  unsigned int noteLT;
  unsigned int velGEQ;
  unsigned int velLT;
  unsigned int noteBack;
  unsigned int velBack;
  unsigned int noteHome;
  unsigned int velHome;


public:

  Glib::ustring getInstructionPath();
  Glib::ustring getPidPath();

  unsigned int getTextChannel();
  unsigned int getControlChannel();

  unsigned int getNoteGEQ();
  unsigned int getNoteLT();
  unsigned int getVelGEQ();
  unsigned int getVelLT();

  unsigned int getNoteBack();
  unsigned int getVelBack();

  unsigned int getNoteHome();
  unsigned int getVelHome();

  Glib::ustring getProxyLabel();
  int readConfig(Glib::ustring filename);
  
};

#endif // PROXYCONFIG_H
