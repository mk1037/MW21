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

OBJECTS	:= modelineconfig.o filesqueue.o modelinewin.o midiclient.o modelinearea.o graphics.o timeoutclient.o signalclient.o modelineaction.o

all: test midi_modeline

midi_modeline: $(OBJECTS) modeline.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) modeline.o -o midi_modeline $(LIBS)

modeline.o: modeline.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c modeline.cc -o modeline.o

test: $(OBJECTS) test.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) test.o -o test $(LIBS)

test.o: $(OBJECTS) test.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c test.cc -o test.o


modelinewin.o: modelinewin.cc modelinewin.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c modelinewin.cc -o modelinewin.o

modelinearea.o: modelinearea.cc modelinearea.h graphics.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c modelinearea.cc -o modelinearea.o

graphics.o: graphics.cc graphics.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c graphics.cc -o graphics.o

modelineconfig.o: modelineconfig.cc modelineconfig.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c modelineconfig.cc -o modelineconfig.o

modelineaction.o: modelineaction.cc modelineaction.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c modelineaction.cc -o modelineaction.o

signalclient.o: signalclient.cc signalclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c signalclient.cc -o signalclient.o

filesqueue.o: filesqueue.cc filesqueue.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c filesqueue.cc -o filesqueue.o

midiclient.o: midiclient.cc midiclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c midiclient.cc -o midiclient.o

timeoutclient.o: timeoutclient.cc timeoutclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c timeoutclient.cc -o timeoutclient.o

clean:
	rm *.o test midi_modeline

