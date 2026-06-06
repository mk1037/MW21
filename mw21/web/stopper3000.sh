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

for playing_item_pid in $(ps -u $(whoami) | grep aplaymidi | awk '{print $1}'); do
echo "$playing_item_pid"
kill -9 $playing_item_pid
done

ps -ef | grep -e "aplay " | grep -v grep |  awk '{print $2;}' | xargs kill -9

sleep 0.1
