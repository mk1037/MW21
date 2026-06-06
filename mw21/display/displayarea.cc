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

#include "displayarea.h"
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>
#include <fstream>
#include <algorithm>
//#include <ft2build.h>


DisplayArea::DisplayArea(FT_Library *p_lib, FT_Face *p_face, unsigned int p_theme)
{
  this->libraryp = p_lib;
  this->facep = p_face;
  this->theme_nr = p_theme;
}

DisplayArea::~DisplayArea()
{
}

void DisplayArea::initialize()
{
  origin_x = (int)( (((float)config->getAreaHeight()) * 0.17f) );
  origin_y = (int)( (((float)config->getAreaHeight()) * 0.7f) );
  space_width = (int)( (((float)config->getAreaHeight()) * 0.2f) );
  advance = 0;
  previous = 0;
}

void DisplayArea::set_config(DisplayConfig *pconfig)
{
  config = pconfig;
}

void DisplayArea::set_color_theme(int p_idx)
{
  this->theme_nr = p_idx;
}

void DisplayArea::render_string(Glib::ustring &left, Glib::ustring &right, int p_state, bool p_is_hint)
{
  total_width = (int)( (((float)config->getAreaHeight()) * 0.17f) );
  is_hint = p_is_hint;
  int backgroundColor;
  int backgroundColorR, backgroundColorG, backgroundColorB;
  int leftFontColorR, leftFontColorG, leftFontColorB;
  int leftFontOutlineColorR, leftFontOutlineColorG, leftFontOutlineColorB;
  int rightFontColorR, rightFontColorG, rightFontColorB;
  int rightFontOutlineColorR, rightFontOutlineColorG, rightFontOutlineColorB;


  //std::cout << "alt_colours is: " << alt_colours << std::endl;
  if(!is_hint)
    switch(p_state)
    {
      case INACTIVE:
        backgroundColor = get_int_color(config->getBackgroundColor(theme_nr));

        backgroundColorR = get_red_value(config->getBackgroundColor(theme_nr));
        backgroundColorG = get_green_value(config->getBackgroundColor(theme_nr));
        backgroundColorB = get_blue_value(config->getBackgroundColor(theme_nr));

        leftFontColorR = get_red_value(config->getInactiveLyricsColor(theme_nr));
        leftFontColorG = get_green_value(config->getInactiveLyricsColor(theme_nr));
        leftFontColorB = get_blue_value(config->getInactiveLyricsColor(theme_nr));

        leftFontOutlineColorR = get_red_value(config->getInactiveLyricsOutlineColor(theme_nr));
        leftFontOutlineColorG = get_green_value(config->getInactiveLyricsOutlineColor(theme_nr));
        leftFontOutlineColorB = get_blue_value(config->getInactiveLyricsOutlineColor(theme_nr));

        rightFontColorR = get_red_value(config->getInactiveLyricsColor(theme_nr));
        rightFontColorG = get_green_value(config->getInactiveLyricsColor(theme_nr));
        rightFontColorB = get_blue_value(config->getInactiveLyricsColor(theme_nr));

        rightFontOutlineColorR = get_red_value(config->getInactiveLyricsOutlineColor(theme_nr));
        rightFontOutlineColorG = get_green_value(config->getInactiveLyricsOutlineColor(theme_nr));
        rightFontOutlineColorB = get_blue_value(config->getInactiveLyricsOutlineColor(theme_nr));

        break;

      case ACTIVE:
        backgroundColor = get_int_color(config->getSungBackgroundColor(theme_nr));

        backgroundColorR = get_red_value(config->getSungBackgroundColor(theme_nr));
        backgroundColorG = get_green_value(config->getSungBackgroundColor(theme_nr));
        backgroundColorB = get_blue_value(config->getSungBackgroundColor(theme_nr));

        leftFontColorR = get_red_value(config->getSungLyricsColor(theme_nr));
        leftFontColorG = get_green_value(config->getSungLyricsColor(theme_nr));
        leftFontColorB = get_blue_value(config->getSungLyricsColor(theme_nr));

        leftFontOutlineColorR = get_red_value(config->getSungLyricsOutlineColor(theme_nr));
        leftFontOutlineColorG = get_green_value(config->getSungLyricsOutlineColor(theme_nr));
        leftFontOutlineColorB = get_blue_value(config->getSungLyricsOutlineColor(theme_nr));

        rightFontColorR = get_red_value(config->getLyricsColor(theme_nr));
        rightFontColorG = get_green_value(config->getLyricsColor(theme_nr));
        rightFontColorB = get_blue_value(config->getLyricsColor(theme_nr));

        rightFontOutlineColorR = get_red_value(config->getLyricsOutlineColor(theme_nr));
        rightFontOutlineColorG = get_green_value(config->getLyricsOutlineColor(theme_nr));
        rightFontOutlineColorB = get_blue_value(config->getLyricsOutlineColor(theme_nr));

        break;

      case VISITED:
        backgroundColor = get_int_color(config->getVisitedBackgroundColor(theme_nr));

        backgroundColorR = get_red_value(config->getVisitedBackgroundColor(theme_nr));
        backgroundColorG = get_green_value(config->getVisitedBackgroundColor(theme_nr));
        backgroundColorB = get_blue_value(config->getVisitedBackgroundColor(theme_nr));

        leftFontColorR = get_red_value(config->getVisitedLyricsColor(theme_nr));
        leftFontColorG = get_green_value(config->getVisitedLyricsColor(theme_nr));
        leftFontColorB = get_blue_value(config->getVisitedLyricsColor(theme_nr));

        leftFontOutlineColorR = get_red_value(config->getVisitedLyricsOutlineColor(theme_nr));
        leftFontOutlineColorG = get_green_value(config->getVisitedLyricsOutlineColor(theme_nr));
        leftFontOutlineColorB = get_blue_value(config->getVisitedLyricsOutlineColor(theme_nr));

        rightFontColorR = get_red_value(config->getVisitedLyricsColor(theme_nr));
        rightFontColorG = get_green_value(config->getVisitedLyricsColor(theme_nr));
        rightFontColorB = get_blue_value(config->getVisitedLyricsColor(theme_nr));

        rightFontOutlineColorR = get_red_value(config->getVisitedLyricsOutlineColor(theme_nr));
        rightFontOutlineColorG = get_green_value(config->getVisitedLyricsOutlineColor(theme_nr));
        rightFontOutlineColorB = get_blue_value(config->getVisitedLyricsOutlineColor(theme_nr));

        break;

      default:
        break;
    }
  else
    switch(p_state)
    {
      case INACTIVE:
        backgroundColor = get_int_color(config->getHintsBackgroundColor(theme_nr));

        backgroundColorR = get_red_value(config->getHintsBackgroundColor(theme_nr));
        backgroundColorG = get_green_value(config->getHintsBackgroundColor(theme_nr));
        backgroundColorB = get_blue_value(config->getHintsBackgroundColor(theme_nr));

        leftFontColorR = get_red_value(config->getInactiveHintsColor(theme_nr));
        leftFontColorG = get_green_value(config->getInactiveHintsColor(theme_nr));
        leftFontColorB = get_blue_value(config->getInactiveHintsColor(theme_nr));

        leftFontOutlineColorR = get_red_value(config->getInactiveHintsOutlineColor(theme_nr));
        leftFontOutlineColorG = get_green_value(config->getInactiveHintsOutlineColor(theme_nr));
        leftFontOutlineColorB = get_blue_value(config->getInactiveHintsOutlineColor(theme_nr));

        rightFontColorR = get_red_value(config->getInactiveHintsColor(theme_nr));
        rightFontColorG = get_green_value(config->getInactiveHintsColor(theme_nr));
        rightFontColorB = get_blue_value(config->getInactiveHintsColor(theme_nr));

        rightFontOutlineColorR = get_red_value(config->getInactiveHintsOutlineColor(theme_nr));
        rightFontOutlineColorG = get_green_value(config->getInactiveHintsOutlineColor(theme_nr));
        rightFontOutlineColorB = get_blue_value(config->getInactiveHintsOutlineColor(theme_nr));

        break;

      case ACTIVE:
        backgroundColor = get_int_color(config->getActiveHintsBackgroundColor(theme_nr));

        backgroundColorR = get_red_value(config->getActiveHintsBackgroundColor(theme_nr));
        backgroundColorG = get_green_value(config->getActiveHintsBackgroundColor(theme_nr));
        backgroundColorB = get_blue_value(config->getActiveHintsBackgroundColor(theme_nr));

        leftFontColorR = get_red_value(config->getActiveHintsColor(theme_nr));
        leftFontColorG = get_green_value(config->getActiveHintsColor(theme_nr));
        leftFontColorB = get_blue_value(config->getActiveHintsColor(theme_nr));

        leftFontOutlineColorR = get_red_value(config->getActiveHintsOutlineColor(theme_nr));
        leftFontOutlineColorG = get_green_value(config->getActiveHintsOutlineColor(theme_nr));
        leftFontOutlineColorB = get_blue_value(config->getActiveHintsOutlineColor(theme_nr));

        rightFontColorR = get_red_value(config->getHintsColor(theme_nr));
        rightFontColorG = get_green_value(config->getHintsColor(theme_nr));
        rightFontColorB = get_blue_value(config->getHintsColor(theme_nr));

        rightFontOutlineColorR = get_red_value(config->getHintsOutlineColor(theme_nr));
        rightFontOutlineColorG = get_green_value(config->getHintsOutlineColor(theme_nr));
        rightFontOutlineColorB = get_blue_value(config->getHintsOutlineColor(theme_nr));

        break;

      case VISITED:
        backgroundColor = get_int_color(config->getVisitedHintsBackgroundColor(theme_nr));

        backgroundColorR = get_red_value(config->getVisitedHintsBackgroundColor(theme_nr));
        backgroundColorG = get_green_value(config->getVisitedHintsBackgroundColor(theme_nr));
        backgroundColorB = get_blue_value(config->getVisitedHintsBackgroundColor(theme_nr));

        leftFontColorR = get_red_value(config->getVisitedHintsColor(theme_nr));
        leftFontColorG = get_green_value(config->getVisitedHintsColor(theme_nr));
        leftFontColorB = get_blue_value(config->getVisitedHintsColor(theme_nr));

        leftFontOutlineColorR = get_red_value(config->getVisitedHintsOutlineColor(theme_nr));
        leftFontOutlineColorG = get_green_value(config->getVisitedHintsOutlineColor(theme_nr));
        leftFontOutlineColorB = get_blue_value(config->getVisitedHintsOutlineColor(theme_nr));

        rightFontColorR = get_red_value(config->getVisitedHintsColor(theme_nr));
        rightFontColorG = get_green_value(config->getVisitedHintsColor(theme_nr));
        rightFontColorB = get_blue_value(config->getVisitedHintsColor(theme_nr));

        rightFontOutlineColorR = get_red_value(config->getVisitedHintsOutlineColor(theme_nr));
        rightFontOutlineColorG = get_green_value(config->getVisitedHintsOutlineColor(theme_nr));
        rightFontOutlineColorB = get_blue_value(config->getVisitedHintsOutlineColor(theme_nr));

        break;

      default:

        break;
    }

  try
  {
    m_image = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, config->getAreaWidth(), config->getAreaHeight());
    m_image->fill(backgroundColor);

//    m_overlay = Gdk::Pixbuf::create_from_file("./image/fractal_image.png");
    //m_overlay = Gdk::Pixbuf::create_from_file("./image/kwadr_grad.png");
    m_overlay = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, config->getAreaWidth() * 3 , config->getAreaHeight());
    m_overlay->fill(backgroundColor);

  
