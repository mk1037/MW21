#!/bin/bash

# Arguments list:
#    1. dir
#    2. item number
#    3. random limit

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

l_prefix=$2

ls $1 | grep ^$l_prefix > $PLAYVPL2_PLAYLIST_TMP

if [ $2 -ge $3 ]; then
   l_prefix=$(echo $2 | cut -c1-3)
   ls $1 | grep ^$l_prefix | grep -v ^$2 | shuf >> $PLAYVPL2_PLAYLIST_TMP
fi

cp $PLAYVPL2_PLAYLIST_TMP $PLAYVPL2_PLAYLIST
cp $PLAYVPL2_PLAYLIST_TMP $PLAYVPL2_PLAYLIST_TO_DISPLAY

