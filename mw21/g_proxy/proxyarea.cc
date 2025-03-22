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

#include "proxyarea.h"
#include <cairomm/context.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <iostream>

ProxyArea::ProxyArea(bool p_open)
{
  m_open = p_open;
}

ProxyArea::~ProxyArea()
{
}

void ProxyArea::render()
{
  try
  {
    m_image = Gdk::Pixbuf::create (Gdk::COLORSPACE_RGB, false, 8, AREA_WIDTH, AREA_HEIGHT);
    if(m_open)
      m_image->fill(0x00ff0000);
    else
      m_image->fill(0xff000000);
  }
  catch(...)
  {
    std::cerr << "Some exception in ProxyArea::render_string(Glib::ustring &str)" << std::endl;
  }
  if (m_image)
    set_size_request(m_image->get_width()/2, m_image->get_height()/2);
  queue_draw();
}

bool ProxyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
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

