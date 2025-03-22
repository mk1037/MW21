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

#ifndef MODELINE_MODELINEAREA_H
#define MODELINE_MODELINEAREA_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include "modelineconfig.h"
#include "graphics.h"


class ModelineArea : public Gtk::DrawingArea
{
public:
  ModelineArea(FT_Library *p_lib, FT_Face *p_face, unsigned int p_width);
  virtual ~ModelineArea();
  void render_string(Glib::ustring &string, bool fade_out, bool p_sep = false);
  void set_config(ModelineConfig *pconfig);
  void initialize(unsigned int p_theme_idx);
  void set_color_theme(int p_idx);

  void paste_pixbuf(Glib::RefPtr<Gdk::Pixbuf> where, Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y);
  void paste_pixbuf(Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y);
  void paste_blend_pixbuf(Glib::RefPtr<Gdk::Pixbuf> where, Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y);
  void paste_blend_pixbuf(Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y);
  void set_pixel(Glib::RefPtr<Gdk::Pixbuf> where, Pixel32 *pixel, int x, int y);
  void set_pixel(Pixel32 *pixel, int x, int y);
  void set_pixel_opacity(Glib::RefPtr<Gdk::Pixbuf> where, unsigned char p_opacity, int x, int y);
//   void Print(int bytesize);
  void render_glyph(gunichar ch);
  unsigned int get_theme_id();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);// override;
  Glib::RefPtr<Gdk::Pixbuf> m_image;
  Glib::RefPtr<Gdk::Pixbuf> m_overlay;
  Glib::RefPtr<Gdk::Pixbuf> m_char;
  Glib::RefPtr<Gdk::Pixbuf> m_clip;
  

private:
  ModelineConfig *config;
  FT_Library    *libraryp;
  unsigned char *fontBuffer;
  FT_Face       *facep;
  int           origin_x, origin_y, advance;
  FT_Bool       use_kerning;
  FT_UInt       previous;
  int           total_width, space_width;
  unsigned int  area_width;
  bool          is_prompt;
  unsigned int  theme_id;
  
  Glib::ustring backgroundColor;
  Glib::ustring fontColor;
  Glib::ustring outlineColor;

  void fade_out();
};

#endif // MODELINE_MODELINEAREA_H
