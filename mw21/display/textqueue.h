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

#ifndef DISPLAYTEXTQUEUE_H
#define DISPLAYTEXTQUEUE_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <gtkmm.h>
#include <giomm.h>
#include <iomanip>
#include "framecontent.h"

class TextLine
{
  private:
    std::vector <Glib::ustring> chunks;
    int chunk_pointer;
    bool is_hint;
  public:
    TextLine();
    void print();
    void push(Glib::ustring chunk);
    void clear();
    void set_hint(bool hint);
    bool get_hint();
    int get_size();
    Glib::ustring get_left(int i);
    Glib::ustring get_right(int i);
};

class TextQueue
{
  private:
    std::vector <TextLine> lines;
    std::vector <unsigned int> groups;
    int pointer;
    int line_pointer;
    int chunk_pointer;
    bool reached_end;
    int group_pointer;
    int group_chunk_pointer;
    unsigned int groups_accumulative_value();
  public:
    TextQueue();
    int read_lines(Glib::ustring path, Glib::ustring p_file_name);
    void set_pointer(int value);
    void set_group_pointer(int value);
    int get_pointer();
    int get_group_pointer();
    int get_group_chunk_pointer();
    unsigned int get_groups_num();
    unsigned int get_group_size(unsigned int i);
    void print();
    int get_size();
    int lines_num();
    FrameContent get_frame();
    void clear();
    bool has_reached_end();
    void unset_reached_end();
    void set_notext(Glib::ustring p_file_name);
    void set_notextpath();
};

std::string ltrim( std::string str );

std::string rtrim( std::string str );

std::string trim( std::string str );

#endif // DISPLAYTEXTQUEUE_H
