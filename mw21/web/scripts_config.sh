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

get_config_variable()
{
  cat $MAIN_PREFIX/mw2_config | grep $1 | awk -F= '{gsub("[ \t]",""); print $2;}'
}

get_client()
{
  CLIENT_SED_INDEX=1
  if [ $# -gt 1 ]; then
    CLIENT_SED_INDEX=$2
  fi
  aconnect -l | grep client | grep $1 | sed -n "$CLIENT_SED_INDEX"p | awk '{ result=$2; gsub(":", "", result); print result; }'
}

get_midi_port()
{
  aconnect -l | grep $1 | awk '{ print $1; }'
}

stop_process()
{
  for l_pid in $(ps -u $(whoami) | grep $1 | awk '{ print $1; }'); do
    kill -2 $l_pid
    sleep 0.5
  done
}

get_virtual_client() ## HARDCODED "Virtual" and "1-0" strings
{
  aconnect -l | grep client | grep "Virtual" | grep -e "\-0" | awk '{ result=$2; gsub(":", "", result); print result; }'
}

. ./specific_variables.sh

################################################################
##################### SCRIPT VARIABLES #########################
################################################################

DATA_DIRECTORY=$(get_config_variable "dataDir")

DATA_CHECK_DIFF_LEFT="$COMMON_DIRECTORY/data_check_left"
DATA_CHECK_DIFF_RIGHT="$COMMON_DIRECTORY/data_check_right"

SEQ_CONTROLLER="$MAIN_PREFIX/web/seq_controller.sh"

SC_TRAP_SCRIPT="sc_trap.sh"
SC_TRAP_PATH="$MAIN_PREFIX/web/$SC_TRAP_SCRIPT"
SC_TRAP_PID_PATH=$(get_config_variable "sc_trap_pid_path")


PLAYER3000_SCRIPT="player3000.sh"
PLAYER3000_PATH="$MAIN_PREFIX/web/$PLAYER3000_SCRIPT"

PLAYER3000_TRAP_SCRIPT="pl3000_trap.sh"
PLAYER3000_TRAP_PATH="$MAIN_PREFIX/web/$PLAYER3000_TRAP_SCRIPT"
PLAYER3000_TRAP_PID_PATH="$COMMON_DIRECTORY/player3000_trap_pid"

STOPPER3000_SCRIPT="stopper3000.sh"
STOPPER3000_PATH="$MAIN_PREFIX/web/$STOPPER3000_SCRIPT"

STOPPER3000_TRAP_SCRIPT="st3000_trap.sh"
STOPPER3000_TRAP_PATH="$MAIN_PREFIX/web/$STOPPER3000_TRAP_SCRIPT"
STOPPER3000_TRAP_PID_PATH="$COMMON_DIRECTORY/stopper3000_trap_pid"

DISPLAY_BIN="midi_display"
MODELINE_BIN="midi_modeline"
CHOOSER_BIN="midi_chooser"
REMOTE_BIN="midi_remote"

MAIN_PR_BIN="MAIN_PR"
PR3000_BIN="PR3000"

MIDI_THROUGH_1_CLIENT_DECSRIPTOR="14:0"

DISPLAY_CLIENT_LABEL="MIDI_Display"
MODELINE_CLIENT_LABEL="Modeline"
CHOOSER_CLIENT_LABEL="Chooser"
REMOTE_CLIENT_LABEL="Remote"

MAIN_PR_CLIENT_LABEL="MAIN_PR"
PR3000_CLIENT_LABEL="PR3000"

DISPLAY_PORT_WRITE_LABEL="Display_write"
MODELINE_PORT_WRITE_LABEL="Modeline_write"
CHOOSER_PORT_READ_LABEL="Chooser_read"
REMOTE_PORT_READ_LABEL="Remote_read"
MAIN_PR_PORT_WRITE_LABEL="MAIN_PR_write"
MAIN_PR_PORT_READ_LABEL="MAIN_PR_read"
PR3000_PORT_WRITE_LABEL="PR3000_write"
PR3000_PORT_READ_LABEL="PR3000_read"


DISPLAY_PATH="$MAIN_PREFIX/display/$DISPLAY_BIN"
MODELINE_PATH="$MAIN_PREFIX/modeline/$MODELINE_BIN"
CHOOSER_PATH="$MAIN_PREFIX/chooser/$CHOOSER_BIN"
REMOTE_PATH="$MAIN_PREFIX/remote/$REMOTE_BIN"

MAIN_PR_PATH="$MAIN_PREFIX/g_proxy/$MAIN_PR_BIN"
PR3000_PATH="$MAIN_PREFIX/g_proxy/$PR3000_BIN"

# web related variables

MW2_WEB_DIR="$MAIN_PREFIX/web"

EXEC_PLAYER_NAME_PATH="$MW2_WEB_DIR/exec_player_name"

PLAYVPL2_SCRIPT="player_vpl2.sh"
PLAYVPL2_PATH=$MW2_WEB_DIR/$PLAYVPL2_SCRIPT

STOPVPL2_SCRIPT="stopvpl2.sh"
STOPVPL2_PATH=$MW2_WEB_DIR/$STOPVPL2_SCRIPT

SIGNAL_PLAYVPL2_SCRIPT="signal_playvpl2.sh"
SIGNAL_PLAYVPL2_PATH=$MW2_WEB_DIR/$SIGNAL_PLAYVPL2_SCRIPT

PLAYVPL2_ON_SIGNAL_SCRIPT="playvpl2_on_signal.sh"
PLAYVPL2_ON_SIGNAL_PATH=$MW2_WEB_DIR/$PLAYVPL2_ON_SIGNAL_SCRIPT

PLACEV2_SCRIPT="placev2.sh"
PLACEV2_PATH=$MW2_WEB_DIR/$PLACEV2_SCRIPT

PLAYVPL2_TRAP_SCRIPT="playvpl2_trap.sh"
PLAYVPL2_TRAP_PATH=$MW2_WEB_DIR/$PLAYVPL2_TRAP_SCRIPT

PLAYVPL2_TRAP_PID_PATH="$COMMON_DIRECTORY/playvpl2_trap_pid" ## SYNCHRONIZED !!!
PLAYVPL2_ARGS_PATH="$COMMON_DIRECTORY/playvpl2_args"

PLAYVPL2_LOGS_PATH="$MW2_WEB_DIR/playvpl2_log"
PLAYVPL2_PLAYLIST_TMP="$MW2_WEB_DIR/playlist_tmp"
PLAYVPL2_PLAYLIST="$MW2_WEB_DIR/playlist"
PLAYVPL2_PLAYLIST_TO_DISPLAY="$MW2_WEB_DIR/playlist_to_display"

REMOTE_INSTRUCTION_PATH=$(get_config_variable "remote_instruction_path")
REMOTE_PID_FILE_PATH=$(get_config_variable "remote_pid_path")

MODELINE_INSTRUCTION_PATH=$(get_config_variable "modeline_instruction")
MODELINE_PID_FILE_PATH=$(get_config_variable "modeline_pid")

DEFAULT_VOLUME_PATH="$COMMON_DIRECTORY/default_volume"
EQ_SETTINGS_PATH="$COMMON_DIRECTORY/eq_settings"

VLCRC_PATH=~/.config/vlc/vlcrc
VLC_PORT="30000"
VLC_PASSWORD="vlcpasswd"

# echo "SC_TRAP_PID_PATH = \"$SC_TRAP_PID_PATH\""

WINDOWS_WORKSPACE_NR="0"
WINDOWS_WORKSPACE_NR2="3"


