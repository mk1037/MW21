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

OBJECTS	:= remoteconfig.o remotewin.o remotearea.o midiclient.o signalclient.o

all: test midi_remote

midi_remote: $(OBJECTS) remote.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) remote.o -o midi_remote $(LIBS)

remote.o: remote.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c remote.cc -o remote.o

test: $(OBJECTS) test.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) test.o -o test $(LIBS)

test.o: $(OBJECTS) test.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c test.cc -o test.o



remotewin.o: remotewin.cc remotewin.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c remotewin.cc -o remotewin.o

remotearea.o: remotearea.cc remotearea.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c remotearea.cc -o remotearea.o

remoteconfig.o: remoteconfig.cc remoteconfig.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c remoteconfig.cc -o remoteconfig.o

midiclient.o: midiclient.cc midiclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c midiclient.cc -o midiclient.o

signalclient.o: signalclient.cc signalclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c signalclient.cc -o signalclient.o

clean:
	rm *.o test midi_remote
