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

#include "framecontent.h"

FrameContent::FrameContent()
{
  for (int i = 0; i < LINES_NUM; i++)
  {
    left[i] = "";
    right[i] = "";
    is_hint[i] = false;
    state[i] = INACTIVE;
  }
}

void FrameContent::set_content(int index, Glib::ustring p_left, Glib::ustring p_right, int p_state, bool p_hint)
{
  if (index < 0) index = -index;
  index = index % 4;

  left[index] = p_left;
  right[index] = p_right;
  state[index] = p_state;
  is_hint[index] = p_hint;
}


void FrameContent::print()
{
  std::cout << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" << std::endl;
  for (int i = 0; i < LINES_NUM; i++)
  {
    if(is_hint[i]) std::cout << "~";
    else std::cout << " ";
    if(state[i] == ACTIVE) std::cout << ">";
    else if (state[i] == VISITED) std::cout << "x";
    else std::cout << " ";

    std::cout << left[i] << "|" << right[i] << std::endl;
  }
  std::cout << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" << std::endl;
}
