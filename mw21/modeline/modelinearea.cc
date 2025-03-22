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

#include "modelinearea.h"
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>
#include <fstream>
#include <algorithm>


ModelineArea::ModelineArea(FT_Library *p_lib, FT_Face *p_face, unsigned int p_width)
{
  this->libraryp = p_lib;
  this->facep = p_face;
  this->area_width = p_width;
}

ModelineArea::~ModelineArea()
{
}

//color theme is set in set_color_theme()
void ModelineArea::render_string(Glib::ustring& string, bool p_fade_out, bool p_sep)
{
  try
  {
//     std::cout << "area_width: " << area_width << " height: " << config->getModelineAreaHeight() << std::endl;
    m_image = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, area_width, p_sep ? 0 : config->getModelineAreaHeight() );
    if(!p_sep)
    {
      m_image->fill(get_int_color(backgroundColor));
      m_overlay = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, area_width * 3 , config->getModelineAreaHeight());
      m_overlay->fill(get_int_color(backgroundColor));

      for ( unsigned int i = 0; i < string.length(); i++ )
      {
        render_glyph(string.at(i));
      }
      origin_x += space_width;
      m_clip = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, std::min(origin_x, (int)(area_width * 3))  , config->getModelineAreaHeight());
      paste_pixbuf(m_clip, m_overlay, 0, 0);
      if(origin_x <= (int)(area_width))
      {
        //paste_pixbuf(m_clip, ((int)(area_width) - origin_x) / 2, 0); // CENTER
        paste_pixbuf(m_clip, 0, 0); // ALIGN TO LEFT
      }
      else
      {
        paste_pixbuf(m_clip->scale_simple(area_width, config->getModelineAreaHeight(), Gdk::INTERP_BILINEAR), 0, 0);
      }
      if(p_fade_out)
      {
        fade_out();
      }
    }
    else
    {
      m_image->fill(0x00000000);
    }
  }
  catch(...)
  {
    std::cerr << "Some exception in DisplayArea::render_string(Glib::ustring &str)" << std::endl;
  }
  if (m_image)
    set_size_request(m_image->get_width(), m_image->get_height());
  queue_draw();
}

void ModelineArea::set_config(ModelineConfig *pconfig)
{
  config = pconfig;
}

unsigned int ModelineArea::get_theme_id()
{
  return theme_id;
}

void ModelineArea::set_color_theme(int p_idx)
{
  theme_id = p_idx;
  switch(p_idx)
  {
    case(THEME_BANK_1):
      backgroundColor = config->getBackgroundColor(0);
      fontColor = config->getLyricsColor(0);
      outlineColor = config->getLyricsOutlineColor(0);
      break;
    case(THEME_BANK_2):
      backgroundColor = config->getBackgroundColor(1);
      fontColor = config->getLyricsColor(1);
      outlineColor = config->getLyricsOutlineColor(1);
      break;
    case(THEME_BANK_3):
      backgroundColor = config->getBackgroundColor(2);
      fontColor = config->getLyricsColor(2);
      outlineColor = config->getLyricsOutlineColor(2);
      break;

    case(THEME_NEUTRAL_1):
      backgroundColor = config->getModelineBackgroundColor_neutral1();
      fontColor = config->getModelineFontColor_neutral1();
      outlineColor = config->getModelineOutlineColor_neutral1();
      break;
    case(THEME_NEUTRAL_2):
      backgroundColor = config->getModelineBackgroundColor_neutral2();
      fontColor = config->getModelineFontColor_neutral2();
      outlineColor = config->getModelineOutlineColor_neutral2();
      break;

    case(THEME_BLINK_1):
      backgroundColor = config->getModelineBackgroundColor_blink1();
      fontColor = config->getModelineFontColor_blink1();
      outlineColor = config->getModelineOutlineColor_blink1();
      break;
    case(THEME_BLINK_2):
      backgroundColor = config->getModelineBackgroundColor_blink2();
      fontColor = config->getModelineFontColor_blink2();
      outlineColor = config->getModelineOutlineColor_blink2();
      break;

    case(THEME_OK):
      backgroundColor = config->getModelineBackgroundColor_ok();
      fontColor = config->getModelineFontColor_ok();
      outlineColor = config->getModelineOutlineColor_ok();
      break;
    case(THEME_SEARCH):
      backgroundColor = config->getModelineBackgroundColor_search();
      fontColor = config->getModelineFontColor_search();
      outlineColor = config->getModelineOutlineColor_search();
      break;
    case(THEME_FOUND):
      backgroundColor = config->getModelineBackgroundColor_found();
      fontColor = config->getModelineFontColor_found();
      outlineColor = config->getModelineOutlineColor_found();
      break;

    default:
      backgroundColor = config->getBackgroundColor(0);
      fontColor = config->getLyricsColor(0);
      outlineColor = config->getLyricsOutlineColor(0);
      break;
  }
}

