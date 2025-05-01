#!/bin/bash

# Copyright (C) 2017-2025 Marek Momot
#
# This file is part of MW21.
#
# MW21 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# MW21 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MW21.  If not, see <http://www.gnu.org/licenses/>.


# This script was tested on Linux Lite 7.2 x86_64 

message()
{
  echo ""
  echo "---------------------------------------------"
  echo $1
  echo "---------------------------------------------"
}

MW2_DIR=$(pwd)
USERNAME=$(whoami)

message "Installing packages"

sudo apt-get install -y build-essential \
  pkg-config \
  libgtkmm-3.0-dev \
  libasound2-dev \
  libfreetype-dev \
  git \
  wmctrl \
  vlc \
  bc \
  pmidi \
  a2jmidid \
  gmidimonitor \
  mc \
  vkeybd \
  meld

message "Compiling MW21"

cd $MW2_DIR/mw21/chooser/ ; make ; \
cd $MW2_DIR/mw21/display/ ; make ; \
cd $MW2_DIR/mw21/g_proxy/ ; make ; \
cd $MW2_DIR/mw21/modeline/ ; make ; \
cd $MW2_DIR/mw21/remote/ ; make ; \
cd $MW2_DIR

message "Modifying configs"

find $MW2_DIR/mw21/configs/default -maxdepth 1 -type f | xargs sed -i "s/USERNAME/${USERNAME}/g"

message "Creating symlink to karaoke"

[ -L $MW2_DIR/karaoke_link ] && rm $MW2_DIR/karaoke_link
ln -s $MW2_DIR/karaoke $MW2_DIR/karaoke_link


