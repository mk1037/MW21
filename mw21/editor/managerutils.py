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

import re

g_patternFilename = r"^[a-zA-Z0-9]+_K3[yY][0-9]{2,3}\.(txt|mid|flac|mp3|ogg|wav|delay)$"

def validFilename(p_filename):
  if re.search(g_patternFilename, p_filename) is not None:
    return True
  return False

def getFilenameOnly(p_path):
  chunks = re.split("/", p_path)
  return chunks[-1]
