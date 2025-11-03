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

#ifndef DISPLAY_FRAMECONTENT_H
#define DISPLAY_FRAMECONTENT_H

#define LINES_NUM 4

#include <gtkmm.h>
#include <iostream>

enum LineState
{
  INACTIVE,
  ACTIVE,
  VISITED
};

class FrameContent
{
  public:
    FrameContent();
    Glib::ustring left[LINES_NUM];
    Glib::ustring right[LINES_NUM];
    int state[LINES_NUM];
    bool is_hint[LINES_NUM];
    void print();
    void set_content(int index, Glib::ustring p_left, Glib::ustring p_right, int p_state, bool p_hint);
};

#endif // DISPLAY_DISPLAYWIN_H
