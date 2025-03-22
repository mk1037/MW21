# Copyright (C) 2017-2025 Marek Momot
#
# This file is part of MW21.
#
# MW21 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# MW21 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MW21.  If not, see <http://www.gnu.org/licenses/>.

CXX=g++
CXXFLAGS=-Wno-deprecated-declarations -std=c++11
INCLUDES=`pkg-config --cflags gtkmm-3.0 freetype2`
LIBS=`pkg-config --libs gtkmm-3.0 freetype2` -lpthread -lasound

OBJECTS	:= displayconfig.o displaywin.o displayarea.o framecontent.o graphics.o textqueue.o midiclient.o

all: test midi_display

midi_display: $(OBJECTS) display.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) display.o -o midi_display $(LIBS)

display.o: display.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c display.cc -o display.o

test: $(OBJECTS) test.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) test.o -o test $(LIBS)

test.o: $(OBJECTS) test.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c test.cc -o test.o


displaywin.o: displaywin.cc displaywin.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c displaywin.cc -o displaywin.o

displayarea.o: displayarea.cc displayarea.h graphics.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c displayarea.cc -o displayarea.o

graphics.o: graphics.cc graphics.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c graphics.cc -o graphics.o

displayconfig.o: displayconfig.cc displayconfig.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c displayconfig.cc -o displayconfig.o

framecontent.o: framecontent.cc framecontent.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c framecontent.cc -o framecontent.o

textqueue.o: textqueue.cc textqueue.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c textqueue.cc -o textqueue.o

midiclient.o: midiclient.cc midiclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c midiclient.cc -o midiclient.o

clean:
	rm *.o test midi_display