//    m_overlay->fill(0x00af0000);
    //paste_blend_pixbuf(m_overlay, 0, 100);
    //paste_blend_pixbuf(m_overlay, 100, 0);
    //paste_blend_pixbuf(m_overlay, 200, 100);
    //paste_blend_pixbuf(m_overlay, 300, 0);
	  //std::cout << (wchar_t)left.at(0) << std::endl;
    //set_pixel(m_image, new Pixel32(255, 0, 0, 255), 50, 20);
    //Print(4 * config->getAreaWidth() * config->getAreaHeight() );
	  for ( unsigned int i = 0; i < left.length(); i++ )
	  {
      render_glyph(left.at(i), leftFontColorR, leftFontColorG, leftFontColorB, leftFontOutlineColorR, leftFontOutlineColorG, leftFontOutlineColorB);
  	}
  	for ( unsigned int i = 0; i < right.length(); i++ )
  	{
      render_glyph(right.at(i), rightFontColorR, rightFontColorG, rightFontColorB, rightFontOutlineColorR, rightFontOutlineColorG, rightFontOutlineColorB);
	  }
    origin_x += space_width;
    m_clip = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, std::min(origin_x, (int)(config->getAreaWidth() * 3))  , config->getAreaHeight());
    paste_pixbuf(m_clip, m_overlay, 0, 0);
    if(origin_x <= (int)(config->getAreaWidth()))
    {
      paste_pixbuf(m_clip, ((int)(config->getAreaWidth()) - origin_x) / 2, 0);
    }
    else
    {
      paste_pixbuf(m_clip->scale_simple(config->getAreaWidth(), config->getAreaHeight(), Gdk::INTERP_BILINEAR), 0, 0);
    }
  }
  catch(...)
  {
    std::cerr << "Some exception in DisplayArea::render_string(Glib::ustring &str)" << std::endl;
  }
  if (m_image)
    set_size_request(m_image->get_width()/2, m_image->get_height()/2);
  queue_draw();
}

