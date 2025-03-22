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

#ifndef MODELINE_GRAPHICS_H
#define MODELINE_GRAPHICS_H

#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_STROKER_H

#include <gtkmm.h>
#include <vector>
#include <fstream>
#include <iostream>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

struct Pixel32
{
  public:
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;

    Pixel32() {r = 0; g = 0; b = 0; a = 0;}

    Pixel32(uint8 ri, uint8 gi, uint8 bi, uint8 ai = 255)
    {
      r = ri;
      g = gi;
      b = bi;
      a = ai;
    }
    void print_this() { std::cout << "Pixel32(" << (int)r << ", " << (int)g << ", " << (int)b <<", " << (int)a << ")" << std::endl;}
};

typedef struct Pixel32 Pixel32;

struct Vec2
{
  Vec2() { }
  Vec2(float a, float b)
  : x(a), y(b) { }

  float x, y;
};


struct Rect
{
  Rect() { }
  Rect(float left, float top, float right, float bottom)
  : xmin(left), xmax(right), ymin(top), ymax(bottom) { }

  void Include(const Vec2 &r)
  {
    xmin = std::min(xmin, r.x);
    ymin = std::min(ymin, r.y);
    xmax = std::max(xmax, r.x);
    ymax = std::max(ymax, r.y);
  }

  float Width() const { return xmax - xmin + 1; }
  float Height() const { return ymax - ymin + 1; }

  float xmin, xmax, ymin, ymax;
};

struct Span
{
  Span() { }
  Span(int _x, int _y, int _width, int _coverage)
  : x(_x), y(_y), width(_width), coverage(_coverage) { }

  int x, y, width, coverage;
};

typedef std::vector<Span> Spans;

void RenderSpans(FT_Library &library,
            FT_Outline * const outline,
            Spans *spans);

void RasterCallback(const int y,
               const int count,
               const FT_Span * const spans,
               void * const user);

uint8 get_sub_value(Glib::ustring code, int offset);
uint8 get_red_value(Glib::ustring code);
uint8 get_blue_value(Glib::ustring code);
uint8 get_green_value(Glib::ustring code);
uint8 get_alpha_value(Glib::ustring code);

guint32 get_int_color(Glib::ustring code);


#endif // MODELINE_GRAPHICS_H
