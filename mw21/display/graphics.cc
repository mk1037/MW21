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

#include "graphics.h"

void RasterCallback(const int y,
               const int count,
               const FT_Span * const spans,
               void * const user) 
{
  Spans *sptr = (Spans *)user;
  for (int i = 0; i < count; ++i) {
      //std::cout << "Pushing Span(" << spans[i].x << ", " << y << ", " << spans[i].len << ", " << (int)spans[i].coverage << ")" << std::endl;
    sptr->push_back(Span(spans[i].x, y, spans[i].len, spans[i].coverage));
  }
}

void RenderSpans(FT_Library &library,
            FT_Outline * const outline,
            Spans *spans) 
{
  FT_Raster_Params params;
  memset(&params, 0, sizeof(params));
  params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
  params.gray_spans = RasterCallback;
  params.user = spans;

  FT_Outline_Render(library, outline, &params);
}

uint8 get_sub_value(Glib::ustring code, int offset)
{
  if (code.length() < 6) return 0;
  int x;

  std::stringstream ss;
  ss << std::hex << code.substr(offset, 2);
  ss >> x;

  return x;
}

uint8 get_red_value(Glib::ustring code)
{
  return (uint8)get_sub_value(code, 0);
}

uint8 get_green_value(Glib::ustring code)
{
  return (uint8)get_sub_value(code, 2);
}

uint8 get_blue_value(Glib::ustring code)
{
  return (uint8)get_sub_value(code, 4);
}

uint8 get_alpha_value(Glib::ustring code)
{
  if (code.length() < 8) return 0;
  return (uint8)get_sub_value(code, 6);
}

guint32 get_int_color(Glib::ustring code)
{
  return (guint32)
    (((guint32) get_red_value(code)) << 3*8) +
    (((guint32) get_green_value(code)) << 2*8) +
    (((guint32) get_blue_value(code)) << 8) +
    ((guint32) get_alpha_value(code));
}
