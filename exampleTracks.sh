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


# This script was tested on Linux Lite 7.2 x86_64 


MW2_DIR=$(pwd)

[ -L $MW2_DIR/karaoke_link ] && rm $MW2_DIR/karaoke_link

[ -d $MW2_DIR/ExampleTracksForMW21-main ] && rm -rf $MW2_DIR/ExampleTracksForMW21-main
[ -d $MW2_DIR/collections/example ] && rm -rf $MW2_DIR/collections/example

[ ! -f main.tar.gz ] && wget https://github.com/mk1037/ExampleTracksForMW21/archive/refs/heads/main.tar.gz
tar -zxvf main.tar.gz ExampleTracksForMW21-main/ExampleTracksForMW21/karaoke/
mv ExampleTracksForMW21-main/ExampleTracksForMW21/karaoke/ $MW2_DIR/collections/example

ln -s $MW2_DIR/collections/example $MW2_DIR/karaoke_link


