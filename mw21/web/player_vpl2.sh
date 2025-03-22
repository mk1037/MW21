#!/bin/bash

# Arguments:
#    1. dir
#    2. log file
#    3. K3Y vs break

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

PLAY2_LOG="$2"
K3Y_VS_BREAK="$3"
logseparator="----------------------------------"

export DISPLAY=":0"

function percent_to_gain {

  TMP_INPUT_VOLUME=$1
  if [[ $TMP_INPUT_VOLUME -lt 10 ]]; then
    GVALUE="0.000000" # 0.0^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 10 && $TMP_INPUT_VOLUME -lt 20 ]]; then
    GVALUE="0.027000" # 0.3^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 20 && $TMP_INPUT_VOLUME -lt 30 ]]; then
    GVALUE="0.125000" # 0.5^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 30 && $TMP_INPUT_VOLUME -lt 40 ]]; then
    GVALUE="0.166375" # 0.55^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 40 && $TMP_INPUT_VOLUME -lt 50 ]]; then
    GVALUE="0.216000" # 0.6^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 50 && $TMP_INPUT_VOLUME -lt 60 ]]; then
    GVALUE="0.274625" # 0.65^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 60 && $TMP_INPUT_VOLUME -lt 70 ]]; then
    GVALUE="0.343000" # 0.7^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 70 && $TMP_INPUT_VOLUME -lt 80 ]]; then
    GVALUE="0.421875" # 0.75^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 80 && $TMP_INPUT_VOLUME -lt 90 ]]; then
    GVALUE="0.658503" # 0.87^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 90 && $TMP_INPUT_VOLUME -lt 100 ]]; then
    GVALUE="0.857375" # 0.95^3
  fi

  if [[ $TMP_INPUT_VOLUME -ge 100 ]]; then
    GVALUE="1.000000" # 1^3
  fi
  echo $GVALUE
}

function create_vlc_config { # source_config print_gain eq_bands
  if [ "OFF" == "$3" ]; then
    cat $1 | awk -v print_gain=$2 '{ if (/alsa-gain/) print "alsa-gain=" print_gain; else print;}' > $VLCRC_PATH
  else
    #TMP_EQ_PREAMP=$(head -2 $EQ_SETTINGS_PATH | tail -1)
    cat $1 | awk -v print_gain=$2 -v eq_bands="$3" '{ if (/alsa-gain/) print "alsa-gain=" print_gain; else if (/audio-filter/) print "audio-filter=equalizer"; else if (/equalizer-bands/) print "equalizer-bands=" eq_bands; else if (/equalizer-preamp/) print "equalizer-preamp=12.000000"; else print;}' > $VLCRC_PATH
  fi
}

function play_vpl { # dir item
  TYPE="video"
  echo $2 | grep -i -e "mp3\$"
  if [ $? == 0 ]; then TYPE="music"; fi

  echo $2 | grep -i -e "wav\$"
  if [ $? == 0 ]; then TYPE="music"; fi

  echo $2 | grep -i -e "flac\$"
  if [ $? == 0 ]; then TYPE="music"; fi

  $PLACEV2_PATH $TYPE &

  TMP_EQ_FLAG=$(head -1 $EQ_SETTINGS_PATH)
  C_TIMESTAMP=$(date +%Y_%m_%d__%H:%M:%S)

  if [ "music" == $TYPE ]; then
    if [ $3 != "K3Y" ]; then
      # filter gain
      TMP_VOLUME=$(head -1 $DEFAULT_VOLUME_PATH)
      TMP_GAIN=$(percent_to_gain $TMP_VOLUME)
#       echo "tmp volume is $TMP_VOLUME"
#       echo "tmp gain is $TMP_GAIN"
#       echo "EQ $TMP_EQ_FLAG"
      create_vlc_config ./templates/alsa_music_template $TMP_GAIN "$TMP_EQ_FLAG"
    else
      create_vlc_config ./templates/alsa_music_template "1.000000" "$TMP_EQ_FLAG"
    fi
    echo "$C_TIMESTAMP AUDIO $K3Y_VS_BREAK $2" >> $PLAYVPL2_LOGS_PATH
    cvlc --extraintf http --http-host 127.0.0.1 --http-port $VLC_PORT --http-password $VLC_PASSWORD --no-volume-save $1/$2 2>>$PLAY2_LOG
  else
    # create tmp movie template
    create_vlc_config ./templates/alsa_movie_template "1.000000" "$TMP_EQ_FLAG"
    echo "$C_TIMESTAMP VIDEO $K3Y_VS_BREAK $2" >> $PLAYVPL2_LOGS_PATH
    vlc --extraintf http --http-host 127.0.0.1 --http-port $VLC_PORT --http-password $VLC_PASSWORD --no-volume-save $1/$2 2>>$PLAY2_LOG
  fi
}

LINES_NUM=$(cat $PLAYVPL2_PLAYLIST | wc -l)

if [ "$#" -eq 4 ]; then
  DELAY=$4
else
  DELAY=0
fi

while [ $LINES_NUM -gt 0 ] ; do
   nextitem=$( head -1 $PLAYVPL2_PLAYLIST )
   cat $PLAYVPL2_PLAYLIST | awk 'NR == 1 { next } { print }' > $PLAYVPL2_PLAYLIST_TMP
   cp $PLAYVPL2_PLAYLIST_TMP $PLAYVPL2_PLAYLIST
   cp $PLAYVPL2_PLAYLIST $PLAYVPL2_PLAYLIST_TO_DISPLAY
   TOTAL_TIME_OFFSET=$(echo "$GLOBAL_DELAY + $DELAY" | bc)
   echo "TOTAL time offset is $TOTAL_TIME_OFFSET and play $nextitem" > $PLAY2_LOG

   ONE_IF_POSITIVE=$(echo "$TOTAL_TIME_OFFSET > 0" | bc)

   if [ "$ONE_IF_POSITIVE" -gt 0 ]; then
     echo "sleeping $TOTAL_TIME_OFFSET"
     sleep $TOTAL_TIME_OFFSET
   else
     echo "Not sleeping $TOTAL_TIME_OFFSET"
   fi

   play_vpl $1 $nextitem $K3Y_VS_BREAK
   LINES_NUM=$(cat $PLAYVPL2_PLAYLIST | wc -l)
   cp $PLAYVPL2_PLAYLIST $PLAYVPL2_PLAYLIST_TO_DISPLAY
done

