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

export DISPLAY=":0"

DISPLAY_WIN_HANDLE=$(wmctrl -l | grep Display | head -1 | awk '{print $1;}')
CHOOSER_WIN_HANDLE=$(wmctrl -l | grep Chooser | head -1 | awk '{print $1;}')
REMOTE_WIN_HANDLE=$(wmctrl -l | grep Remote | head -1 | awk '{print $1;}')
MODELINE_WIN_HANDLE=$(wmctrl -l | grep Modeline | head -1 | awk '{print $1;}')
MAIN_PR_WIN_HANDLE=$(wmctrl -l | grep MAIN_PR | head -1 | awk '{print $1;}')
PR3000_WIN_HANDLE=$(wmctrl -l | grep PR3000 | head -1 | awk '{print $1;}')

wmctrl -i -r $MAIN_PR_WIN_HANDLE -t $WINDOWS_WORKSPACE_NR
echo "wmctrl -i -r $MAIN_PR_WIN_HANDLE -e 0,$MAIN_PR_WIN_X,$MAIN_PR_WIN_Y,$MAIN_PR_WIN_WIDTH,$MAIN_PR_WIN_HEIGHT"
wmctrl -i -r $MAIN_PR_WIN_HANDLE -e 0,$MAIN_PR_WIN_X,$MAIN_PR_WIN_Y,$MAIN_PR_WIN_WIDTH,$MAIN_PR_WIN_HEIGHT

sleep $DEFAULT_TIMEOUT
wmctrl -i -r $PR3000_WIN_HANDLE -t $WINDOWS_WORKSPACE_NR2
wmctrl -i -r $PR3000_WIN_HANDLE -e 0,$PR3000_WIN_X,$PR3000_WIN_Y,$PR3000_WIN_WIDTH,$PR3000_WIN_HEIGHT
sleep $DEFAULT_TIMEOUT
wmctrl -i -r $CHOOSER_WIN_HANDLE -t $WINDOWS_WORKSPACE_NR2
wmctrl -i -r $CHOOSER_WIN_HANDLE -e 0,$CHOOSER_WIN_X,$CHOOSER_WIN_Y,$CHOOSER_WIN_WIDTH,$CHOOSER_WIN_HEIGHT
sleep $DEFAULT_TIMEOUT
wmctrl -i -r $REMOTE_WIN_HANDLE -t $WINDOWS_WORKSPACE_NR2
wmctrl -i -r $REMOTE_WIN_HANDLE -e 0,$REMOTE_WIN_X,$REMOTE_WIN_Y,$REMOTE_WIN_WIDTH,$REMOTE_WIN_HEIGHT

sleep $DEFAULT_TIMEOUT
wmctrl -i -r $DISPLAY_WIN_HANDLE -t $WINDOWS_WORKSPACE_NR
wmctrl -i -r $DISPLAY_WIN_HANDLE -e 0,$DISPLAY_WIN_X,$DISPLAY_WIN_Y,$DISPLAY_WIN_WIDTH,$DISPLAY_WIN_HEIGHT
sleep $DEFAULT_TIMEOUT
wmctrl -i -r $MODELINE_WIN_HANDLE -t $WINDOWS_WORKSPACE_NR
wmctrl -i -r $MODELINE_WIN_HANDLE -e 0,$MODELINE_WIN_X,$MODELINE_WIN_Y,$MODELINE_WIN_WIDTH,$MODELINE_WIN_HEIGHT

sleep $DEFAULT_TIMEOUT

COUNTER_VAR=0

for window_id in $(wmctrl -l | grep -e "Terminal" | awk '{ print $1;}' ); do
  TERMINAL_WIN_X=`expr $TERMINAL_ORIGIN_X + $TERMINAL_OFFSET_X \* $COUNTER_VAR`
  TERMINAL_WIN_Y=`expr $TERMINAL_ORIGIN_Y + $TERMINAL_OFFSET_Y \* $COUNTER_VAR`

  wmctrl -i -r $window_id -t 2
  wmctrl -i -r $window_id -e 0,$TERMINAL_WIN_X,$TERMINAL_WIN_Y,$TERMINAL_WIN_WIDTH,$TERMINAL_WIN_HEIGHT

  COUNTER_VAR=`expr $COUNTER_VAR + 1`
done

sleep $DEFAULT_TIMEOUT
wmctrl -i -a $MAIN_PR_WIN_HANDLE

sleep $DEFAULT_TIMEOUT
wmctrl -i -a $MODELINE_WIN_HANDLE

sleep $DEFAULT_TIMEOUT
wmctrl -i -a $DISPLAY_WIN_HANDLE

