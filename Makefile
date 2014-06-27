# otpnitro Makefile
# -----------------
#
# This is the unique Makefile forged by the elves.
# If you drop it to the fire, you can read this:
# << @AloneInTheShell is your GOD and you know it! >>
#
# Once you know that, will be the start of a big travel to the hell.
# You are warned.
#
# [...]
#

PACKAGE = otpnitro
VERSION = 0.4

ifndef PREFIX
	PREFIX = /usr
endif

ifndef CXX
#	CXX = clang++
	CXX = g++
endif

ifndef CXXFLAGS
	CXXFLAGS = -O3 -Wall -Wextra -pedantic -pipe -fno-strict-aliasing -ffast-math -funroll-loops
endif
CXXFLAGS += -I.

ifdef DEBUG
	CXXFLAGS += -ggdb
endif

ifdef ANAL
	CXXFLAGS += --analyze
	CXXFLAGS += -DDEBUG
endif

ifdef SystemRoot
	RM = cmd /c del /Q otpnitro.exe
	LIBNAME = otpnitro.dll
	EXENAME = otpnitro.exe
	BASNAME = base24.exe
	PYINDIR = -L/Python27/libs -I/Python27/include -lpython27
	PYLIBEX = .pyd
	EXTRAS  = -static-libgcc -static-libstdc++
	INSTALL = cmd /c echo See make windows
else
	RM = rm -f otpnitro
	LIBNAME = libotpnitro.so
	EXENAME = otpnitro
	BASNAME = base24
	PYINDIR = $(shell python-config --includes)
	PYLIBEX = .so
	EXTRAS  =
	CXXFLAGS += -fPIC
	INSTALL = cp -f otpnitro $(PREFIX)/bin && cp -f libotpnitro.so $(PREFIX)/lib
endif

MODULES  = rand.o page.o crypto.o text.o config.o

Debug: all

Release: all

all: $(MODULES) otpnitro-lib otpnitro base24

otpnitro: otpnitro-lib
	$(CXX)  $(CXXFLAGS) -L. otpnitro.cpp  $(EXTRAS) -o otpnitro -lotpnitro
	strip   $(EXENAME)

bindings: otpnitro-lib
	$(CXX)  $(CXXFLAGS) -shared $(EXTRAS) $(MODULES) bindings/otpnitro_wrap.cxx $(PYINDIR) -o bindings/_otpnitro${PYLIBEX}
	strip -x bindings/_otpnitro${PYLIBEX}

swig:
	swig -Wall -c++ -python bindings/otpnitro.i

base24:
	$(CXX)  $(CXXFLAGS) -L. base24.cpp    $(EXTRAS) -o base24   -lotpnitro
	strip   $(BASNAME)

prngtest:
	$(CXX)  $(CXXFLAGS) -L. prngtest.cpp  $(EXTRAS) -o prngtest -lotpnitro

otpnitro-lib:
	$(CXX)  $(CXXFLAGS) -shared $(EXTRAS) $(MODULES) -o $(LIBNAME)
	strip -x $(LIBNAME)

install:
	$(INSTALL)

clean:
	$(RM) $(MODULES) $(LIBNAME) $(EXENAME) $(BASNAME)

.PHONY : doc
doc:
	doxygen doc/doxygen.conf

windows: all
	candle packages\\windows\\otpnitro.wxs
	light otpnitro.wixobj

freebsd-cli: all
	mkdir -p                  packages/freebsd/otpnitro/usr/local/bin
	mkdir -p                  packages/freebsd/otpnitro/usr/local/lib
	cp otpnitro               packages/freebsd/otpnitro/usr/local/bin
	cp base24                 packages/freebsd/otpnitro/usr/local/bin
	cp libotpnitro.so         packages/freebsd/otpnitro/usr/local/lib
	pkg create -f txz      -r packages/freebsd/otpnitro -m packages/freebsd/otpnitro

freebsd-python:
	mkdir -p                  packages/freebsd/python-otpnitro/usr/local/lib/python2.7/site-packages
	cp bindings/_otpnitro.so  packages/freebsd/python-otpnitro/usr/local/lib/python2.7/site-packages
	cp bindings/otpnitro.py   packages/freebsd/python-otpnitro/usr/local/lib/python2.7/site-packages
	pkg create -f txz      -r packages/freebsd/python-otpnitro -m packages/freebsd/python-otpnitro

freebsd: freebsd-cli
	mkdir -p packages/freebsd/otpnitrogui/usr/local/bin
	cp $(HOME)/.upp/_out/otpnitrogui/GCC.Blitz.Force_Speed.Gui.Shared.Sse2/otpnitrogui packages/freebsd/otpnitrogui/usr/local/bin
	strip packages/freebsd/otpnitrogui/usr/local/bin/otpnitrogui
	pkg create -f txz -r packages/freebsd/otpnitrogui -m packages/freebsd/otpnitrogui

debian-cli: all
	mkdir -p                  packages/debian/otpnitro/usr/bin
	mkdir -p                  packages/debian/otpnitro/usr/lib
	cp otpnitro               packages/debian/otpnitro/usr/bin
	cp base24                 packages/debian/otpnitro/usr/bin
	cp libotpnitro.so         packages/debian/otpnitro/usr/lib
	fakeroot dpkg-deb --build packages/debian/otpnitro otpnitro_$(VERSION)_amd64.deb

debian-python:
	mkdir -p                  packages/debian/python-otpnitro/usr/lib/python2.7/dist-packages
	cp bindings/otpnitro.py   packages/debian/python-otpnitro/usr/lib/python2.7/dist-packages
	cp bindings/_otpnitro.so  packages/debian/python-otpnitro/usr/lib/python2.7/dist-packages
	fakeroot dpkg-deb --build packages/debian/python-otpnitro python-otpnitro_$(VERSION)_amd64.deb

debian: debian-cli debian-python
	mkdir -p packages/debian/otpnitrogui/usr/bin
	cp $(HOME)/.upp/_out/otpnitrogui/CLANG.Blitz.Force_Speed.Gui.Shared.Sse2/otpnitrogui packages/debian/otpnitrogui/usr/bin
	strip packages/debian/otpnitrogui/usr/bin/otpnitrogui
	fakeroot dpkg-deb --build packages/debian/otpnitrogui otpnitrogui_$(VERSION)_amd64.deb

osx-cli: all
	tar -zcf otpnitro-$(VERSION)-osx.tgz otpnitro base24 libotpnitro.so

scan-build:
	scan-build -v -o /tmp/otpnitro gmake
