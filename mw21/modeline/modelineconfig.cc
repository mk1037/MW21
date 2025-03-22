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

#include "modelineconfig.h"
#include <glibmm/keyfile.h>

ModelineConfig::ModelineConfig() {
  backgroundColor[0]        = "e4e4e4ff";
  sungBackgroundColor[0]    = "f4f4f4ff";
  lyricsColor[0]            = "ffffff";
  sungLyricsColor[0]        = "ff0000";
  lyricsOutlineColor[0]     = "000000";
  sungLyricsOutlineColor[0] = "000000";
  hintsBackgroundColor[0]   = "343434ff";
  activeHintsBackgroundColor[0] = "838383ff";
  hintsColor[0]              = "848484";
  activeHintsColor[0]        = "b4b4b4";
  hintsOutlineColor[0]       = "202020";
  activeHintsOutlineColor[0] = "707070";

  backgroundColor[1]        = "e4e424ff";
  sungBackgroundColor[1]    = "f4f422ff";
  lyricsColor[1]            = "ffff2f";
  sungLyricsColor[1]        = "ff0020";
  lyricsOutlineColor[1]     = "000020";
  sungLyricsOutlineColor[1] = "000020";
  hintsBackgroundColor[1]   = "343424ff";
  activeHintsBackgroundColor[1] = "838323ff";
  hintsColor[1]              = "848424";
  activeHintsColor[1]        = "b4b424";
  hintsOutlineColor[1]       = "f02020";
  activeHintsOutlineColor[1] = "707020";

  backgroundColor[2]        = "34e4a4ff";
  sungBackgroundColor[2]    = "f4f422ff";
  lyricsColor[2]            = "ffff2f";
  sungLyricsColor[2]        = "ff0020";
  lyricsOutlineColor[2]     = "000020";
  sungLyricsOutlineColor[2] = "000020";
  hintsBackgroundColor[2]   = "343424ff";
  activeHintsBackgroundColor[2] = "838323ff";
  hintsColor[2]              = "848424";
  activeHintsColor[2]        = "b4b424";
  hintsOutlineColor[2]       = "f02020";
  activeHintsOutlineColor[2] = "707020";


  modelineBackgroundColor_neutral1         = "000000ff";
  modelineBackgroundColor_neutral2         = "babdb6ff";
  modelineBackgroundColor_blink1           = "ffffffff";
  modelineBackgroundColor_blink2           = "ef2929ff";
  modelineBackgroundColor_ok               = "3d7d00ff";
  modelineBackgroundColor_search           = "fcaf3eff";
  modelineBackgroundColor_found            = "fcffaeff";

  modelineFontColor_neutral1               = "f3f3f3";
  modelineFontColor_neutral2               = "ffffff";
  modelineFontColor_blink1                 = "ef2929";
  modelineFontColor_blink2                 = "ffffff";
  modelineFontColor_ok                     = "ffffff";
  modelineFontColor_search                 = "ffffff";
  modelineFontColor_found                  = "bd0052";

  modelineOutlineColor_neutral1            = "888a85";
  modelineOutlineColor_neutral2            = "000000";
  modelineOutlineColor_blink1              = "000000";
  modelineOutlineColor_blink2              = "000000";
  modelineOutlineColor_ok                  = "000000";
  modelineOutlineColor_search              = "000000";
  modelineOutlineColor_found               = "000000";

  instructionPath        = "/tmp/modeline_instruction";
  pidPath                = "/tmp/modeline_pid";

  seqControllerInstruction  = "/tmp/seq_controller_instruction";
  SCTrapPidPath             = "/tmp/sc_trap_pid";

  outlineWidth           = 0.7;
  fontDirPrefix          = "/usr/share/fonts/truetype/dejavu/";
  fontName               = "DejaVuSerif-BoldItalic.ttf";
  fontSize               = 30;

  modelineAreaWidth         = 530;
  modelineAreaHeight        = 70;
  firstRow                  = true;
  secondRow                 = true;

  blinkCounter              = 8;
  blinkPeriod               = 250;
  timeout                   = 1000;

  modelineControlChannel         = 1;
  textPointerPath                = "/tmp/textpath";
  dataDir                        = "/tmp/data";
}

