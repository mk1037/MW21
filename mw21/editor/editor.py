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

import manager
from tkinter import *
from tkinter import ttk
from tkinter.filedialog import askopenfilenames
import tkinter as tk
import os
import json
import pprint
import tapes

homeDir = os.environ['HOME']
collectionsDir = homeDir + "/MW21/collections"
config = {}

configPath = homeDir + "/.MW21editor"


class ScrollableFrame(ttk.Frame):
  def __init__(self, container, *args, **kwargs):
    super().__init__(container, *args, **kwargs)
    canvas = tk.Canvas(self, width = 600, height = 200)
    scrollbar = ttk.Scrollbar(self, orient="vertical", command=canvas.yview)
    self.scrollable_frame = ttk.Frame(canvas)

    self.scrollable_frame.bind(
      "<Configure>",
      lambda e: canvas.configure(
          scrollregion=canvas.bbox("all")
      )
    )
    canvas.create_window((0, 0), window=self.scrollable_frame, anchor="nw")
    canvas.configure(yscrollcommand=scrollbar.set)

    canvas.grid(column = 0, row = 0, sticky=(N, W, S, E))
    scrollbar.grid(column = 1, row = 0, sticky=(N, E, S, W))

  def getInnerFrame(self):
    return self.scrollable_frame



if os.path.exists(configPath):
  with open(configPath, 'r') as file:
    config = json.load(file)
    print("Config has been read from {}".format(configPath))

def loadCollection(*args):
  managerObj.setCollectionName(collectionVar.get())
  managerObj.scanRoot()
  managerObj.printSongs()
  redrawCollection(managerObj)

def redrawCollection(p_manager):
  for a in list(songLabels.keys()):
    widget = songLabels.pop(a)
    widget.destroy()

  for a in list(songCheckVars.keys()):
    widget = songCheckButtons.pop(a)
    widget.destroy()
    songCheckVars.pop(a)

  for a in list(songAudio.keys()):
    widget = songAudio.pop(a)
    widget.destroy()

  for a in list(songDelay.keys()):
    widget = songDelay.pop(a)
    widget.destroy()

  for a in list(songMidi.keys()):
    widget = songMidi.pop(a)
    widget.destroy()

  for a in list(songText.keys()):
    widget = songText.pop(a)
    widget.destroy()

  collection = p_manager.getCollection()

  rowindex = 0
  for item in collection.getSongs().keys():
    #print(rowindex)

    color = "black"
    background = "white"
    if collection.getSongs()[item]["status"] != True:
      color = "white"
      background = "red"

    clabel = ttk.Label(labelsFrame, text=item, borderwidth=1, relief="solid")
    clabel['background'] = background
    clabel['foreground'] = color
    clabel.grid(column = 0, row = rowindex, padx = 1, sticky=(N, W, E))
    songLabels[item] = clabel




    songCheckVars[item] = IntVar()
    check = ttk.Checkbutton(labelsFrame, text='Select', variable=songCheckVars[item] )
    check.grid(column = 1, row = rowindex, padx = 1, sticky=(N, W, E))
    songCheckButtons[item] = check



    background = "white"
    color = "green"
    text = "audio OK"
    if len(collection.getSongs()[item]["audio"]) != 1:
      color = "red"
      text = "NO audio"

    caudio = ttk.Label(labelsFrame, text=text, width = 8, borderwidth=1, relief="solid")
    caudio['background'] = background
    caudio['foreground'] = color
    caudio.grid(column = 2, row = rowindex, padx = 1, sticky=(N, W, E))
    songAudio[item] = caudio



    background = "white"
    color = "green"
    text = "delay OK"
    if len(collection.getSongs()[item]["delay"]) != 1:
      color = "red"
      text = "NO delay"

    cdelay = ttk.Label(labelsFrame, text=text, width = 8, borderwidth=1, relief="solid")
    cdelay['background'] = background
    cdelay['foreground'] = color
    cdelay.grid(column = 3, row = rowindex, padx = 1, sticky=(N, W, E))
    songDelay[item] = cdelay


    background = "white"
    color = "green"
    text = "midi OK"
    if len(collection.getSongs()[item]["midi"]) != 1:
      color = "red"
      text = "NO midi"

    cmidi = ttk.Label(labelsFrame, text=text, width = 8, borderwidth=1, relief="solid")
    cmidi['background'] = background
    cmidi['foreground'] = color
    cmidi.grid(column = 4, row = rowindex, padx = 1, sticky=(N, W, E))
    songMidi[item] = cmidi




    background = "white"
    color = "green"
    text = "text OK"
    if len(collection.getSongs()[item]["midi"]) != 1:
      color = "red"
      text = "NO text"

    ctext = ttk.Label(labelsFrame, text=text, width = 8, borderwidth=1, relief="solid")
    ctext['background'] = background
    ctext['foreground'] = color
    ctext.grid(column = 5, row = rowindex, padx = 1, sticky=(N, W, E))
    songText[item] = ctext


    rowindex += 1
  #pprint.pprint(songLabels)


