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

rm /tmp/mw2_config
cp ../mw2_config /tmp

./data_check.sh

if [ "$?" != "0" ]; then
  echo "Incorrect data, exiting midi ..."
  exit 1;
fi

$TERMINAL_BIN --title="remote_Terminal" -x $REMOTE_PATH &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="chooser_Terminal" -x $CHOOSER_PATH &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="mainpr_Terminal" -x $MAIN_PR_PATH -noborder &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="pr3000_Terminal" -x $PR3000_PATH &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="sc_trap_Terminal" -x $SC_TRAP_PATH &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="player3000_trap_Terminal" -x $PLAYER3000_TRAP_PATH &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="stopper3000_trap_Terminal" -x $STOPPER3000_TRAP_PATH &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="display_Terminal" -x $DISPLAY_PATH -noborder &
sleep $DEFAULT_TIMEOUT

$TERMINAL_BIN --title="modeline_Terminal" -x $MODELINE_PATH -noborder &
sleep $DEFAULT_TIMEOUT


echo "Processes midi started"


## HARDWARE CONNECTIONS
./reconnect.sh

echo "MIDI processes connected"