Glib::ustring ModelineConfig::getBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return backgroundColor[p_idx];
  return backgroundColor[0];
}

Glib::ustring ModelineConfig::getSungBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return sungBackgroundColor[p_idx];
  return sungBackgroundColor[0];
}

Glib::ustring ModelineConfig::getLyricsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return lyricsColor[p_idx];
  return lyricsColor[0];
}

Glib::ustring ModelineConfig::getSungLyricsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return sungLyricsColor[p_idx];
  return sungLyricsColor[0];
}

Glib::ustring ModelineConfig::getLyricsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return lyricsOutlineColor[p_idx];
  return lyricsOutlineColor[0];
}

Glib::ustring ModelineConfig::getSungLyricsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return sungLyricsOutlineColor[p_idx];
  return sungLyricsOutlineColor[0];
}

Glib::ustring ModelineConfig::getHintsBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return hintsBackgroundColor[p_idx];
  return hintsBackgroundColor[0];
}

Glib::ustring ModelineConfig::getActiveHintsBackgroundColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return activeHintsBackgroundColor[p_idx];
  return activeHintsBackgroundColor[0];
}

Glib::ustring ModelineConfig::getHintsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return hintsColor[p_idx];
  return hintsColor[0];
}

Glib::ustring ModelineConfig::getActiveHintsColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return activeHintsColor[p_idx];
  return activeHintsColor[0];
}

Glib::ustring ModelineConfig::getHintsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return hintsOutlineColor[p_idx];
  return hintsOutlineColor[0];
}

Glib::ustring ModelineConfig::getActiveHintsOutlineColor(unsigned int p_idx)
{
  if(p_idx < THEMES_NUM) return activeHintsOutlineColor[p_idx];
  return activeHintsOutlineColor[0];
}




Glib::ustring ModelineConfig::getModelineBackgroundColor_neutral1()
{
  return modelineBackgroundColor_neutral1;
}

Glib::ustring ModelineConfig::getModelineBackgroundColor_neutral2()
{
  return modelineBackgroundColor_neutral2;
}

Glib::ustring ModelineConfig::getModelineBackgroundColor_blink1()
{
  return modelineBackgroundColor_blink1;
}

Glib::ustring ModelineConfig::getModelineBackgroundColor_blink2()
{
  return modelineBackgroundColor_blink2;
}

Glib::ustring ModelineConfig::getModelineBackgroundColor_ok()
{
  return modelineBackgroundColor_ok;
}

Glib::ustring ModelineConfig::getModelineBackgroundColor_search()
{
  return modelineBackgroundColor_search;
}

Glib::ustring ModelineConfig::getModelineBackgroundColor_found()
{
  return modelineBackgroundColor_found;
}



Glib::ustring ModelineConfig::getModelineFontColor_neutral1()
{
  return modelineFontColor_neutral1;
}

Glib::ustring ModelineConfig::getModelineFontColor_neutral2()
{
  return modelineFontColor_neutral2;
}

Glib::ustring ModelineConfig::getModelineFontColor_blink1()
{
  return modelineFontColor_blink1;
}

Glib::ustring ModelineConfig::getModelineFontColor_blink2()
{
  return modelineFontColor_blink2;
}

Glib::ustring ModelineConfig::getModelineFontColor_ok()
{
  return modelineFontColor_ok;
}

Glib::ustring ModelineConfig::getModelineFontColor_search()
{
  return modelineFontColor_search;
}

Glib::ustring ModelineConfig::getModelineFontColor_found()
{
  return modelineFontColor_found;
}



Glib::ustring ModelineConfig::getModelineOutlineColor_neutral1()
{
  return modelineOutlineColor_neutral1;
}

Glib::ustring ModelineConfig::getModelineOutlineColor_neutral2()
{
  return modelineOutlineColor_neutral2;
}

Glib::ustring ModelineConfig::getModelineOutlineColor_blink1()
{
  return modelineOutlineColor_blink1;
}

Glib::ustring ModelineConfig::getModelineOutlineColor_blink2()
{
  return modelineOutlineColor_blink2;
}

