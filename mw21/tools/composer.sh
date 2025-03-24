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


if [[ $# -lt 4 ]] ; then
   echo "ERROR Too less arguments"
   echo "Usage: $0 abs_waves_dir scenario_file proxy_dir output_dir"
   exit
fi

WAVES_DIR=$1
SCENARIO_FILE=$2
PROXY_DIR=$3
OUTPUT_DIR=$4
ACTUAL_PATH=./

if [ ! -d $WAVES_DIR ]; then
   echo "Waves dir doesn't exist. Exiting ..."
   exit
fi

if [ -d $PROXY_DIR ]; then
   echo "Proxy dir already exists. Exiting ..."
   exit
fi

if [ -d $OUTPUT_DIR ]; then
   echo "Output dir already exists. Exiting ..."
   exit
fi

mkdir $PROXY_DIR
mkdir $OUTPUT_DIR


find_index() {
   is_empty=$(find $1 -maxdepth 0 -empty -exec echo empty \;)
   if [ "$is_empty" == "empty" ]; then
      echo "empty"
      return
   fi
   last_index_result=$(ls -1 $1 | sort | tail -1 | cut -c1-4 | sed 's/^0\+//g')
   if [ "$last_index_result" == "" ] ; then
      echo "empty"
      return
   fi
   echo $last_index_result
}

next_index() {
   if [ "$1" == "empty" ]; then
      echo "0"
      return
   fi
   echo `expr $1 + 1`
}

execute_line() {
   printf "execute_line() called with %d parameters\n" $#
   if [[ $# -lt 2 || $# -gt 5 ]]; then
      echo "Invalid number of parameters"
      return
   fi

   if [ $1 == "PR10" ]; then
      echo "Proxy random 10"
      if [[ $# -lt 3 ]]; then
         echo "Too less parameters for proxy random 10"
         return
      fi
      MULTIPLIER=1
      if [[ $# -eq 4 ]]; then
         MULTIPLIER=$4
      fi

      mkdir $PROXY_DIR/$3

      for mult_index in $(seq $MULTIPLIER); do
         echo "ACTION proxying random 10 from $WAVES_DIR/$2/ to $PROXY_DIR/$3/"
         echo "perl $ACTUAL_PATH/proxy_random_10.pl $WAVES_DIR/$2/ $PROXY_DIR/$3/"
         perl $ACTUAL_PATH/proxy_random_10.pl $WAVES_DIR/$2/ $PROXY_DIR/$3/
      done

      return
   fi

   if [ $1 == "PR_D" ]; then
      echo "Proxy directory"
      if [[ $# -lt 3 ]]; then
         echo "Too less parameters for proxy directory"
         return
      fi

      mkdir $PROXY_DIR/$3

      echo "ACTION proxying directory $WAVES_DIR/$2/ to $PROXY_DIR/$3/"
      echo "perl $ACTUAL_PATH/proxy_directory.pl $WAVES_DIR/$2/ $PROXY_DIR/$3/"
      perl $ACTUAL_PATH/proxy_directory.pl $WAVES_DIR/$2/ $PROXY_DIR/$3/

      return
   fi

   if [ $1 == "PR_I" ]; then
      echo "Proxy single item"
      if [ ! -f $WAVES_DIR/$2/$3 ]; then
         echo "File $WAVES_DIR/$2/$3 does not exist. Exiting ..."
         exit
      fi

      mkdir $PROXY_DIR/$4
      echo "ACTION proxying item $WAVES_DIR/$2/$3 to $PROXY_DIR/$4/"
      ln -s $WAVES_DIR/$2/$3 $PROXY_DIR/$4/$3

      return
   fi

   if [ $1 == "IM10" ]; then
      echo "Import random 10"
      if [[ $# -lt 2 ]]; then
         echo "Too less parameters for import random 10"
         return
      fi

      if [[ $# -eq 3 ]]; then
         IMPORT_INDEX=$3
      else
         LAST_INDEX=$( find_index $OUTPUT_DIR )
         IMPORT_INDEX=$(next_index $LAST_INDEX)
      fi

      echo "ACTION importing random 10 from $PROXY_DIR/$2/ to $OUTPUT_DIR/ at index $IMPORT_INDEX"
      echo "perl $ACTUAL_PATH/import_random_10.pl $PROXY_DIR/$2/ $OUTPUT_DIR/ $IMPORT_INDEX"
      perl $ACTUAL_PATH/import_random_10.pl $PROXY_DIR/$2/ $OUTPUT_DIR/ $IMPORT_INDEX

      return
   fi

   if [ $1 == "IM_D" ]; then
      echo "Import directory"
      if [[ $# -lt 2 ]]; then
         echo "Too less parameters for import directory"
         return
      fi

      if [[ $# -eq 3 ]]; then
         IMPORT_INDEX=$3
      else
         LAST_INDEX=$( find_index $OUTPUT_DIR )
         IMPORT_INDEX=$(next_index $LAST_INDEX)
      fi

      echo "ACTION importing directory $PROXY_DIR/$2/ to $OUTPUT_DIR/ at index $IMPORT_INDEX"
      echo "perl $ACTUAL_PATH/import_directory.pl $PROXY_DIR/$2/ $OUTPUT_DIR/ $IMPORT_INDEX"
      perl $ACTUAL_PATH/import_directory.pl $PROXY_DIR/$2/ $OUTPUT_DIR/ $IMPORT_INDEX

      return
   fi

}

while IFS= read -r line
do
   echo "---------------------------------------------"
   printf "line is    \'%s\'\n" "$line"
   CONTENT=$(echo $line | sed 's/#.*//g')
   printf "content is \'%s\'\n" "$CONTENT"

   execute_line $CONTENT

done <"$SCENARIO_FILE"



