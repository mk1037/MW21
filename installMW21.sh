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

#1 - name
#2 - command
#3 - icon path

createActivator()
{
  [ -f $MW21_DESKTOP_DIR/$1.desktop ] && rm $MW21_DESKTOP_DIR/$1.desktop

  if [ $MW21_DESKTOP_ENVIRONMENT == "xfce" ]; then
    printf "[Desktop Entry]\nVersion=1.0\nType=Application\nName=%s\nComment=\nExec=$MW21_TERMINAL_BIN --working-directory=$MW2_DIR/mw21/web -x ./%s\nIcon=%s\nPath=\nTerminal=false\nStartupNotify=false\n" $1 $2 $3 > $MW21_DESKTOP_DIR/$1.desktop
  fi

  if [ $MW21_DESKTOP_ENVIRONMENT == "mate" ]; then
    printf "#!/usr/bin/env xdg-open\n[Desktop Entry]\nVersion=1.0\nType=Application\nTerminal=false\nExec=$MW21_TERMINAL_BIN --working-directory=$MW2_DIR/mw21/web -x ./%s\nName=%s\nIcon=%s\n" $2 $1 $3 > $MW21_DESKTOP_DIR/$1.desktop
  fi

  [ -f $MW21_DESKTOP_DIR/$1.desktop ] && chmod 755 $MW21_DESKTOP_DIR/$1.desktop
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
  wget \
  meld

message "Compiling MW21"

cd $MW2_DIR/mw21/chooser/ ; make ; \
cd $MW2_DIR/mw21/display/ ; make ; \
cd $MW2_DIR/mw21/g_proxy/ ; make ; \
cd $MW2_DIR/mw21/modeline/ ; make ; \
cd $MW2_DIR/mw21/remote/ ; make ; \
cd $MW2_DIR

message "Determine desktop environment"

MW21_DESKTOP_ENVIRONMENT="mate"
MW21_TERMINAL_BIN="mate-terminal"

echo $XDG_CURRENT_DESKTOP | grep -q -i xfce
MW21_IS_XFCE=$?
if [ $MW21_IS_XFCE -eq 0 ]; then
  MW21_DESKTOP_ENVIRONMENT="xfce"
fi

if [ $MW21_DESKTOP_ENVIRONMENT == "xfce" ]; then
  MW21_TERMINAL_BIN="xfce4-terminal"
fi

message "Modifying configs"

find $MW2_DIR/mw21/configs/default -maxdepth 1 -type f | xargs sed -i "s/USERNAME/${USERNAME}/g"

sed -i "s/MW21TERMINAL/${MW21_TERMINAL_BIN}/g" $MW2_DIR/mw21/configs/default/specific_variables.sh

message "Creating symlink to karaoke"

[ -d $MW2_DIR/collections ] || mkdir $MW2_DIR/collections
[ -L $MW2_DIR/karaoke_link ] && rm $MW2_DIR/karaoke_link
ln -s $MW2_DIR/collections/example $MW2_DIR/karaoke_link


message "Creating desktop activators"

MW21_DESKTOP_DIR=$(xdg-user-dir DESKTOP)

createActivator "runMW21" run_mw21.sh $MW2_DIR/mw21/icons/runMW21.png
createActivator "stopMW21" stop_mw21.sh $MW2_DIR/mw21/icons/stopMW21.png
createActivator "reconnectMW21" reconnect.sh $MW2_DIR/mw21/icons/reconnectMW21.png
createActivator "keyboardMW21" vk.sh $MW2_DIR/mw21/icons/keyboardMW21.png
createActivator "placeMW21" place_windows.sh $MW2_DIR/mw21/icons/placeMW21.png
#createActivator "collectionMW21" collection.sh $MW2_DIR/mw21/icons/collectionMW21.png

