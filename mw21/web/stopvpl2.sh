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

EXISTING_PLAYER=$(ps -u $(whoami) | grep -e "$PLAYER3000_SCRIPT")
PLAY_NEXT="false"


if [[ $1 == "next" ]]; then
  PLAY_NEXT="true"
fi

if [[ $EXISTING_PLAYER != "" ]]; then
  echo "false"
  exit 1
fi

if [[ $PLAY_NEXT != "true" ]]; then
  ps -ef | grep player_vpl2 | grep -v grep |  awk '{print $2;}' | xargs kill -9
fi

ps -ef | grep -e "vlc" | grep -v grep |  awk '{print $2;}' | xargs kill -9
sleep 1

echo "true"
exit 0