def deleteSelected(*args):
  for a in list(songCheckVars.keys()):
    print("{} {}".format(a, songCheckVars[a].get()))
    if songCheckVars[a].get() == 1:
      managerObj.removeSong(a)
  managerObj.setCollectionName(collectionVar.get())
  managerObj.scanRoot()
  managerObj.printSongs()
  redrawCollection(managerObj)


def importTape(*args):
  if collectionVar.get() == "":
    print("Select collection first")
    return
  files = askopenfilenames(title = "Select Tape Archives (tar, tar.gz, tar.bz2)", initialdir=managerObj.getTapesRecentDir(), filetypes = [ ('tar', '*.tar'), ('tar.gz', '*.tar.gz'), ('tar.bz2', '*.tar.bz2'),  ])
  print(files)
  tapesObj = tapes.Tapes(collectionsDir + "/" + collectionVar.get())
  print("Will import to {}".format(tapesObj.collectionPath))
  lastPath = None
  for apath in files:
    lastPath = tapesObj.importTape(apath)

  if lastPath is not None:
    managerObj.setTapesRecentDir(lastPath)
    managerObj.saveConfig()
  managerObj.setCollectionName(collectionVar.get())
  managerObj.scanRoot()
  managerObj.printSongs()
  redrawCollection(managerObj)


managerObj = manager.Manager(config, configPath, collectionsDir, homeDir)
songLabels = {}
songCheckButtons = {}
songCheckVars = {}
songAudio = {}
songDelay = {}
songMidi = {}
songText = {}

root = Tk()
root.title("MW21 Collection Editor")

mainframe = ttk.Frame(root).grid(column = 0, row = 0)

topFrame = ttk.Frame(mainframe)
topFrame.grid(column = 0, row = 0, padx = 5, pady = 5, sticky=(N, W, E))

middleFrame = ScrollableFrame(mainframe)
middleFrame.grid(column = 0, row = 1, padx = 5, pady = 5, sticky=(N, S, W, E))

labelsFrame = middleFrame.getInnerFrame()

bottomFrame = ttk.Frame(mainframe)
bottomFrame.grid(column = 0, row = 2, padx = 5, pady = 5, sticky=(N, S, E))

collectionVar = StringVar()
collectionComboBox = ttk.Combobox(topFrame, textvariable=collectionVar)
collectionComboBox['values'] = managerObj.getCollectionNames()
collectionComboBox.bind('<<ComboboxSelected>>', loadCollection)
collectionComboBox.state(["readonly"])
collectionComboBox.grid(column = 0, row = 0, sticky=(N, W))


separatorFrame = ttk.Frame(topFrame)
separatorFrame.grid(column = 1, row = 0, padx = 100, pady = 5, sticky=(N, W, E))

tapeButton = ttk.Button(topFrame, text='tar', command=importTape)
tapeButton.grid(column = 2, row = 0, padx = 5, pady = 5, sticky=(N, E))


deleteButton = ttk.Button(bottomFrame, text='Delete selected', command=deleteSelected)
deleteButton.grid(column = 0, row = 0, sticky=(S, E))

root.mainloop()



