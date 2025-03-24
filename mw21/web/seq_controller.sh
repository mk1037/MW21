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


# sequencer controller

. ./scripts_config.sh

# e.g   switch_proxy "PR3000" "ON"
switch_proxy()
{
  PROXY_INSTRUCTION_PATH=$(get_config_variable "$1_instruction")
  PROXY_PID_PATH=$(get_config_variable "$1_pid")
  PROXY_PID=$(head -1 $PROXY_PID_PATH)
  
  echo $2 > $PROXY_INSTRUCTION_PATH
  kill -10 "$PROXY_PID"
}

SC_INSTRUCTION=$(get_config_variable "seq_controller_instruction")
TEXT_POINTER_PATH=$(get_config_variable "textPointerPath")
CHOOSER_INSTRUCTION_PATH=$(get_config_variable "chooser_instruction_path")
CHOOSER_PID_PATH=$(get_config_variable "chooser_pid_path")

INSTRUCTION_FOR_MODELINE=$(get_config_variable "modeline_instruction")
THE_MODELINE_PID_PATH=$(get_config_variable "modeline_pid")
MODELINE_PID=$(head -1 $THE_MODELINE_PID_PATH)

echo "Seq controller run ..."

ACTION=$(head -1 $SC_INSTRUCTION)

if [ $ACTION == "LOAD" ]; then
  echo "-------------------------------------"

  echo "IDLE" > $INSTRUCTION_FOR_MODELINE

  # check for anything playing
  echo "checking for existing ANY midi players"
  EXISTING_PLAYER=$(ps -u $(whoami) | grep -e "$PLAYER3000_SCRIPT")
  echo "ANY EXISTING_PLAYER midi are $EXISTING_PLAYER"
  if [[ $EXISTING_PLAYER != "" ]]; then
    echo "SOMETHING IS PLAYING ... NOT LOADING"
    exit 1
  fi

  echo "Will LOAD a file"
  ITEM_NAME=$(cat $SC_INSTRUCTION | sed -n 2p)
  echo "The item is \"$ITEM_NAME\""

  # check for K3Y
  match_code=$(echo $ITEM_NAME | grep -i K3Y)
  echo "match code is $match_code"
  if [ ! -z $match_code ] ; then
    echo "switching proxies to 3000 mode"
    switch_proxy "PR3000" "ON"
    echo "K3Y" > $INSTRUCTION_FOR_MODELINE
  fi

  echo $ITEM_NAME > $TEXT_POINTER_PATH

  echo "LOAD" > $CHOOSER_INSTRUCTION_PATH
  echo $ITEM_NAME >> $CHOOSER_INSTRUCTION_PATH
  CHOOSER_PID=$(head -1 $CHOOSER_PID_PATH)
  kill -10 "$CHOOSER_PID"

  echo "Updating modeline after loading"
  kill -10 "$MODELINE_PID"

fi

if [ $ACTION == "PLAY" ]; then
  echo "-------------------------------------"

  echo "Will PLAY a file"
  # action
  ITEM_TO_PLAY=$(head -1 $TEXT_POINTER_PATH)
  echo "$ITEM_TO_PLAY"
  
  # check for K3Y
  play_match_code=$(echo $ITEM_TO_PLAY | grep -i K3Y)
  echo "player match code is $play_match_code"
  if [ ! -z $play_match_code ] ; then

    echo "checking for existing players 3000"
    EXISTING_PLAYER_3000=$(ps -u $(whoami) | grep $PLAYER3000_SCRIPT)
    echo "EXISTING_PLAYER_3000 are $EXISTING_PLAYER_3000"

    echo "checking for existing wave players"
    EXISTING_PLAYER_WAVE=$(ps -u $(whoami) | grep vlc)
    echo "EXISTING_PLAYER_WAVE are $EXISTING_PLAYER_WAVE"

    if [[ $EXISTING_PLAYER_3000 == "" && $EXISTING_PLAYER_WAVE == "" ]]; then
      echo "RUNNING PLAYER3000 !!!"
      PLAYER_PID=$(head -1 $PLAYER3000_TRAP_PID_PATH)
      kill -10 $PLAYER_PID
    else
      echo "SOMETHING IS PLAYING ... NOT PLAY 3000"
    fi
  fi

fi

if [ $ACTION == "STOP1" ]; then
  STOPPER1_PID=$(head -1 $STOPPER3000_TRAP_PID_PATH)
  kill -10 $STOPPER1_PID
fi


