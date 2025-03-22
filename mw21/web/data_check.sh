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

# DATA_DIRECTORY

BANK_3_MID_NUMBER=$(ls $DATA_DIRECTORY/bank_3/midi/ | wc -l )
BANK_3_TXT_NUMBER=$(ls $DATA_DIRECTORY/bank_3/text/ | wc -l )
BANK_3_DELAY_NUMBER=$(ls $DATA_DIRECTORY/bank_3/delay/ | wc -l )
BANK_3_WAVES_NUMBER=$(ls $DATA_DIRECTORY/bank_3/waves/ | wc -l )

if [ "$BANK_3_MID_NUMBER" -ne "$BANK_3_TXT_NUMBER" ]; then
  echo "Number of files in bank_3 mid vs txt differ !!!"
  ls $DATA_DIRECTORY/bank_3/midi/ | rev | cut -c5- | rev | sort > $DATA_CHECK_DIFF_LEFT
  ls $DATA_DIRECTORY/bank_3/text/ | rev | cut -c5- | rev | sort > $DATA_CHECK_DIFF_RIGHT
  diff -u $DATA_CHECK_DIFF_LEFT $DATA_CHECK_DIFF_RIGHT
  exit 1;
fi

if [ "$BANK_3_MID_NUMBER" -ne "$BANK_3_DELAY_NUMBER" ]; then
  echo "Number of files in bank_3 mid vs delay differ !!!"
  ls $DATA_DIRECTORY/bank_3/midi/ | rev | cut -c5- | rev | sort > $DATA_CHECK_DIFF_LEFT
  ls $DATA_DIRECTORY/bank_3/delay/ | rev | cut -c7- | rev | sort > $DATA_CHECK_DIFF_RIGHT
  diff -u $DATA_CHECK_DIFF_LEFT $DATA_CHECK_DIFF_RIGHT
  exit 1;
fi

if [ "$BANK_3_MID_NUMBER" -ne "$BANK_3_WAVES_NUMBER" ]; then
  echo "Number of files in bank_3 mid vs waves differ !!!"
  ls $DATA_DIRECTORY/bank_3/midi/ | rev | cut -c5- | rev | sort > $DATA_CHECK_DIFF_LEFT
  ls $DATA_DIRECTORY/bank_3/waves/ | rev | cut -c5- | rev | sort > $DATA_CHECK_DIFF_RIGHT
  diff -u $DATA_CHECK_DIFF_LEFT $DATA_CHECK_DIFF_RIGHT
  exit 1;
fi


for name in $(ls $DATA_DIRECTORY/bank_3/midi/ ); do
  filtered_name=$( echo $name | grep -e '^[a-zA-Z0-9]\+_K3[yY][0-9]\{2,3\}.mid$' )
  if [ "$filtered_name" == "" ]; then
    echo "Wrong name in bank_3: $name"
    exit 1;
  fi
  base_file_name=$(echo $filtered_name | rev | cut -c5- | rev)
  text_file_name=$base_file_name.txt
  ls $DATA_DIRECTORY/bank_3/text/$text_file_name 1>/dev/null
  if [ "$?" != "0" ]; then
    echo "No file $DATA_DIRECTORY/bank_3/text/$text_file_name"
    echo "Exiting ..."
    exit 1;
  fi
  delay_file_name=$base_file_name.delay
  ls $DATA_DIRECTORY/bank_3/delay/$delay_file_name 1>/dev/null
  if [ "$?" != "0" ]; then
    echo "No file $DATA_DIRECTORY/bank_3/delay/$delay_file_name"
    echo "Exiting ..."
    exit 1;
  fi
  audio_file_name=$base_file_name.mp3
  ls $DATA_DIRECTORY/bank_3/waves/$audio_file_name 1>/dev/null
  if [ "$?" != "0" ]; then
    echo "No file $DATA_DIRECTORY/bank_3/waves/$audio_file_name"
    echo "Exiting ..."
    exit 1;
  fi
done

exit 0;
