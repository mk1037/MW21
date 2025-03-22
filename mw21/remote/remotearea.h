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

#ifndef REMOTEAREA_H
#define REMOTEAREA_H

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>

#define AREA_WIDTH 150
#define AREA_HEIGHT 50

class RemoteArea : public Gtk::DrawingArea
{
public:
  void render();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);// override;
  Glib::RefPtr<Gdk::Pixbuf> m_image;
};

#endif // REMOTEAREA_H
