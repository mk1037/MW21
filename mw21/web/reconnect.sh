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

echo "Connecting software clients"

MIDI_DISPLAY_CLIENT=$(get_client $DISPLAY_CLIENT_LABEL)
MODELINE_CLIENT=$(get_client $MODELINE_CLIENT_LABEL)
CHOOSER_CLIENT=$(get_client $CHOOSER_CLIENT_LABEL)
REMOTE_CLIENT=$(get_client $REMOTE_CLIENT_LABEL)
MAIN_PR_CLIENT=$(get_client $MAIN_PR_CLIENT_LABEL)
PR3000_CLIENT=$(get_client $PR3000_CLIENT_LABEL)

# echo "DIsplay client is : $MIDI_DISPLAY_CLIENT"

DISPLAY_PORT_WRITE=$(get_midi_port $DISPLAY_PORT_WRITE_LABEL)
MODELINE_PORT_WRITE=$(get_midi_port $MODELINE_PORT_WRITE_LABEL)
CHOOSER_PORT_READ=$(get_midi_port $CHOOSER_PORT_READ_LABEL)
REMOTE_PORT_READ=$(get_midi_port $REMOTE_PORT_READ_LABEL)
MAIN_PR_PORT_WRITE=$(get_midi_port $MAIN_PR_PORT_WRITE_LABEL)
MAIN_PR_PORT_READ=$(get_midi_port $MAIN_PR_PORT_READ_LABEL)
PR3000_PORT_WRITE=$(get_midi_port $PR3000_PORT_WRITE_LABEL)
PR3000_PORT_READ=$(get_midi_port $PR3000_PORT_READ_LABEL)

echo "I AM HERE"

sleep $DEFAULT_TIMEOUT
aconnect $MAIN_PR_CLIENT:$MAIN_PR_PORT_READ $MODELINE_CLIENT:$MODELINE_PORT_WRITE


sleep $DEFAULT_TIMEOUT
aconnect $CHOOSER_CLIENT:$CHOOSER_PORT_READ $MIDI_DISPLAY_CLIENT:$DISPLAY_PORT_WRITE
sleep $DEFAULT_TIMEOUT
aconnect $MIDI_THROUGH_1_CLIENT_DECSRIPTOR $PR3000_CLIENT:$PR3000_PORT_WRITE
sleep $DEFAULT_TIMEOUT
aconnect $PR3000_CLIENT:$PR3000_PORT_READ $MIDI_DISPLAY_CLIENT:$DISPLAY_PORT_WRITE
sleep $DEFAULT_TIMEOUT
aconnect $REMOTE_CLIENT:$REMOTE_PORT_READ $MODELINE_CLIENT:$MODELINE_PORT_WRITE

echo "Connecting hardware"

MAIN_PR_CLIENT=$(get_client $MAIN_PR_CLIENT_LABEL)
MAIN_PR_PORT_WRITE=$(get_midi_port $MAIN_PR_PORT_WRITE_LABEL)

echo ""
echo "Hardware connected"

