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

OBJECTS	:= chooserconfig.o chooserwin.o chooserarea.o midiclient.o signalclient.o

all: test midi_chooser

midi_chooser: $(OBJECTS) chooser.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) chooser.o -o midi_chooser $(LIBS)

chooser.o: chooser.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c chooser.cc -o chooser.o

test: $(OBJECTS) test.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) test.o -o test $(LIBS)

test.o: $(OBJECTS) test.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c test.cc -o test.o



chooserwin.o: chooserwin.cc chooserwin.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c chooserwin.cc -o chooserwin.o

chooserarea.o: chooserarea.cc chooserarea.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c chooserarea.cc -o chooserarea.o

chooserconfig.o: chooserconfig.cc chooserconfig.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c chooserconfig.cc -o chooserconfig.o

midiclient.o: midiclient.cc midiclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c midiclient.cc -o midiclient.o

signalclient.o: signalclient.cc signalclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c signalclient.cc -o signalclient.o

clean:
	rm *.o test midi_chooser
