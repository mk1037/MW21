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

MW2_DIR=$(pwd)

echo "MW21 collection choose"
echo ""

MW21_COLLECTIONS=($( find ./collections -maxdepth 1 -type d | tail -n+2 | cut -c 15- | sort ))

printf "Collections found in MW21/collections/:\n"

for index in "${!MW21_COLLECTIONS[@]}"; do
  printf "%4d: %s\n" "$index" "${MW21_COLLECTIONS[$index]}"
done

printf "\nChoose the number and press ENTER: "

read COLLECTION_NUMBER_TXT
COLLECTION_NUMBER_INT=$(($COLLECTION_NUMBER_TXT))

CHOSEN_COLLECTION="${MW21_COLLECTIONS[$COLLECTION_NUMBER_INT]}"

printf "Your choice is %d: \"%s\"\n" $COLLECTION_NUMBER_INT $CHOSEN_COLLECTION

if [ "$CHOSEN_COLLECTION" == "" ]; then
  echo "This is not valid choose. Doing nothing"
  printf "\nPress ENTER to exit"
else
  echo "Linking collection \"$CHOSEN_COLLECTION\""
  [ -L $MW2_DIR/karaoke_link ] && rm $MW2_DIR/karaoke_link
  ln -s $MW2_DIR/collections/$CHOSEN_COLLECTION $MW2_DIR/karaoke_link
  printf "\nPlease remember to restart MW21. Press ENTER to exit."
fi

read x