bool ModelineArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
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

void ModelineArea::initialize(unsigned int p_theme_idx)
{
  origin_x = (int)( (((float)config->getModelineAreaHeight()) * 0.17f) );
  origin_y = (int)( (((float)config->getModelineAreaHeight()) * 0.7f) );
  space_width = (int)( (((float)config->getModelineAreaHeight()) * 0.2f) );
  advance = 0;
  previous = 0;
  set_color_theme(p_theme_idx);
}




void ModelineArea::paste_pixbuf(Glib::RefPtr<Gdk::Pixbuf> where, Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
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
void ModelineArea::paste_pixbuf(Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
{
  paste_pixbuf(m_image, what, x, y);
}

void ModelineArea::paste_blend_pixbuf(Glib::RefPtr<Gdk::Pixbuf> where, Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
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

void ModelineArea::paste_blend_pixbuf(Glib::RefPtr<Gdk::Pixbuf> what, const unsigned int x, const unsigned int y)
{
  paste_blend_pixbuf(m_image, what, x, y);
}

void ModelineArea::set_pixel(Glib::RefPtr<Gdk::Pixbuf> where, Pixel32 *pixel, int x, int y)
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
void ModelineArea::set_pixel(Pixel32 *pixel, int x, int y)
{
  set_pixel(m_image, pixel, x, y);
}


void ModelineArea::set_pixel_opacity(Glib::RefPtr<Gdk::Pixbuf> where, unsigned char p_opacity, int x, int y)
{
  if(!where) return;
  int dst_width = where->get_width();
  int dst_height = where->get_height();
  int dst_rowstride = where->get_rowstride();

  if (x > dst_width) return;
  if (y > dst_height) return;
  guint8 *dst_data = where->get_pixels();

  //std::cout << "Setting pixel at (" << (int)x << ", " << (int)y << ") to RGBA(" << (int)pixel->r << ", " << (int)pixel->g << ", " << (int)pixel->b << ", " << (int)pixel->a << ")" << std::endl;
  *(dst_data + (y * dst_rowstride) + (x * 4 * sizeof(guint8)) + 3 * sizeof(guint8)) = p_opacity;
}




void ModelineArea::fade_out()
{
  if(!m_image) return;
  int width = m_image->get_width();
  int height = m_image->get_height();

  int over_width = (int)( (((float)config->getModelineAreaHeight()) * 0.17f) ) / 2;

  Glib::RefPtr<Gdk::Pixbuf> t_over = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, true, 8, over_width , height );
  t_over->fill(get_int_color(backgroundColor));

//   for (int i = 0; i < over_width / 2 ; i++)
//   {
//     for ( int j = 0; j < height; j++)
//     {
//       set_pixel_opacity(t_over, (unsigned char)( ((double) i ) /  ((double) over_width / 2 )   )*255, i, j      );
//     }
//   }

  paste_blend_pixbuf(t_over, width - over_width, 0);
}



void ModelineArea::render_glyph(gunichar ch)
{
  FT_Face face = *facep;
  FT_Library library = *libraryp;
  FT_UInt gindex = FT_Get_Char_Index(face, (wchar_t)ch);

//   std::cout << std::endl << " backgroundColor is " << backgroundColor << std::endl;

  if(' ' == ch)
  {
    origin_x += space_width;
    previous = gindex;
	  return;
  }
  //std::cout << "gindex  = " << gindex << std::endl;
  if (FT_Load_Glyph(face, gindex, FT_LOAD_NO_BITMAP) == 0)
  {
      // Need an outline for this to work.
      if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
      {
        // Render the basic glyph to a span list.
        //std::cout << "RENDERING FRONT SPANS" << std::endl;
        Spans spans;
        //std::cout << "Before render front, spans size is : " << spans.size() << std::endl;
        RenderSpans(library, &face->glyph->outline, &spans);
        //std::cout << "After render front, spans size is : " << spans.size() << std::endl;
        // Next we need the spans for the outline.
        Spans outlineSpans;

        // Set up a stroker.
        FT_Stroker stroker;
        FT_Stroker_New(library, &stroker);
        FT_Stroker_Set(stroker,
                       (int)(config->getOutlineWidth() * 64),
                       FT_STROKER_LINECAP_ROUND,
                       FT_STROKER_LINEJOIN_ROUND,
                       0);

        FT_Glyph glyph;
        if (FT_Get_Glyph(face->glyph, &glyph) == 0)
        {
          FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
          // Again, this needs to be an outline to work.
          if (glyph->format == FT_GLYPH_FORMAT_OUTLINE)
          {
            //std::cout << "RENDERING OUTLINE SPANS" << std::endl;
            // Render the outline spans to the span list
            FT_Outline *o =
              &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;
            RenderSpans(library, o, &outlineSpans);
          }

          // Clean up afterwards.
          FT_Stroker_Done(stroker);
          FT_Done_Glyph(glyph);

          // Now we need to put it all together.
          if (!spans.empty())
          {
            // Figure out what the bounding rect is for both the span lists.
            Rect rect(spans.front().x,
                      spans.front().y,
                      spans.front().x,
                      spans.front().y);
            for (Spans::iterator s = spans.begin();
                 s != spans.end(); ++s)
            {
              rect.Include(Vec2(s->x, s->y));
              rect.Include(Vec2(s->x + s->width - 1, s->y));
            }
            for (Spans::iterator s = outlineSpans.begin();
                 s != outlineSpans.end(); ++s)
            {
              rect.Include(Vec2(s->x, s->y));
              rect.Include(Vec2(s->x + s->width - 1, s->y));
            }

            int bearingX = (int) ( face->glyph->metrics.horiBearingX >> 6 );
            int bearingY = (int) ( face->glyph->metrics.horiBearingY >> 6 );
            advance =  (int) ( face->glyph->advance.x >> 6 );


            int imgWidth = rect.Width(),
                imgHeight = rect.Height(),
                imgSize = imgWidth * imgHeight;

            //std::cout << "dimensions of out rect is " << imgWidth << " x " << imgHeight << std::endl;

            // Allocate data for our image and clear it out to transparent.
            Pixel32 *pxl = new Pixel32[imgSize];
            memset(pxl, 0, sizeof(Pixel32) * imgSize);

            uint8 text_r, text_g, text_b;
            uint8 out_r, out_g, out_b;

            text_r = get_red_value(fontColor);
            text_g = get_green_value(fontColor);
            text_b = get_blue_value(fontColor);

            out_r = get_red_value(outlineColor);
            out_g = get_green_value(outlineColor);
            out_b = get_blue_value(outlineColor);

            // Loop over the outline spans and just draw them into the
            // image.
            for (Spans::iterator s = outlineSpans.begin();
                 s != outlineSpans.end(); ++s)
            {
              for (int w = 0; w < s->width; ++w)
              {
                //std::cout << (int)get_red_value(config->getLyricsOutlineColor()) << std::endl;
                Pixel32 l_pixel = Pixel32(out_r, out_g, out_b, s->coverage);
                //l_pixel.print_this();

                pxl[(int)((imgHeight - 1 - (s->y - rect.ymin)) * imgWidth
                          + s->x - rect.xmin + w)] = l_pixel;
              }
            }

            // Then loop over the regular glyph spans and blend them into
            // the image.
            for (Spans::iterator s = spans.begin();
                 s != spans.end(); ++s)
            {
              for (int w = 0; w < s->width; ++w)
              {
                Pixel32 &dst =
                  pxl[(int)((imgHeight - 1 - (s->y - rect.ymin)) * imgWidth
                      + s->x - rect.xmin + w)];
                Pixel32 src =
                  Pixel32(text_r, text_g, text_b, s->coverage);

                dst.r = (int)(dst.r + ((src.r - dst.r) * src.a) / 255.0f);
                dst.g = (int)(dst.g + ((src.g - dst.g) * src.a) / 255.0f);
                dst.b = (int)(dst.b + ((src.b - dst.b) * src.a) / 255.0f);
                dst.a = MIN(255, dst.a + src.a);
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
			      //std::cout << "origin_x " << origin_x << " bearing_x " << bearingX << " bearing_y " << bearingY << " advance " << advance << std::endl;
            paste_blend_pixbuf(m_overlay, m_char, (int)(origin_x + bearingX), (int)(origin_y - bearingY));
			      /*if ( use_kerning && previous && gindex )
            {
              std::cout << "Computing kerning. gindex " << gindex << " previous " << previous << std::endl;
              FT_Vector  delta;
              FT_Get_Kerning( face, previous, gindex,
              FT_KERNING_DEFAULT, &delta );
              std::cout << "delta.x = " << (delta.x >> 6) << std::endl;
              origin_x += delta.x << 6;
            }*/
            origin_x += advance;
            //previous = gindex;
          }
        }
      }

  }

}
