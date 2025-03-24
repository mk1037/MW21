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

. ./scripts_config.sh
. ./xy.sh

sleep 2.8

export DISPLAY=":0"

VLC_TYPE=$1

VLC_HANDLE=$( wmctrl -l | grep "VLC media player" | awk '{print $1;}' )
IS_VLC_HANDLE=$?

if [ $IS_VLC_HANDLE == 0 ]; then
  if [ $VLC_TYPE != "music" ]; then
    wmctrl -i -r $VLC_HANDLE -e 0,$VLC_VIDEO_X,$VLC_VIDEO_Y,$VLC_VIDEO_SIZE_X,$VLC_VIDEO_SIZE_Y
  fi
fi

