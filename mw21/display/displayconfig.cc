/*
 * Copyright (C) 2017-2025 Marek Momot
 *
 * This file is part of MW21.
 *
 * MW21 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MW21 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MW21.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "displayconfig.h"
#include <glibmm/keyfile.h>

DisplayConfig::DisplayConfig() {
  backgroundColor[0]        = "e4e4e4";
  sungBackgroundColor[0]    = "f4f4f4";
  lyricsColor[0]            = "ffffff";
  sungLyricsColor[0]        = "ff0000";
  lyricsOutlineColor[0]     = "000000";
  sungLyricsOutlineColor[0] = "000000";
  hintsBackgroundColor[0]   = "343434";
  activeHintsBackgroundColor[0] = "838383";
  hintsColor[0]              = "848484";
  activeHintsColor[0]        = "b4b4b4";
  hintsOutlineColor[0]       = "202020";
  activeHintsOutlineColor[0] = "707070";
  inactiveLyricsColor[0]     = "ffffff";
  inactiveLyricsOutlineColor[0] = "000000";
  inactiveHintsColor[0]      = "848484";
  inactiveHintsOutlineColor[0] = "202020";

  backgroundColor[1]        = "e4e424";
  sungBackgroundColor[1]    = "f4f422";
  lyricsColor[1]            = "ffff2f";
  sungLyricsColor[1]        = "ff0020";
  lyricsOutlineColor[1]     = "000020";
  sungLyricsOutlineColor[1] = "000020";
  hintsBackgroundColor[1]   = "343424";
  activeHintsBackgroundColor[1] = "838323";
  hintsColor[1]              = "848424";
  activeHintsColor[1]        = "b4b424";
  hintsOutlineColor[1]       = "f02020";
  activeHintsOutlineColor[1] = "707020";
  inactiveLyricsColor[1]     = "ffffff";
  inactiveLyricsOutlineColor[1] = "000000";
  inactiveHintsColor[1]      = "848484";
  inactiveHintsOutlineColor[1] = "202020";

  backgroundColor[2]        = "34e4a4";
  sungBackgroundColor[2]    = "f4f422";
  lyricsColor[2]            = "ffff2f";
  sungLyricsColor[2]        = "ff0020";
  lyricsOutlineColor[2]     = "000020";
  sungLyricsOutlineColor[2] = "000020";
  hintsBackgroundColor[2]   = "343424";
  activeHintsBackgroundColor[2] = "838323";
  hintsColor[2]              = "848424";
  activeHintsColor[2]        = "b4b424";
  hintsOutlineColor[2]       = "f02020";
  activeHintsOutlineColor[2] = "707020";
  inactiveLyricsColor[2]     = "ffffff";
  inactiveLyricsOutlineColor[2] = "000000";
  inactiveHintsColor[2]      = "848484";
  inactiveHintsOutlineColor[2] = "202020";

  outlineWidth           = 0.7;
  fontDirPrefix          = "/usr/share/fonts/truetype/dejavu/";
  fontName               = "DejaVuSerif-BoldItalic.ttf";
  fontSize               = 30;

  textPointerPath        = "/tmp/textpath";
  dataDir                = "/tmp/data";

  channel                = 16;
  noteGEQ                = 1;
  noteLT                 = 2;
  velGEQ            = 1;
  velLT             = 2;

  ctrlNum4Fw        = 81;
  ctrlVal4Fw        = 127;
  ctrlNum4Bw        = 80;
  ctrlVal4Bw        = 127;

  noteRead          = 3;
  velRead           = 1;
  noteBack          = 5;
  velBack           = 1;
  noteTheme1          = 6;
  velTheme1           = 1;
  noteTheme2          = 7;
  velTheme2           = 1;
  noteTheme3          = 8;
  velTheme3           = 1;
  noteHome            = 9;
  velHome             = 1;

  notePCKbdEnable     = 10;
  notePCKbdDisable    = 11;

  areaWidth         = 1000;
  areaHeight        = 132;
}

Glib::ustring DisplayConfig::getBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return backgroundColor[p_idx];
  return backgroundColor[0];
}

Glib::ustring DisplayConfig::getSungBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return sungBackgroundColor[p_idx];
  return sungBackgroundColor[0];
}

Glib::ustring DisplayConfig::getLyricsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return lyricsColor[p_idx];
  return lyricsColor[0];
}

Glib::ustring DisplayConfig::getSungLyricsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return sungLyricsColor[p_idx];
  return sungLyricsColor[0];
}

Glib::ustring DisplayConfig::getLyricsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return lyricsOutlineColor[p_idx];
  return lyricsOutlineColor[0];
}

Glib::ustring DisplayConfig::getSungLyricsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return sungLyricsOutlineColor[p_idx];
  return sungLyricsOutlineColor[0];
}

Glib::ustring DisplayConfig::getHintsBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return hintsBackgroundColor[p_idx];
  return hintsBackgroundColor[0];
}

Glib::ustring DisplayConfig::getActiveHintsBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return activeHintsBackgroundColor[p_idx];
  return activeHintsBackgroundColor[0];
}

Glib::ustring DisplayConfig::getHintsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return hintsColor[p_idx];
  return hintsColor[0];
}

Glib::ustring DisplayConfig::getActiveHintsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return activeHintsColor[p_idx];
  return activeHintsColor[0];
}

Glib::ustring DisplayConfig::getHintsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return hintsOutlineColor[p_idx];
  return hintsOutlineColor[0];
}

Glib::ustring DisplayConfig::getActiveHintsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return activeHintsOutlineColor[p_idx];
  return activeHintsOutlineColor[0];
}

Glib::ustring DisplayConfig::getInactiveLyricsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return inactiveLyricsColor[p_idx];
  return inactiveLyricsColor[0];
}

Glib::ustring DisplayConfig::getInactiveLyricsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return inactiveLyricsOutlineColor[p_idx];
  return inactiveLyricsOutlineColor[0];
}

Glib::ustring DisplayConfig::getInactiveHintsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return inactiveHintsColor[p_idx];
  return inactiveHintsColor[0];
}

Glib::ustring DisplayConfig::getInactiveHintsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return inactiveHintsOutlineColor[p_idx];
  return inactiveHintsOutlineColor[0];
}






double DisplayConfig::getOutlineWidth()
{
  return outlineWidth;
}

Glib::ustring DisplayConfig::getFontDirPrefix()
{
  return fontDirPrefix;
}

Glib::ustring DisplayConfig::getFontName()
{
  return fontName;
}

unsigned int DisplayConfig::getFontSize()
{
  return fontSize;
}

Glib::ustring DisplayConfig::getTextPointerPath()
{
  return textPointerPath;
}

Glib::ustring DisplayConfig::getDataDir()
{
  return dataDir;
}

unsigned int DisplayConfig::getChannel()
{
  return channel;
}

unsigned int DisplayConfig::getNoteGEQ()
{
  return noteGEQ;
}

unsigned int DisplayConfig::getNoteLT()
{
  return noteLT;
}

unsigned int DisplayConfig::getVelGEQ()
{
  return velGEQ;
}

unsigned int DisplayConfig::getVelLT()
{
  return velLT;
}

unsigned int DisplayConfig::getCtrlNum4Fw()
{
  return ctrlNum4Fw;
}

unsigned int DisplayConfig::getCtrlVal4Fw()
{
  return ctrlVal4Fw;
}

unsigned int DisplayConfig::getCtrlNum4Bw()
{
  return ctrlNum4Bw;
}

unsigned int DisplayConfig::getCtrlVal4Bw()
{
  return ctrlVal4Bw;
}

unsigned int DisplayConfig::getNoteRead()
{
  return noteRead;
}

unsigned int DisplayConfig::getVelRead()
{
  return velRead;
}


unsigned int DisplayConfig::getNoteBack()
{
  return noteBack;
}

unsigned int DisplayConfig::getVelBack()
{
  return velBack;
}

unsigned int DisplayConfig::getNoteTheme1()
{
  return noteTheme1;
}

unsigned int DisplayConfig::getVelTheme1()
{
  return velTheme1;
}

unsigned int DisplayConfig::getNoteTheme2()
{
  return noteTheme2;
}

unsigned int DisplayConfig::getVelTheme2()
{
  return velTheme2;
}

unsigned int DisplayConfig::getNoteTheme3()
{
  return noteTheme3;
}

unsigned int DisplayConfig::getVelTheme3()
{
  return velTheme3;
}

unsigned int DisplayConfig::getNotePCKbdEnable()
{
  return notePCKbdEnable;
}

unsigned int DisplayConfig::getNotePCKbdDisable()
{
  return notePCKbdDisable;
}

unsigned int DisplayConfig::getNoteHome()
{
  return noteHome;
}

unsigned int DisplayConfig::getVelHome()
{
  return velHome;
}


unsigned int DisplayConfig::getAreaWidth ()
{
  return areaWidth;
}

unsigned int DisplayConfig::getAreaHeight ()
{
  return areaHeight;
}


void DisplayConfig::readMandatoryParameter(Glib::ustring * p_dest, Glib::KeyFile & p_keyfile, Glib::ustring p_key)
{
  try {
    *p_dest = p_keyfile.get_value("MAIN", p_key);
  } catch (Glib::KeyFileError& ex) {
    std::cout << "Missing key '" << p_key << "' Hardcoded value in use." << std::endl;
  }
}

void DisplayConfig::readNonMandatoryParameter(Glib::ustring * p_dest, Glib::KeyFile & p_keyfile, Glib::ustring p_key, Glib::ustring p_inheritLabel, unsigned int p_th_idx)
{
  try {
    *p_dest = p_keyfile.get_value("MAIN", p_key);
  } catch (Glib::KeyFileError& ex) {
    std::cout << "Missing key '" << p_key << "' color inherited from '" << p_inheritLabel << p_th_idx << "' in use." << std::endl;
    *p_dest = getNamedColor(p_inheritLabel, p_th_idx);
  }
}

Glib::ustring DisplayConfig::getNamedColor(Glib::ustring p_inheritLabel, unsigned int p_th_idx)
{
  if ( p_inheritLabel == "backgroundColor" ) return getBackgroundColor(p_th_idx);
  if ( p_inheritLabel == "sungBackgroundColor" ) return getSungBackgroundColor(p_th_idx);
  if ( p_inheritLabel == "lyricsColor" ) return getLyricsColor(p_th_idx);
  if ( p_inheritLabel == "sungLyricsColor" ) return getSungLyricsColor(p_th_idx);
  if ( p_inheritLabel == "lyricsOutlineColor" ) return getLyricsOutlineColor(p_th_idx);
  if ( p_inheritLabel == "sungLyricsOutlineColor" ) return getSungLyricsOutlineColor(p_th_idx);

  if ( p_inheritLabel == "hintsBackgroundColor" ) return getHintsBackgroundColor(p_th_idx);
  if ( p_inheritLabel == "activeHintsBackgroundColor" ) return getActiveHintsBackgroundColor(p_th_idx);
  if ( p_inheritLabel == "hintsColor" ) return getHintsColor(p_th_idx);
  if ( p_inheritLabel == "activeHintsColor" ) return getActiveHintsColor(p_th_idx);
  if ( p_inheritLabel == "hintsOutlineColor" ) return getHintsOutlineColor(p_th_idx);
  if ( p_inheritLabel == "activeHintsOutlineColor" ) return getActiveHintsOutlineColor(p_th_idx);

  if ( p_inheritLabel == "inactiveLyricsColor" ) return getInactiveLyricsColor(p_th_idx);
  if ( p_inheritLabel == "inactiveLyricsOutlineColor" ) return getInactiveLyricsOutlineColor(p_th_idx);
  if ( p_inheritLabel == "inactiveHintsColor" ) return getInactiveHintsColor(p_th_idx);
  if ( p_inheritLabel == "inactiveHintsOutlineColor" ) getInactiveHintsOutlineColor (p_th_idx);

  std::cout << "WARNING!!! Couldn't get color for label '" << p_inheritLabel << p_th_idx << "'" << std::endl;

  return "FFFF00";
}

int DisplayConfig::readConfig(Glib::ustring filename, bool colorsOnly)
{
  bool result = false;
  Glib::KeyFile keyfile;
  Glib::ustring l_backgroundColor;
  try
  {
    //std::cout << "Reading" << std::endl;
    result = keyfile.load_from_file(filename);
  }
  catch (Glib::Error ex)
  {
    std::cout << "Exception cought during reading config" << std::endl;
  }

  if(!result) return 1;
  
  
  for (int i = 0; i < THEMES_NUM; i++)
  {
    std::ostringstream indexStream;
    indexStream << i;
//     std::cout << "Trying to read " << "backgroundColor" + indexStream.str() << std::endl;
    //mandatory parameters
    readMandatoryParameter(&backgroundColor[i], keyfile, "backgroundColor" + indexStream.str());

    readNonMandatoryParameter(&sungBackgroundColor[i], keyfile, "sungBackgroundColor" + indexStream.str(), "backgroundColor", i);

    readMandatoryParameter(&lyricsColor[i], keyfile, "lyricsColor" + indexStream.str());

    readNonMandatoryParameter(&sungLyricsColor[i], keyfile, "sungLyricsColor" + indexStream.str(), "lyricsColor", i);
    readNonMandatoryParameter(&lyricsOutlineColor[i], keyfile, "lyricsOutlineColor" + indexStream.str(), "backgroundColor", i);
    readNonMandatoryParameter(&sungLyricsOutlineColor[i], keyfile, "sungLyricsOutlineColor" + indexStream.str(), "lyricsOutlineColor", i);

    readNonMandatoryParameter(&hintsBackgroundColor[i], keyfile, "hintsBackgroundColor" + indexStream.str(), "backgroundColor", i);
    readNonMandatoryParameter(&activeHintsBackgroundColor[i], keyfile, "activeHintsBackgroundColor" + indexStream.str(), "sungBackgroundColor", i);

    readNonMandatoryParameter(&hintsColor[i], keyfile, "hintsColor" + indexStream.str(), "lyricsColor", i);
    readNonMandatoryParameter(&activeHintsColor[i], keyfile, "activeHintsColor" + indexStream.str(), "hintsColor", i);

    readNonMandatoryParameter(&hintsOutlineColor[i], keyfile, "hintsOutlineColor" + indexStream.str(), "backgroundColor", i);
    readNonMandatoryParameter(&activeHintsOutlineColor[i], keyfile, "activeHintsOutlineColor" + indexStream.str(), "sungBackgroundColor", i);

    readNonMandatoryParameter(&inactiveLyricsColor[i], keyfile, "inactiveLyricsColor" + indexStream.str(), "lyricsColor", i);
    readNonMandatoryParameter(&inactiveLyricsOutlineColor[i], keyfile, "inactiveLyricsOutlineColor" + indexStream.str(), "lyricsOutlineColor", i);

    readNonMandatoryParameter(&inactiveHintsColor[i], keyfile, "inactiveHintsColor" + indexStream.str(), "hintsColor", i);
    readNonMandatoryParameter(&inactiveHintsOutlineColor[i], keyfile, "inactiveHintsOutlineColor" + indexStream.str(), "hintsOutlineColor", i);
  }
  
  if (colorsOnly) return 0;

  outlineWidth = stod(std::string(keyfile.get_value("MAIN", "outlineWidth").c_str()));
  fontDirPrefix = keyfile.get_value("MAIN", "fontDirPrefix");
  fontName = keyfile.get_value("MAIN", "fontName");
  fontSize = atoi(keyfile.get_value("MAIN", "fontSize").c_str());

  textPointerPath = keyfile.get_value("MAIN", "textPointerPath");
  dataDir = keyfile.get_value("MAIN", "dataDir");
  
  channel = atoi(keyfile.get_value("MAIN", "channel").c_str());
  noteGEQ = atoi(keyfile.get_value("MAIN", "noteGEQ").c_str());
  noteLT = atoi(keyfile.get_value("MAIN", "noteLT").c_str());
  velGEQ = atoi(keyfile.get_value("MAIN", "velGEQ").c_str());
  velLT = atoi(keyfile.get_value("MAIN", "velLT").c_str());

  ctrlNum4Fw = atoi(keyfile.get_value("MAIN", "ctrlNum4Fw").c_str());
  ctrlVal4Fw = atoi(keyfile.get_value("MAIN", "ctrlVal4Fw").c_str());
  ctrlNum4Bw = atoi(keyfile.get_value("MAIN", "ctrlNum4Bw").c_str());
  ctrlVal4Bw = atoi(keyfile.get_value("MAIN", "ctrlVal4Bw").c_str());

  noteRead = atoi(keyfile.get_value("MAIN", "noteRead").c_str());
  velRead = atoi(keyfile.get_value("MAIN", "velRead").c_str());

  noteBack = atoi(keyfile.get_value("MAIN", "noteBack").c_str());
  velBack = atoi(keyfile.get_value("MAIN", "velBack").c_str());

  noteTheme1 = atoi(keyfile.get_value("MAIN", "noteTheme1").c_str());
  velTheme1 = atoi(keyfile.get_value("MAIN", "velTheme1").c_str());

  noteTheme2 = atoi(keyfile.get_value("MAIN", "noteTheme2").c_str());
  velTheme2 = atoi(keyfile.get_value("MAIN", "velTheme2").c_str());

  noteTheme3 = atoi(keyfile.get_value("MAIN", "noteTheme3").c_str());
  velTheme3 = atoi(keyfile.get_value("MAIN", "velTheme3").c_str());

  notePCKbdEnable = atoi(keyfile.get_value("MAIN", "notePCKbdEnable").c_str());
  notePCKbdDisable = atoi(keyfile.get_value("MAIN", "notePCKbdDisable").c_str());

  noteHome = atoi(keyfile.get_value("MAIN", "noteHome").c_str());
  velHome = atoi(keyfile.get_value("MAIN", "velHome").c_str());

  areaWidth = atoi(keyfile.get_value("MAIN", "areaWidth").c_str());
  areaHeight = atoi(keyfile.get_value("MAIN", "areaHeight").c_str());

  return 0;
}
