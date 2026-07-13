#!/bin/bash

# Copyright (C) 2017-2026 Marek Momot
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


DECODE_WAV_DIR=~/MW21/karaoke_link

for oggfile in $(find -L $DECODE_WAV_DIR -type f -iname "*.ogg"); do
  base_file_name=$(echo $oggfile | sed 's/....$//')
  ogg123 -d wav -f "$base_file_name.wav" $oggfile
  rm $oggfile
done

for flacfile in $(find -L $DECODE_WAV_DIR -type f -iname "*.flac"); do
  flac -f --decode $flacfile
  rm $flacfile
done

for mp3file in $(find -L $DECODE_WAV_DIR -type f -iname "*.mp3"); do
  lame --decode $mp3file
  rm $mp3file
done
