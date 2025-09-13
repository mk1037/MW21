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

printf "###################### MW21 ######################

Welcome to MW21 - Music Workstation!

Copyright (C) 2017-2025 Marek Momot

MW21 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

MW21 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with MW21.  If not, see <http://www.gnu.org/licenses/>.\n\n"

sleep 2

if [[ $# -lt 1 ]]; then
    LABEL=default
else
    LABEL=$1
fi

./install_configs.sh $LABEL

. ./scripts_config.sh

cp ../mw2_config /tmp/mw2_config

echo "Initializing directory $COMMON_DIRECTORY"
[ -d $COMMON_DIRECTORY ] || mkdir -p $COMMON_DIRECTORY

./data_check.sh

if [ "$?" != "0" ]; then
  echo "Incorrect data. Check your collection. Exiting. Press ENTER"
  read variable1
  exit 1;
fi

echo "70" > $DEFAULT_VOLUME_PATH

./run_midi.sh
./run_audio.sh

./place_windows.sh

