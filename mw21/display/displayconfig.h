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

#ifndef DISPLAYCONFIG_H
#define DISPLAYCONFIG_H

#define THEMES_NUM 3

#include <gtkmm.h>
#include <iostream>

class DisplayConfig
{
public:
  DisplayConfig();

private:
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

  Glib::ustring inactiveLyricsColor[THEMES_NUM];
  Glib::ustring inactiveLyricsOutlineColor[THEMES_NUM];
  Glib::ustring inactiveHintsColor[THEMES_NUM];
  Glib::ustring inactiveHintsOutlineColor[THEMES_NUM];

  Glib::ustring visitedBackgroundColor[THEMES_NUM];
  Glib::ustring visitedHintsBackgroundColor[THEMES_NUM];
  Glib::ustring visitedLyricsColor[THEMES_NUM];
  Glib::ustring visitedLyricsOutlineColor[THEMES_NUM];
  Glib::ustring visitedHintsColor[THEMES_NUM];
  Glib::ustring visitedHintsOutlineColor[THEMES_NUM];

  double outlineWidth;

  Glib::ustring fontDirPrefix;
  Glib::ustring fontName;
  unsigned int fontSize;

  Glib::ustring textPointerPath;
  Glib::ustring dataDir;

  unsigned int channel;
  unsigned int noteGEQ;
  unsigned int noteLT;
  unsigned int velGEQ;
  unsigned int velLT;

  unsigned int ctrlNum4Fw;
  unsigned int ctrlVal4Fw;
  unsigned int ctrlNum4Bw;
  unsigned int ctrlVal4Bw;

  unsigned int ctrlNumGroupSel;

  unsigned int noteRead;
  unsigned int velRead;
  unsigned int noteBack;
  unsigned int velBack;
  unsigned int noteTheme1;
  unsigned int velTheme1;
  unsigned int noteTheme2;
  unsigned int velTheme2;
  unsigned int noteTheme3;
  unsigned int velTheme3;
  unsigned int noteHome;
  unsigned int velHome;

  unsigned int notePCKbdEnable; //positive
  unsigned int notePCKbdDisable; //positive

  unsigned int areaWidth;
  unsigned int areaHeight;

  void readMandatoryParameter(Glib::ustring * p_dest, Glib::KeyFile & p_keyfile, Glib::ustring p_key);
  void readNonMandatoryParameter(Glib::ustring * p_dest, Glib::KeyFile & p_keyfile, Glib::ustring p_key, Glib::ustring p_inheritLabel, unsigned int p_th_idx);
  Glib::ustring getNamedColor(Glib::ustring p_inheritLabel, unsigned int p_th_idx);

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

  Glib::ustring getInactiveLyricsColor(unsigned int p_th_idx);
  Glib::ustring getInactiveLyricsOutlineColor(unsigned int p_th_idx);
  Glib::ustring getInactiveHintsColor(unsigned int p_th_idx);
  Glib::ustring getInactiveHintsOutlineColor(unsigned int p_th_idx);

  Glib::ustring getVisitedBackgroundColor(unsigned int p_th_idx);
  Glib::ustring getVisitedHintsBackgroundColor(unsigned int p_th_idx);
  Glib::ustring getVisitedLyricsColor(unsigned int p_th_idx);
  Glib::ustring getVisitedLyricsOutlineColor(unsigned int p_th_idx);
  Glib::ustring getVisitedHintsColor(unsigned int p_th_idx);
  Glib::ustring getVisitedHintsOutlineColor(unsigned int p_th_idx);

  double getOutlineWidth();

  Glib::ustring getFontDirPrefix();
  Glib::ustring getFontName();
  unsigned int getFontSize();

  Glib::ustring getTextPointerPath();
  Glib::ustring getDataDir();
  
  unsigned int getChannel();
  unsigned int getNoteGEQ();
  unsigned int getNoteLT();
  unsigned int getVelGEQ();
  unsigned int getVelLT();

  unsigned int getCtrlNum4Fw();
  unsigned int getCtrlVal4Fw();
  unsigned int getCtrlNum4Bw();
  unsigned int getCtrlVal4Bw();

  unsigned int getCtrlNumGroupSel();

  unsigned int getNoteRead();
  unsigned int getVelRead();

  unsigned int getNoteBack();
  unsigned int getVelBack();

  unsigned int getNoteTheme1();
  unsigned int getVelTheme1();

  unsigned int getNoteTheme2();
  unsigned int getVelTheme2();

  unsigned int getNoteTheme3();
  unsigned int getVelTheme3();

  unsigned int getNoteHome();
  unsigned int getVelHome();

  unsigned int getNotePCKbdEnable();
  unsigned int getNotePCKbdDisable();

  unsigned int getAreaWidth();
  unsigned int getAreaHeight();

  int readConfig(Glib::ustring filename, bool colorsOnly = false);
};

#endif // DISPLAYCONFIG_H

