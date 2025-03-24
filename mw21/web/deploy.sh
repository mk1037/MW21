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

if [ $# -ne 2 ]; then
  echo "Usage $0 <label> <srcDir>"
  exit 1
fi

labelVar=$1
srcDir=$2

if [ ! -d $srcDir ] ; then
  echo "Source dir $srcDir doesn't exist. Exiting..."
  exit 1
fi

echo "Target dir is $DATA_DIRECTORY"

deploy_file() # sourcefilebasename extension destfileextension srcDir targetDir
{
  if [ $# -ne 5 ]; then
    echo "Function deploy_file called with wrong numer of arguments. Exiting ..."
    exit 1
  fi

  results=$(find $4 -type f -name "$1.$2" | grep $1) # grep purpose is to skip empty lines
  results_num=$(echo $results | wc -l)
  if [ "$results" = "" ]; then
    echo "Empty result for file $1.$2 Skipping..."
    return
  fi

  if [ $results_num -ne 1 ]; then
    echo "Non-unique result for file $1.$2"
    echo "$results"
    exit 1
  fi

  sourceFile=$(echo $results | head -1)
  echo "Will copy $sourceFile TO $5/$1.$3"
  cp $sourceFile $5/$1.$3
  
}

echo "Trying deploy $labelVar item from directory $srcDir"

item_match_code=$(echo $labelVar | grep -i -e "K1E[0-9][0-9]$")
if [ ! -z $item_match_code ] ; then
  echo ""
  echo "Deploying mid"
  deploy_file $labelVar "mid" "mid" $srcDir $DATA_DIRECTORY/bank_1/midi
  echo ""
  echo "Deploying text"
  deploy_file $labelVar "txt" "txt" $srcDir $DATA_DIRECTORY/bank_1/text
  echo ""
  echo "Deploying delay"
  deploy_file $labelVar "delay" "delay" $srcDir $DATA_DIRECTORY/bank_1/delay
fi

item_match_code=$(echo $labelVar | grep -i -e "WRX[0-9][0-9]$")
if [ ! -z $item_match_code ] ; then
  echo ""
  echo "Deploying mid"
  deploy_file $labelVar "mid" "mid" $srcDir $DATA_DIRECTORY/bank_2/midi
  echo ""
  echo "Deploying text"
  deploy_file $labelVar "txt" "txt" $srcDir $DATA_DIRECTORY/bank_2/text
fi

item_match_code=$(echo $labelVar | grep -i -e "K3Y[0-9][0-9]$")
if [ ! -z $item_match_code ] ; then
  echo "Deploying $labelVar item from directory $srcDir"
  echo ""
  echo "Deploying mid"
  deploy_file $labelVar "mid" "mid" $srcDir $DATA_DIRECTORY/bank_3/midi
  echo ""
  echo "Deploying text"
  deploy_file $labelVar "txt" "txt" $srcDir $DATA_DIRECTORY/bank_3/text
  echo ""
  echo "Deploying wave"
  deploy_file $labelVar "mp3" "mp3" $srcDir $DATA_DIRECTORY/bank_3/waves
  echo ""
  echo "Deploying delay"
  deploy_file $labelVar "delay" "delay" $srcDir $DATA_DIRECTORY/bank_3/delay
fi


