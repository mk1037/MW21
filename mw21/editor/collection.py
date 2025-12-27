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

import dirscan
import pprint

class Collection:
  def __init__(self, p_root):
    self.rootDir = p_root
    self.songs = {}

  def readCollection(self):
    scanObj = dirscan.DirScan(self.rootDir + "/bank_3/**")
    labels = scanObj.scanDirLabels()
    self.songs = {}
    for label in sorted(labels):
      self.songs[label] = scanObj.preCheckLabel(label)

  def printCollection(self):
    pprint.pprint(self.songs)

  def getSongs(self):
    return self.songs
