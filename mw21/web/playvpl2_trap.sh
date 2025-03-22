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

touch $PLAYVPL2_TRAP_PID_PATH

echo "trap $PLAYVPL2_ON_SIGNAL_PATH SIGUSR1"
trap $PLAYVPL2_ON_SIGNAL_PATH SIGUSR1
echo "echo $$ > $PLAYVPL2_TRAP_PID_PATH"
echo $$ > $PLAYVPL2_TRAP_PID_PATH

while true; do
  read somevar  
done