Glib::ustring ModelineConfig::getModelineOutlineColor_ok()
{
  return modelineOutlineColor_ok;
}

Glib::ustring ModelineConfig::getModelineOutlineColor_search()
{
  return modelineOutlineColor_search;
}

Glib::ustring ModelineConfig::getModelineOutlineColor_found()
{
  return modelineOutlineColor_found;
}


Glib::ustring ModelineConfig::getPidPath()
{
  return pidPath;
}

Glib::ustring ModelineConfig::getInstructionPath()
{
  return instructionPath;
}

double ModelineConfig::getOutlineWidth()
{
  return outlineWidth;
}

Glib::ustring ModelineConfig::getFontDirPrefix()
{
  return fontDirPrefix;
}

Glib::ustring ModelineConfig::getFontName()
{
  return fontName;
}

unsigned int ModelineConfig::getFontSize()
{
  return fontSize;
}

Glib::ustring ModelineConfig::getTextPointerPath()
{
  return textPointerPath;
}

Glib::ustring ModelineConfig::getDataDir()
{
  return dataDir;
}

unsigned int ModelineConfig::getModelineControlChannel()
{
  return modelineControlChannel;
}

unsigned int ModelineConfig::getModelineAreaWidth()
{
  return modelineAreaWidth;
}

unsigned int ModelineConfig::getModelineAreaHeight()
{
  return modelineAreaHeight;
}

bool ModelineConfig::getFirstRow()
{
  return firstRow;
}

bool ModelineConfig::getSecondRow()
{
  return secondRow;
}

unsigned int ModelineConfig::getBlinkCounter()
{
  return blinkCounter;
}

unsigned int ModelineConfig::getBlinkPeriod()
{
  return blinkPeriod;
}

unsigned int ModelineConfig::getTimeout()
{
  return timeout;
}

Glib::ustring ModelineConfig::getSeqControllerInstruction()
{
  return seqControllerInstruction;
}

Glib::ustring ModelineConfig::getSCTrapPidPath()
{
  return SCTrapPidPath;
}

Glib::ustring ModelineConfig::getStarterInstructionPath()
{
  return starterInstructionPath;
}

Glib::ustring ModelineConfig::getStarterPidPath()
{
  return starterPidPath;
}


