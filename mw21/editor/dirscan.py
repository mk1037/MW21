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

import glob
import managerutils
import pprint

class DirScan:
  def __init__(self, rootDir):
    self.rootDir = rootDir

  def setRootDir(self, p_dir):
    self.rootDir = p_dir

  def scanDirPaths(self):
    allpaths = []
    for apath in glob.iglob(self.rootDir + "/*K3Y*.txt", recursive=True):
      allpaths.append(apath)
    for apath in glob.iglob(self.rootDir + "/*K3Y*.mp3", recursive=True):
      allpaths.append(apath)
    for apath in glob.iglob(self.rootDir + "/*K3Y*.delay", recursive=True):
      allpaths.append(apath)
    for apath in glob.iglob(self.rootDir + "/*K3Y*.mid", recursive=True):
      allpaths.append(apath)
    return allpaths

  def getValidLabels(self, p_paths):
    filenames = []
    for path in p_paths:
      filenames.append(managerutils.getFilenameOnly(path))

    for filename in filenames:
      if not managerutils.validFilename(filename):
        print("Invalid filename {}".format(filename))

    result = set()

    for filename in filenames:
      chunks = filename.split(".")
      result.add(chunks[0])

    return list(result)

  def scanDirLabels(self):
    return self.getValidLabels(self.scanDirPaths())

  def preCheckLabel(self, p_label):
    result = { "label" : p_label,
              "status" : False,
              "audio" : [],
              "delay" : [],
              "midi" : [],
              "text" : []
              }

    audio = []
    for apath in glob.iglob(self.rootDir + "/" + p_label + ".mp3", recursive=True):
      result["audio"].append(apath)

    delay = []
    for apath in glob.iglob(self.rootDir + "/" + p_label + ".delay", recursive=True):
      result["delay"].append(apath)

    midi = []
    for apath in glob.iglob(self.rootDir + "/" + p_label + ".mid", recursive=True):
      result["midi"].append(apath)

    text = []
    for apath in glob.iglob(self.rootDir + "/" + p_label + ".txt", recursive=True):
      result["text"].append(apath)

    if len(result["audio"]) == 1 and len(result["delay"]) == 1 and len(result["midi"]) == 1 and len(result["text"]) == 1:
      result["status"] = True

    return result
