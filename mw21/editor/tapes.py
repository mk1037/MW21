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

import tarfile
import re
import io
import pprint

g_patternTapeFilename = r"^[a-zA-Z0-9]+_K3[yY][0-9]{2,3}\.(tar|tar\.gz|tar\.bz2)$"

class Tapes:
  def __init__(self, p_collectionPath):
    self.collectionPath = p_collectionPath
  
  def checkTapeFilename(self, p_filename):
    if re.search(g_patternTapeFilename, p_filename) is not None:
      return True
    return False



  def importTape(self, p_tapePath):
    chunks = p_tapePath.split("/")
    tapeFilename = chunks[-1]
    chunks.pop()
    tapePath = "/".join(chunks)
    if not self.checkTapeFilename(tapeFilename):
      print("Invalid tape filename '{}'".format(tapeFilename))
      return
    
    tarObj = tarfile.open(name = p_tapePath)
    members = tarObj.getnames()

    audiofiles = []
    delayfiles = []
    midifiles = []
    textfiles = []
    
    chunks2 = tapeFilename.split(".")
    tapeLabel = chunks2[0]
    for path in members:
      if re.search(tapeLabel + ".mp3$", path):
        audiofiles.append(path)
      if re.search(tapeLabel + ".delay$", path):
        delayfiles.append(path)
      if re.search(tapeLabel + ".mid$", path):
        midifiles.append(path)
      if re.search(tapeLabel + ".txt$", path):
        textfiles.append(path)
        
    pprint.pprint(audiofiles)
    pprint.pprint(delayfiles)
    pprint.pprint(midifiles)
    pprint.pprint(textfiles)
    
    if len(audiofiles) != 1 or len(delayfiles) != 1 or len(midifiles) != 1 or len(textfiles) != 1:
      print("Wrong tape archive '{}'".format(p_tapePath))
      return

    audiofile = tarObj.extractfile(tarObj.getmember(audiofiles[0]))
    with open(self.collectionPath + "/bank_3/waves/" + tapeLabel + ".mp3", 'wb') as a_writer:
      a_writer.write(audiofile.read())

    delayfile = tarObj.extractfile(tarObj.getmember(delayfiles[0]))
    with open(self.collectionPath + "/bank_3/delay/" + tapeLabel + ".delay", 'wb') as a_writer:
      a_writer.write(delayfile.read())

    midifile = tarObj.extractfile(tarObj.getmember(midifiles[0]))
    with open(self.collectionPath + "/bank_3/midi/" + tapeLabel + ".mid", 'wb') as a_writer:
      a_writer.write(midifile.read())

    textfile = tarObj.extractfile(tarObj.getmember(textfiles[0]))
    with open(self.collectionPath + "/bank_3/text/" + tapeLabel + ".txt", 'wb') as a_writer:
      a_writer.write(textfile.read())

    return tapePath