bool DisplayArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  if (!m_image)
    return false;

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // Draw the image in the middle of the drawing area, or (if the image is
  // larger than the drawing area) draw the middle part of the image.
  Gdk::Cairo::set_source_pixbuf(cr, m_image,
    (width - m_image->get_width())/2, (height - m_image->get_height())/2);
  cr->paint();

  return true;
}

void DisplayArea::paste_pixbuf(Glib::RefPtr<Gdk::Pixbuf> where, Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
{
  if(!where) return;
  int dst_width = where->get_width();
  int dst_height = where->get_height();
  int dst_rowstride = where->get_rowstride();

  int src_width = what->get_width();
  int src_height = what->get_height();
  int src_rowstride = what->get_rowstride();

  int inter_width;
  if ((unsigned int)dst_width <= x)
    inter_width = 0;
  else
    inter_width = std::min((unsigned int)(dst_width - x), (unsigned int)src_width);

  int inter_height;
  if ((unsigned int)dst_height <= y)
    inter_height = 0;
  else
    inter_height = std::min((unsigned int)(dst_height - y), (unsigned int)src_height);

//  printf("DST W %d  x  H %d  x  R %d\n" , dst_width, dst_height, dst_rowstride );
//  printf("SRC W %d  x  H %d  x  R %d\n" , src_width, src_height, src_rowstride );
//  printf("INTER W %d  x  H %d\n" , inter_width, inter_height );

  guint8 *src_data = what->get_pixels();
  guint8 *dst_data = where->get_pixels();

  for (int i = 0; i < inter_height; i++)
    for (int j = 0; j < inter_width; j++)
  {
	int dst_offset = ((y + i) * dst_rowstride) + ((x + j) * 4 * sizeof(guint8));
	int src_offset = (i * src_rowstride) + (j * 4 * sizeof(guint8));
	for ( int j = 0; j < 4; j++) {
      *(dst_data + dst_offset + j * sizeof(guint8)) = *(src_data + src_offset + j * sizeof(guint8));
	}
  }
}
void DisplayArea::paste_pixbuf(Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
{
  paste_pixbuf(m_image, what, x, y);
}

void DisplayArea::paste_blend_pixbuf(Glib::RefPtr<Gdk::Pixbuf> where, Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
{
  if(!where) return;
  int dst_width = where->get_width();
  int dst_height = where->get_height();
  int dst_rowstride = where->get_rowstride();

  int src_width = what->get_width();
  int src_height = what->get_height();
  int src_rowstride = what->get_rowstride();

  int inter_width;
  if ((unsigned int)dst_width <= x)
    inter_width = 0;
  else
    inter_width = std::min((unsigned int)(dst_width - x), (unsigned int)src_width);

  int inter_height;
  if ((unsigned int)dst_height <= y)
    inter_height = 0;
  else
    inter_height = std::min((unsigned int)(dst_height - y), (unsigned int)src_height);

//  printf("DST W %d  x  H %d  x  R %d\n" , dst_width, dst_height, dst_rowstride );
//  printf("SRC W %d  x  H %d  x  R %d\n" , src_width, src_height, src_rowstride );
//  printf("INTER W %d  x  H %d\n" , inter_width, inter_height );

  guint8 *src_data = what->get_pixels();
  guint8 *dst_data = where->get_pixels();

  for (int i = 0; i < inter_height; i++)
    for (int j = 0; j < inter_width; j++)
  {
	int dst_offset = ((y + i) * dst_rowstride) + ((x + j) * 4 * sizeof(guint8));
	int src_offset = (i * src_rowstride) + (j * 4 * sizeof(guint8));
    int src_r, src_g, src_b, src_a;
    int dst_r, dst_g, dst_b, dst_a;

	src_r = *(src_data + src_offset + 0 * sizeof(guint8));
	src_g = *(src_data + src_offset + 1 * sizeof(guint8));
	src_b = *(src_data + src_offset + 2 * sizeof(guint8));
	src_a = *(src_data + src_offset + 3 * sizeof(guint8));

	dst_r = *(dst_data + dst_offset + 0 * sizeof(guint8));
	dst_g = *(dst_data + dst_offset + 1 * sizeof(guint8));
	dst_b = *(dst_data + dst_offset + 2 * sizeof(guint8));
	dst_a = *(dst_data + dst_offset + 3 * sizeof(guint8));

	dst_r = (int)(dst_r + ((src_r - dst_r) * src_a) / 255.0f);
	dst_g = (int)(dst_g + ((src_g - dst_g) * src_a) / 255.0f);
	dst_b = (int)(dst_b + ((src_b - dst_b) * src_a) / 255.0f);
    dst_a = std::min(255, dst_a + src_a);


	*(dst_data + dst_offset + 0 * sizeof(guint8)) = dst_r;
	*(dst_data + dst_offset + 1 * sizeof(guint8)) = dst_g;
	*(dst_data + dst_offset + 2 * sizeof(guint8)) = dst_b;
	*(dst_data + dst_offset + 3 * sizeof(guint8)) = dst_a;
  }
}

void DisplayArea::paste_blend_pixbuf(Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
{
  paste_blend_pixbuf(m_image, what, x, y);
}

void DisplayArea::set_pixel(Glib::RefPtr<Gdk::Pixbuf> where, Pixel32 *pixel, int x, int y)
{
  if(!where) return;
  int dst_width = where->get_width();
  int dst_height = where->get_height();
  int dst_rowstride = where->get_rowstride();

  if (x > dst_width) return;
  if (y > dst_height) return;
  guint8 *dst_data = where->get_pixels();

  //std::cout << "Setting pixel at (" << (int)x << ", " << (int)y << ") to RGBA(" << (int)pixel->r << ", " << (int)pixel->g << ", " << (int)pixel->b << ", " << (int)pixel->a << ")" << std::endl;
  *(dst_data + (y * dst_rowstride) + (x * 4 * sizeof(guint8)) + 0 * sizeof(guint8)) = pixel->r;
  *(dst_data + (y * dst_rowstride) + (x * 4 * sizeof(guint8)) + 1 * sizeof(guint8)) = pixel->g;
  *(dst_data + (y * dst_rowstride) + (x * 4 * sizeof(guint8)) + 2 * sizeof(guint8)) = pixel->b;
  *(dst_data + (y * dst_rowstride) + (x * 4 * sizeof(guint8)) + 3 * sizeof(guint8)) = pixel->a;
}
void DisplayArea::set_pixel(Pixel32 *pixel, int x, int y)
{
  set_pixel(m_image, pixel, x, y);
}

void DisplayArea::Print(int bytesize)
{
  if(!m_image) return;
  printf("Rowstride for this pixmap is %d bytes\n", m_image->get_rowstride());
  guint8 *dst_data = m_image->get_pixels();
  for (int i = 0; i < bytesize; i++){
    printf("NR %d is %d\n", i, *(dst_data + i) );
  }
}

void DisplayArea::render_glyph(gunichar ch, int p_font_R, int p_font_G, int p_font_B, int p_outline_R, int p_outline_G, int p_outline_B)
{

  FT_Face face = *facep;
  FT_Library library = *libraryp;
  FT_UInt gindex = FT_Get_Char_Index(face, (wchar_t)ch);

  if(' ' == ch)
  {
    origin_x += space_width;
    previous = gindex;
    return;
  }

  if (FT_Load_Glyph(face, gindex, FT_LOAD_NO_BITMAP) == 0)
  {
    FT_Glyph glyph;
    if (FT_Get_Glyph(face->glyph, &glyph) == 0)
    {
      int bearingX = (int) ( face->glyph->metrics.horiBearingX >> 6 );
      int bearingY = (int) ( face->glyph->metrics.horiBearingY >> 6 );

      advance =  (int) ( face->glyph->advance.x >> 6 );
      int glyph_width = (int)( face->glyph->metrics.width >> 6 );
      int glyph_height = (int)( face->glyph->metrics.height >> 6 );

      int imgWidth = glyph_width;
      int imgHeight = glyph_height;
      int imgSize = imgWidth * imgHeight;

      Pixel32 *pxl = new Pixel32[imgSize];
      memset(pxl, 0, sizeof(Pixel32) * imgSize);

      uint8 text_r, text_g, text_b;
      uint8 out_r, out_g, out_b;

      text_r = p_font_R;
      text_g = p_font_G;
      text_b = p_font_B;
      out_r = p_outline_R;
      out_g = p_outline_G;
      out_b = p_outline_B;

      FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

      for (int i = 0; i < (int)face->glyph->bitmap.rows; i++)
      {
        for (int j = 0; j < (int)face->glyph->bitmap.width; j++)
        {
          unsigned char p = face->glyph->bitmap.buffer [i * face->glyph->bitmap.pitch + j];
          Pixel32 l_pixel = Pixel32(text_r, text_g, text_b, p);
          pxl[ i * imgWidth +  j] = l_pixel;
        }
      }

      m_char = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, imgWidth, imgHeight);
      for (int i = 0; i < imgHeight; i++)
      {
        for (int j = 0; j < imgWidth; j++)
        {
          set_pixel(m_char, pxl + (i * imgWidth + j), j , i);
        }
      }
      delete [] pxl;

      paste_blend_pixbuf(m_overlay, m_char, (int)(origin_x + bearingX), (int)(origin_y - bearingY));
      origin_x += advance;
    }
  }
}
