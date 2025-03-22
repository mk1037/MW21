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

if [[ $# -lt 1 ]]; then
    LABEL=default
else
    LABEL=$1
fi

echo "Installing configs for environment \"$LABEL\""

[ -d ./templates ] || mkdir -p ./templates

cp ../configs/$LABEL/mw2_config ../
cp ../configs/$LABEL/specific_variables.sh .
cp ../configs/$LABEL/config.php .
cp ../configs/$LABEL/templates/* ./templates/

php ./init_files.php

