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

OBJECTS	:= proxyconfig.o g_proxywin.o midiclient.o signalclient.o proxyarea.o

all: PR3000 MAIN_PR

PR3000: $(OBJECTS) PR3000.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) PR3000.o -o PR3000 $(LIBS)

PR3000.o: $(OBJECTS) PR3000.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c PR3000.cc -o PR3000.o

MAIN_PR: $(OBJECTS) MAIN_PR.o
	$(CXX) $(CXXFLAGS) $(OBJECTS) MAIN_PR.o -o MAIN_PR $(LIBS)

MAIN_PR.o: $(OBJECTS) MAIN_PR.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c MAIN_PR.cc -o MAIN_PR.o


g_proxywin.o: g_proxywin.cc g_proxywin.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c g_proxywin.cc -o g_proxywin.o

proxyarea.o: proxyarea.cc proxyarea.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c proxyarea.cc -o proxyarea.o

proxyconfig.o: proxyconfig.cc proxyconfig.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c proxyconfig.cc -o proxyconfig.o

midiclient.o: midiclient.cc midiclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c midiclient.cc -o midiclient.o

signalclient.o: signalclient.cc signalclient.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c signalclient.cc -o signalclient.o

clean:
	rm *.o PR3000 MAIN_PR
