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

echo "Here is 3000 player ..."
TEXT_POINTER_PATH=$(get_config_variable "textPointerPath")
TITLE_TO_PLAY=$(head -1 $TEXT_POINTER_PATH)

INSTRUCTION_FOR_MODELINE=$(get_config_variable "modeline_instruction")
THE_MODELINE_PID_PATH=$(get_config_variable "modeline_pid")
MODELINE_PID=$(head -1 $THE_MODELINE_PID_PATH)

echo "Read from textpath $TITLE_TO_PLAY"

# check for K3Y
player3000_match_code=$(echo $TITLE_TO_PLAY | grep -i K3Y)
echo "player3000 match code is $player3000_match_code"
if [ ! -z $player3000_match_code ] ; then
  echo "runnung seq"
  echo "PLAY" > $INSTRUCTION_FOR_MODELINE
  kill -10 $MODELINE_PID

  if [ -f "$DATA_DIRECTORY/bank_3/delay/$TITLE_TO_PLAY.delay" ]; then
    DELAY_VALUE=$(head -1 "$DATA_DIRECTORY/bank_3/delay/$TITLE_TO_PLAY.delay")
  else
    DELAY_VALUE=0
  fi
  EXEC_DELAY_VALUE=$DELAY_VALUE
#  EXEC_DELAY_VALUE=`expr $DELAY_VALUE + 0.2`
#  $STOPVPL2_PATH
# compute playlist and args for playvpl2 and execute "signal_playvpl2.sh" script (it is extra script which is ready already)
  echo $TITLE_TO_PLAY.mp3 > $PLAYVPL2_PLAYLIST
  echo "$DATA_DIRECTORY/bank_3/waves/ $MW2_WEB_DIR/mw2_web_log2 K3Y $EXEC_DELAY_VALUE" > $PLAYVPL2_ARGS_PATH
  $SIGNAL_PLAYVPL2_PATH
  pmidi -d 0 -p "14:0" "$DATA_DIRECTORY/bank_3/midi/$TITLE_TO_PLAY.mid"
  #sleep 20
fi

echo "STOP" >$INSTRUCTION_FOR_MODELINE
kill -10 $MODELINE_PID