int ModelineConfig::readConfig(Glib::ustring filename)
{
  bool result = false;
  Glib::KeyFile keyfile;
  Glib::ustring l_backgroundColor;
  Glib::ustring l_firstRowText;
  Glib::ustring l_secondRowText;
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
    //std::cout << "Trying to read " << "backgroundColor" + indexStream.str() << std::endl;
    backgroundColor[i] = keyfile.get_value("MAIN", "backgroundColor" + indexStream.str());
    sungBackgroundColor[i] = keyfile.get_value("MAIN", "sungBackgroundColor" + indexStream.str());
    lyricsColor[i] = keyfile.get_value("MAIN", "lyricsColor" + indexStream.str());
    sungLyricsColor[i] = keyfile.get_value("MAIN", "sungLyricsColor" + indexStream.str());
    lyricsOutlineColor[i] = keyfile.get_value("MAIN", "lyricsOutlineColor" + indexStream.str());
    sungLyricsOutlineColor[i] = keyfile.get_value("MAIN", "sungLyricsOutlineColor" + indexStream.str());

    hintsBackgroundColor[i] = keyfile.get_value("MAIN", "hintsBackgroundColor" + indexStream.str());
    activeHintsBackgroundColor[i] = keyfile.get_value("MAIN", "activeHintsBackgroundColor" + indexStream.str());
    hintsColor[i] = keyfile.get_value("MAIN", "hintsColor" + indexStream.str());
    activeHintsColor[i] = keyfile.get_value("MAIN", "activeHintsColor" + indexStream.str());
    hintsOutlineColor[i] = keyfile.get_value("MAIN", "hintsOutlineColor" + indexStream.str());
    activeHintsOutlineColor[i] = keyfile.get_value("MAIN", "activeHintsOutlineColor" + indexStream.str());
  }


  modelineBackgroundColor_neutral1 = keyfile.get_value("MAIN", "modelineBackgroundColor_neutral1");
  modelineBackgroundColor_neutral2 = keyfile.get_value("MAIN", "modelineBackgroundColor_neutral2");
  modelineBackgroundColor_blink1 = keyfile.get_value("MAIN", "modelineBackgroundColor_blink1");
  modelineBackgroundColor_blink2 = keyfile.get_value("MAIN", "modelineBackgroundColor_blink2");
  modelineBackgroundColor_ok = keyfile.get_value("MAIN", "modelineBackgroundColor_ok");
  modelineBackgroundColor_search = keyfile.get_value("MAIN", "modelineBackgroundColor_search");
  modelineBackgroundColor_found = keyfile.get_value("MAIN", "modelineBackgroundColor_found");

  modelineFontColor_neutral1 = keyfile.get_value("MAIN", "modelineFontColor_neutral1");
  modelineFontColor_neutral2 = keyfile.get_value("MAIN", "modelineFontColor_neutral2");
  modelineFontColor_blink1 = keyfile.get_value("MAIN", "modelineFontColor_blink1");
  modelineFontColor_blink2 = keyfile.get_value("MAIN", "modelineFontColor_blink2");
  modelineFontColor_ok = keyfile.get_value("MAIN", "modelineFontColor_ok");
  modelineFontColor_search = keyfile.get_value("MAIN", "modelineFontColor_search");
  modelineFontColor_found = keyfile.get_value("MAIN", "modelineFontColor_found");

  modelineOutlineColor_neutral1 = keyfile.get_value("MAIN", "modelineOutlineColor_neutral1");
  modelineOutlineColor_neutral2 = keyfile.get_value("MAIN", "modelineOutlineColor_neutral2");
  modelineOutlineColor_blink1 = keyfile.get_value("MAIN", "modelineOutlineColor_blink1");
  modelineOutlineColor_blink2 = keyfile.get_value("MAIN", "modelineOutlineColor_blink2");
  modelineOutlineColor_ok = keyfile.get_value("MAIN", "modelineOutlineColor_ok");
  modelineOutlineColor_search = keyfile.get_value("MAIN", "modelineOutlineColor_search");
  modelineOutlineColor_found = keyfile.get_value("MAIN", "modelineOutlineColor_found");

  instructionPath = keyfile.get_value("MAIN", "modeline_instruction");
  pidPath = keyfile.get_value("MAIN", "modeline_pid");

  seqControllerInstruction = keyfile.get_value("MAIN", "seq_controller_instruction");
  SCTrapPidPath = keyfile.get_value("MAIN", "sc_trap_pid_path");

  starterInstructionPath = keyfile.get_value("MAIN", "STARTER_instruction");
  starterPidPath = keyfile.get_value("MAIN", "STARTER_pid");

  outlineWidth = stod(std::string(keyfile.get_value("MAIN", "outlineWidth").c_str()));
  fontDirPrefix = keyfile.get_value("MAIN", "fontDirPrefix");
  fontName = keyfile.get_value("MAIN", "fontName");
  fontSize = atoi(keyfile.get_value("MAIN", "fontSize").c_str());

  modelineAreaWidth = atoi(keyfile.get_value("MAIN", "modelineAreaWidth").c_str());
  modelineAreaHeight = atoi(keyfile.get_value("MAIN", "modelineAreaHeight").c_str());

  l_secondRowText = keyfile.get_value("MAIN", "secondRow");
  if (l_secondRowText.lowercase() == "false")
    secondRow = false;

  l_firstRowText = keyfile.get_value("MAIN", "firstRow");
  if (l_firstRowText.lowercase() == "false" && secondRow == true)
    firstRow = false;

  blinkCounter = atoi(keyfile.get_value("MAIN", "blinkCounter").c_str());
  blinkPeriod = atoi(keyfile.get_value("MAIN", "blinkPeriod").c_str());
  timeout = atoi(keyfile.get_value("MAIN", "timeout").c_str());

  modelineControlChannel = atoi(keyfile.get_value("MAIN", "modelineControlChannel").c_str());
  textPointerPath = keyfile.get_value("MAIN", "textPointerPath");
  dataDir = keyfile.get_value("MAIN", "dataDir");

  return 0;
}
