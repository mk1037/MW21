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

MAINPR_INSTRUCTION_PATH=$(get_config_variable "MAIN_PR_instruction")
MAINPR_PID_PATH=$(get_config_variable "MAIN_PR_pid")

echo "ON" > $MAINPR_INSTRUCTION_PATH
MAIN_PROXY_PID_FOR_LOCK=$(head -1 $MAINPR_PID_PATH)
kill -10 $MAIN_PROXY_PID_FOR_LOCK

