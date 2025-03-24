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

touch $PLAYVPL2_PLAYLIST_TMP
touch $PLAYVPL2_PLAYLIST
touch $PLAYVPL2_PLAYLIST_TO_DISPLAY
touch $EXEC_PLAYER_NAME_PATH

echo "vlc" > $EXEC_PLAYER_NAME_PATH
echo "70" > $DEFAULT_VOLUME_PATH

echo "OFF" > $EQ_SETTINGS_PATH

echo $PLAYVPL2_TRAP_PATH
$TERMINAL_BIN --title="playvpl2_Terminal" -x $PLAYVPL2_TRAP_PATH &
