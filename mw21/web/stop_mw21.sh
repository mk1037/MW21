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

printf "Thank you for using MW21!\n\n"

stop_process $DISPLAY_BIN
stop_process $MODELINE_BIN
stop_process $CHOOSER_BIN
stop_process $REMOTE_BIN

stop_process $MAIN_PR_BIN
stop_process $PR3000_BIN

stop_process $SC_TRAP_SCRIPT
stop_process $PLAYER3000_TRAP_SCRIPT
stop_process $STOPPER3000_TRAP_SCRIPT

stop_process $PLAYVPL2_TRAP_SCRIPT
sleep 0.2

PLAYVPL2_TRAP_PID_TO_STOP=$(head -1 $PLAYVPL2_TRAP_PID_PATH)
kill -9 $PLAYVPL2_TRAP_PID_TO_STOP

sleep 0.5
