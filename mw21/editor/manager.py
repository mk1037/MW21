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

import collection
import os
import json
import pprint

class Manager:
  def __init__(self, p_config, p_configPath, p_collectionsDir, p_homeDir ):
    self.config = p_config
    self.configPath = p_configPath
    self.collection = None
    self.collectionName = None
    self.collectionsDir = p_collectionsDir
    if "tapesRecentDir" not in self.config.keys():
      self.config["tapesRecentDir"] = p_homeDir

  def setCollectionName(self, p_collectionName):
    self.collectionName = p_collectionName

  def scanRoot(self):
    self.collection = collection.Collection(self.collectionsDir + "/" + self.collectionName)
    self.collection.readCollection()

  def printSongs(self):
    self.collection.printCollection()

  def getCollectionNames(self):
    return os.listdir(self.collectionsDir)

  def getCollection(self):
    return self.collection

  def removeSong(self, p_label):
    print("Removing song '{}'".format(p_label))
    audiofile = self.collectionsDir + "/" + self.collectionName + "/bank_3/waves/" + p_label + ".mp3"
    delayfile = self.collectionsDir + "/" + self.collectionName + "/bank_3/delay/" + p_label + ".delay"
    midifile = self.collectionsDir + "/" + self.collectionName + "/bank_3/midi/" + p_label + ".mid"
    textfile = self.collectionsDir + "/" + self.collectionName + "/bank_3/text/" + p_label + ".txt"

    if os.path.exists(audiofile):
      os.remove(audiofile)
    if os.path.exists(delayfile):
      os.remove(delayfile)
    if os.path.exists(midifile):
      os.remove(midifile)
    if os.path.exists(textfile):
      os.remove(textfile)

  def getTapesRecentDir(self):
    return self.config["tapesRecentDir"]

  def setTapesRecentDir(self, p_dir):
    self.config["tapesRecentDir"] = p_dir
    print("Tapes recent dir updated to '{}'".format(self.config["tapesRecentDir"]))

  def saveConfig(self):
    print("Saving config")
    with open(self.configPath, "w") as f:
      json.dump(self.config, f)
      print("Config has been written to {}".format(self.configPath))
