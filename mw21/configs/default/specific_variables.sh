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


MAIN_PREFIX="/home/USERNAME/MW21/mw21"
COMMON_DIRECTORY="/home/USERNAME/common_files_mw21"

DEFAULT_TIMEOUT="0.5"
TERMINAL_BIN=xfce4-terminal

GLOBAL_DELAY=0.5
GLOBAL_MID_DELAY=0.5
BOTTOM_SEPARATOR_HEIGHT=8

DISPLAY_WIN_X=0
DISPLAY_WIN_Y=0
DISPLAY_AREA_HEIGHT=$(get_config_variable "areaHeight")
DISPLAY_WIN_HEIGHT=`expr $DISPLAY_AREA_HEIGHT \* 4`
DISPLAY_AREA_WIDTH=$(get_config_variable "areaWidth")
DISPLAY_WIN_WIDTH=$DISPLAY_AREA_WIDTH

MODELINE_AREA_HEIGHT=$(get_config_variable "modelineAreaHeight")
MODELINE_WIN_HEIGHT=`expr 2 \* $MODELINE_AREA_HEIGHT`
MODELINE_AREA_WIDTH=$(get_config_variable "modelineAreaWidth")
MODELINE_WIN_WIDTH=$MODELINE_AREA_WIDTH
MODELINE_WIN_X=$DISPLAY_WIN_X
MODELINE_WIN_Y=`expr $DISPLAY_WIN_Y + $DISPLAY_WIN_HEIGHT + $BOTTOM_SEPARATOR_HEIGHT`

PROXY_WIN_WIDTH=150
PROXY_WIN_HEIGHT=50

MAIN_PR_WIN_X=`expr 800 - $PROXY_WIN_WIDTH + $DISPLAY_WIN_X`
MAIN_PR_WIN_Y=`expr $MODELINE_WIN_Y + $MODELINE_WIN_HEIGHT - $PROXY_WIN_HEIGHT + 4`
MAIN_PR_WIN_WIDTH=$PROXY_WIN_WIDTH
MAIN_PR_WIN_HEIGHT=$PROXY_WIN_HEIGHT

PR3000_WIN_X=10
PR3000_WIN_Y=10
PR3000_WIN_WIDTH=$PROXY_WIN_WIDTH
PR3000_WIN_HEIGHT=$PROXY_WIN_HEIGHT

CHOOSER_WIN_X=10
CHOOSER_WIN_Y=100
CHOOSER_WIN_WIDTH=$PROXY_WIN_WIDTH
CHOOSER_WIN_HEIGHT=$PROXY_WIN_HEIGHT

REMOTE_WIN_X=10
REMOTE_WIN_Y=190
REMOTE_WIN_WIDTH=$PROXY_WIN_WIDTH
REMOTE_WIN_HEIGHT=$PROXY_WIN_HEIGHT

TERMINAL_ORIGIN_X=10
TERMINAL_ORIGIN_Y=10

TERMINAL_OFFSET_X=25
TERMINAL_OFFSET_Y=15

TERMINAL_WIN_WIDTH=500
TERMINAL_WIN_HEIGHT=300

