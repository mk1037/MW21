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

#ifndef MODELINECONFIG_H
#define MODELINECONFIG_H

#define THEMES_NUM 3

#define THEME_BANK_1 0
#define THEME_BANK_2 1
#define THEME_BANK_3 2

#define THEME_NEUTRAL_1 3
#define THEME_NEUTRAL_2 4
#define THEME_BLINK_1   5
#define THEME_BLINK_2   6
#define THEME_OK        7
#define THEME_SEARCH    8
#define THEME_FOUND     9


#include <gtkmm.h>
#include <iostream>

class ModelineConfig
{
public:
  ModelineConfig();

private:
  // ############# DISPLAY COLOURS ##############
  Glib::ustring backgroundColor[THEMES_NUM];
  Glib::ustring sungBackgroundColor[THEMES_NUM];
  Glib::ustring lyricsColor[THEMES_NUM];
  Glib::ustring sungLyricsColor[THEMES_NUM];
  Glib::ustring lyricsOutlineColor[THEMES_NUM];
  Glib::ustring sungLyricsOutlineColor[THEMES_NUM];

  Glib::ustring hintsBackgroundColor[THEMES_NUM];
  Glib::ustring activeHintsBackgroundColor[THEMES_NUM];
  Glib::ustring hintsColor[THEMES_NUM];
  Glib::ustring activeHintsColor[THEMES_NUM];
  Glib::ustring hintsOutlineColor[THEMES_NUM];
  Glib::ustring activeHintsOutlineColor[THEMES_NUM];

  // ############# MODELINE COLOURS ##############
  Glib::ustring modelineBackgroundColor_neutral1;
  Glib::ustring modelineBackgroundColor_neutral2;
  Glib::ustring modelineBackgroundColor_blink1  ;
  Glib::ustring modelineBackgroundColor_blink2;
  Glib::ustring modelineBackgroundColor_ok;
  Glib::ustring modelineBackgroundColor_search;
  Glib::ustring modelineBackgroundColor_found;

  Glib::ustring modelineFontColor_neutral1;
  Glib::ustring modelineFontColor_neutral2;
  Glib::ustring modelineFontColor_blink1;
  Glib::ustring modelineFontColor_blink2;
  Glib::ustring modelineFontColor_ok;
  Glib::ustring modelineFontColor_search;
  Glib::ustring modelineFontColor_found;

  Glib::ustring modelineOutlineColor_neutral1;
  Glib::ustring modelineOutlineColor_neutral2;
  Glib::ustring modelineOutlineColor_blink1;
  Glib::ustring modelineOutlineColor_blink2;
  Glib::ustring modelineOutlineColor_ok;
  Glib::ustring modelineOutlineColor_search;
  Glib::ustring modelineOutlineColor_found;

  Glib::ustring instructionPath;
  Glib::ustring pidPath;

  Glib::ustring seqControllerInstruction;
  Glib::ustring SCTrapPidPath;

  Glib::ustring starterInstructionPath;
  Glib::ustring starterPidPath;

  double outlineWidth;
  Glib::ustring fontDirPrefix;
  Glib::ustring fontName;
  unsigned int fontSize;

  unsigned int modelineAreaWidth;
  unsigned int modelineAreaHeight;
  bool firstRow;
  bool secondRow;

  unsigned int blinkCounter;
  unsigned int blinkPeriod;
  unsigned int timeout;

  unsigned int modelineControlChannel;
  Glib::ustring textPointerPath;
  Glib::ustring dataDir;

public:
  Glib::ustring getBackgroundColor(unsigned int p_th_idx);
  Glib::ustring getSungBackgroundColor(unsigned int p_th_idx);
  Glib::ustring getLyricsColor(unsigned int p_th_idx);
  Glib::ustring getSungLyricsColor(unsigned int p_th_idx);
  Glib::ustring getLyricsOutlineColor(unsigned int p_th_idx);
  Glib::ustring getSungLyricsOutlineColor(unsigned int p_th_idx);

  Glib::ustring getHintsBackgroundColor(unsigned int p_th_idx);
  Glib::ustring getActiveHintsBackgroundColor(unsigned int p_th_idx);
  Glib::ustring getHintsColor(unsigned int p_th_idx);
  Glib::ustring getActiveHintsColor(unsigned int p_th_idx);
  Glib::ustring getHintsOutlineColor(unsigned int p_th_idx);
  Glib::ustring getActiveHintsOutlineColor(unsigned int p_th_idx);

  Glib::ustring getModelineBackgroundColor_neutral1();
  Glib::ustring getModelineBackgroundColor_neutral2();
  Glib::ustring getModelineBackgroundColor_blink1  ();
  Glib::ustring getModelineBackgroundColor_blink2();
  Glib::ustring getModelineBackgroundColor_ok();
  Glib::ustring getModelineBackgroundColor_search();
  Glib::ustring getModelineBackgroundColor_found();

  Glib::ustring getModelineFontColor_neutral1();
  Glib::ustring getModelineFontColor_neutral2();
  Glib::ustring getModelineFontColor_blink1();
  Glib::ustring getModelineFontColor_blink2();
  Glib::ustring getModelineFontColor_ok();
  Glib::ustring getModelineFontColor_search();
  Glib::ustring getModelineFontColor_found();

  Glib::ustring getModelineOutlineColor_neutral1();
  Glib::ustring getModelineOutlineColor_neutral2();
  Glib::ustring getModelineOutlineColor_blink1();
  Glib::ustring getModelineOutlineColor_blink2();
  Glib::ustring getModelineOutlineColor_ok();
  Glib::ustring getModelineOutlineColor_search();
  Glib::ustring getModelineOutlineColor_found();

  Glib::ustring getInstructionPath();
  Glib::ustring getPidPath();

  Glib::ustring getSeqControllerInstruction();
  Glib::ustring getSCTrapPidPath();

  Glib::ustring getStarterInstructionPath();
  Glib::ustring getStarterPidPath();

  double getOutlineWidth();
  Glib::ustring getFontDirPrefix();
  Glib::ustring getFontName();
  unsigned int getFontSize();

  unsigned int getModelineAreaWidth();
  unsigned int getModelineAreaHeight();
  bool getFirstRow();
  bool getSecondRow();

  unsigned int getBlinkCounter();
  unsigned int getBlinkPeriod();
  unsigned int getTimeout();

  unsigned int getModelineControlChannel();
  Glib::ustring getTextPointerPath();
  Glib::ustring getDataDir();


  int readConfig(Glib::ustring filename);
};

#endif // MODELINECONFIG_H

