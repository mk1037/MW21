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

echo "Here is 3000 stopper !"

for playing_item_pid in $(pstree -hpl | grep -e "$PLAYER3000_SCRIPT" | awk '{ gsub(".*pmidi\\(", ""); gsub("\\).*", ""); print; }'); do
  kill -2 "$playing_item_pid"
done

sleep 0.1

$STOPVPL2_PATH
