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

#USAGE: volumev2.sh <0-100>

export DISPLAY=":0"

INPUT_VOLUME=$1


if [[ $INPUT_VOLUME -lt 10 ]]; then
  echo "Volume set to 0"
  VVALUE="0" # 0 * 256
fi

if [[ $INPUT_VOLUME -ge 10 && $INPUT_VOLUME -lt 20 ]]; then
  echo "Volume set to 10"
  VVALUE="77" # 0.3 * 256
fi

if [[ $INPUT_VOLUME -ge 20 && $INPUT_VOLUME -lt 30 ]]; then
  echo "Volume set to 20"
  VVALUE="128" # 0.5 * 256
fi

if [[ $INPUT_VOLUME -ge 30 && $INPUT_VOLUME -lt 40 ]]; then
  echo "Volume set to 30"
  VVALUE="141" # 0.55 * 256
fi

if [[ $INPUT_VOLUME -ge 40 && $INPUT_VOLUME -lt 50 ]]; then
  echo "Volume set to 40"
  VVALUE="154" # 0.6 * 256
fi

if [[ $INPUT_VOLUME -ge 50 && $INPUT_VOLUME -lt 60 ]]; then
  echo "Volume set to 50"
  VVALUE="166" # 0.65 * 256
fi

if [[ $INPUT_VOLUME -ge 60 && $INPUT_VOLUME -lt 70 ]]; then
  echo "Volume set to 60"
  VVALUE="179" # 0.7 * 256
fi

if [[ $INPUT_VOLUME -ge 70 && $INPUT_VOLUME -lt 80 ]]; then
  echo "Volume set to 70"
  VVALUE="192" # 0.75 * 256
fi

if [[ $INPUT_VOLUME -ge 80 && $INPUT_VOLUME -lt 90 ]]; then
  echo "Volume set to 80"
  VVALUE="223" # 0.87 * 256
fi

if [[ $INPUT_VOLUME -ge 90 && $INPUT_VOLUME -lt 100 ]]; then
  echo "Volume set to 90"
  VVALUE="243" # 0.95 * 256
fi

if [[ $INPUT_VOLUME -ge 100 ]]; then
  echo "Volume set to 100"
  VVALUE="256" # 1 * 256
fi

curl -XGET -u :$VLC_PASSWORD "127.0.0.1:$VLC_PORT/requests/status.xml?command=volume&val=$VVALUE" --write-out %{http_code} --output "$COMMON_DIRECTORY/curl_out" --silent
