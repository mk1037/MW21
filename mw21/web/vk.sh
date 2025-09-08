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

VK_LABEL="Virtual Keyboard"

sleep 0.3

vkeybd &

sleep 0.5

VK_CLIENT=$( aconnect -l | grep client | grep -e "Virtual Keyboard" | awk '{ result=$2; gsub(":", "", result); print result; }' )

MAIN_PR_CLIENT=$(get_client $MAIN_PR_CLIENT_LABEL)
MAIN_PR_PORT_WRITE=$(get_midi_port $MAIN_PR_PORT_WRITE_LABEL)

aconnect $VK_CLIENT:0 $MAIN_PR_CLIENT:$MAIN_PR_PORT_WRITE

echo "When ready to close this window - press \"Ctrl+c\""

while true; do
  read variable1
done
