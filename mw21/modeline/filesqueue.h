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

#ifndef MODELINE_FILESQUEUE_H
#define MODELINE_FILESQUEUE_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <gtkmm.h>
#include <giomm.h>
#include <glibmm/regex.h>
#include <iomanip>

class FilesQueue
{
  private:
    std::vector <Glib::ustring> items;
    int pointer;
    Glib::ustring filenamePattern;
    Glib::RefPtr<Glib::Regex> filenamePatternRegex;
  public:
    FilesQueue();
    Glib::ustring getItem(int p_idx) const;
    int getPointer() const;
    int readDir(Glib::ustring p_absDir);
    char setAtChar(char p_char);
    void setAtIndex(unsigned int p_index);
    void increase();
    void decrease();
    char decreaseChar();
    char increaseChar();
    void print();
};


#endif // MODELINE_FILESQUEUE_H
