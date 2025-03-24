#!/bin/bash

# Arguments list:
#    1. dir
#    2. position (positive)
#    3. item number

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

l_prefix=$3
item_to_write=$(ls $1 | grep ^$l_prefix)


cat $PLAYVPL2_PLAYLIST | awk "NR==$2 { print \"$item_to_write\"; } NR!=$2 { print; }" > $PLAYVPL2_PLAYLIST_TMP

cp $PLAYVPL2_PLAYLIST_TMP $PLAYVPL2_PLAYLIST
cp $PLAYVPL2_PLAYLIST_TMP $PLAYVPL2_PLAYLIST_TO_DISPLAY

