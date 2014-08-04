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
VERSION = 0.5.0

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
	STRIPCM = strip
else 
ifdef COMSPEC
	RM = del otpnitro.exe
	LIBNAME = otpnitro.dll
	EXENAME = otpnitro.exe
	BASNAME = base24.exe
	PYINDIR =
	PYLIBEX =
	EXTRAS  =
	INSTALL = echo TODO: OS/2 INSTALL
	STRIPCM = ar cr otpnitro.a *.o | echo
else
	RM = rm -f otpnitro
	LIBNAME = libotpnitro.so
	EXENAME = otpnitro
	BASNAME = base24
	PYINDIR = $(shell python-config --includes) $(shell python-config --ldflags)
	PYLIBEX = .so
	EXTRAS  =
	CXXFLAGS += -fPIC
	INSTALL = cp -f otpnitro $(PREFIX)/bin && cp -f base24 $(PREFIX)/bin && cp -f libotpnitro.so $(PREFIX)/lib
	STRIPCM = strip
endif
endif

ifdef BE_HOST_CPU
	PYINDIR = $(shell python-config --includes)
endif

MODULES  = rand.o page.o crypto.o text.o config.o

.PHONY: base24 doc

Debug: all

Release: all

all: $(MODULES) otpnitro-lib otpnitro base24

otpnitro: otpnitro-lib
	$(CXX)  $(CXXFLAGS) -L. otpnitro.cpp  $(EXTRAS) -o $(EXENAME) -lotpnitro
	$(STRIPCM) $(EXENAME)

bindings: otpnitro-lib
	$(CXX)  $(CXXFLAGS) -shared $(EXTRAS) $(MODULES) bindings/otpnitro_wrap.cxx $(PYINDIR) -o bindings/_otpnitro${PYLIBEX}
	$(STRIPCM) -x bindings/_otpnitro${PYLIBEX}

swig:
	swig -Wall -c++ -python bindings/otpnitro.i

base24:
	$(CXX)  $(CXXFLAGS) -L. base24.cpp    $(EXTRAS) -o $(BASNAME) -lotpnitro
	$(STRIPCM) $(BASNAME)

prngtest:
	$(CXX)  $(CXXFLAGS) -L. prngtest.cpp  $(EXTRAS) -o prngtest -lotpnitro

otpnitro-lib:
	$(CXX)  $(CXXFLAGS) -shared $(EXTRAS) $(MODULES) -o $(LIBNAME)
	$(STRIPCM) -x $(LIBNAME)

install:
	$(INSTALL)

clean:
	$(RM) $(MODULES) $(LIBNAME) $(EXENAME) $(BASNAME)

doc:
	doxygen doc/doxygen.conf

windows: all

windows-gui: windows
	cmd /s /c 'cd qotpnitro && qmake'
	cmd /s /c 'cd qotpnitro && mingw32-make'
	cmd /c copy qotpnitro\release\qotpnitro.exe .
	candle packages\\windows\\otpnitro.wxs
	light otpnitro.wixobj

freebsd: all
	mkdir -p                  packages/freebsd/otpnitro/usr/local/bin
	mkdir -p                  packages/freebsd/otpnitro/usr/local/lib
	cp otpnitro               packages/freebsd/otpnitro/usr/local/bin
	cp base24                 packages/freebsd/otpnitro/usr/local/bin
	cp libotpnitro.so         packages/freebsd/otpnitro/usr/local/lib
	packages/freebsd/build.sh packages/freebsd/otpnitro/+MANIFEST
	pkg create -f txz      -r packages/freebsd/otpnitro -m packages/freebsd/otpnitro
	mv -f packages/freebsd/otpnitro/+MANIFEST.orig packages/freebsd/otpnitro/+MANIFEST

freebsd-python: bindings
	mkdir -p                  packages/freebsd/python-otpnitro/usr/local/lib/python2.7/site-packages
	cp bindings/_otpnitro.so  packages/freebsd/python-otpnitro/usr/local/lib/python2.7/site-packages
	cp bindings/otpnitro.py   packages/freebsd/python-otpnitro/usr/local/lib/python2.7/site-packages
	packages/freebsd/build.sh packages/freebsd/python-otpnitro/+MANIFEST
	pkg create -f txz      -r packages/freebsd/python-otpnitro -m packages/freebsd/python-otpnitro
	mv -f packages/freebsd/python-otpnitro/+MANIFEST.orig packages/freebsd/python-otpnitro/+MANIFEST

freebsd-gui: freebsd freebsd-python
	cd qotpnitro && qmake-qt4
	cd qotpnitro && make
	mkdir -p packages/freebsd/qotpnitro/usr/local/bin
	cp qotpnitro/qotpnitro packages/freebsd/qotpnitro/usr/local/bin
	strip packages/freebsd/qotpnitro/usr/local/bin/qotpnitro
	packages/freebsd/build.sh packages/freebsd/qotpnitro/+MANIFEST
	pkg create -f txz -r packages/freebsd/qotpnitro -m packages/freebsd/qotpnitro
	mv -f packages/freebsd/qotpnitro/+MANIFEST.orig packages/freebsd/qotpnitro/+MANIFEST

debian: all
	mkdir -p                  packages/debian/otpnitro/usr/bin
	mkdir -p                  packages/debian/otpnitro/usr/lib
	cp otpnitro               packages/debian/otpnitro/usr/bin
	cp base24                 packages/debian/otpnitro/usr/bin
	cp libotpnitro.so         packages/debian/otpnitro/usr/lib
	packages/debian/build.sh  packages/debian/otpnitro/DEBIAN/control
	fakeroot dpkg-deb --build packages/debian/otpnitro otpnitro_$(shell packages/debian/build.sh --all).deb
	mv -f packages/debian/otpnitro/DEBIAN/control.orig packages/debian/otpnitro/DEBIAN/control

debian-python: bindings
	mkdir -p                  packages/debian/python-otpnitro/usr/lib/python2.7/dist-packages
	cp bindings/otpnitro.py   packages/debian/python-otpnitro/usr/lib/python2.7/dist-packages
	cp bindings/_otpnitro.so  packages/debian/python-otpnitro/usr/lib/python2.7/dist-packages
	packages/debian/build.sh  packages/debian/python-otpnitro/DEBIAN/control
	fakeroot dpkg-deb --build packages/debian/python-otpnitro python-otpnitro_$(shell packages/debian/build.sh --all).deb
	mv -f packages/debian/python-otpnitro/DEBIAN/control.orig packages/debian/python-otpnitro/DEBIAN/control

debian-gui: debian debian-python
	cd qotpnitro && qmake
	cd qotpnitro && make
	mkdir -p                  packages/debian/qotpnitro/usr/bin
	cp qotpnitro/qotpnitro    packages/debian/qotpnitro/usr/bin
	strip                     packages/debian/qotpnitro/usr/bin/qotpnitro
	packages/debian/build.sh  packages/debian/qotpnitro/DEBIAN/control
	fakeroot dpkg-deb --build packages/debian/qotpnitro qotpnitro_$(shell packages/debian/build.sh --all).deb
	mv -f packages/debian/qotpnitro/DEBIAN/control.orig packages/debian/qotpnitro/DEBIAN/control

haiku:
	CXX=g++-x86 make
	mkdir -p           packages/haiku/otpnitro/develop/headers/otpnitro/
	mkdir -p           packages/haiku/otpnitro/apps/otpnitro/
	mkdir -p           packages/haiku/otpnitro/bin/
	mkdir -p           packages/haiku/otpnitro/lib/x86/
	cp *.h             packages/haiku/otpnitro/develop/headers/otpnitro/
	cp -fr doc         packages/haiku/otpnitro/apps/otpnitro/
	cp base24 otpnitro packages/haiku/otpnitro/bin/
	cp libotpnitro.so  packages/haiku/otpnitro/lib/x86/
	package create -C  packages/haiku/otpnitro  otpnitro-$(VERSION)-x86_gcc2.hpkg

haiku-gui: haiku
	cd qotpnitro && qmake-x86 QMAKE_CC=gcc-x86 QMAKE_CXX=g++-x86 QMAKE_LINK=g++-x86
	cd qotpnitro && make
	rc   -o qotpnitro/qotpnitro qotpnitro/qotpnitro.rdef
	xres -o qotpnitro/qotpnitro qotpnitro/qotpnitro.rsrc
	mimeset -f qotpnitro/qotpnitro
	mkdir -p               packages/haiku/qotpnitro/bin/
	cp qotpnitro/qotpnitro packages/haiku/qotpnitro/bin/
	mkdir -p               packages/haiku/qotpnitro/data/deskbar/menu/Applications/
	ln -f -s /boot/home/config/bin/qotpnitro packages/haiku/qotpnitro/data/deskbar/menu/Applications/OTPNitro
	package create -C  packages/haiku/qotpnitro qotpnitro-$(VERSION)-x86_gcc2.hpkg
	
os2:
	set CXX=g++ && make
	
os2-gui:
	cd qotpnitro && qmake
	cd qotpnitro && make

osx: all
	tar -zcf otpnitro-$(VERSION)-osx.tgz otpnitro base24 libotpnitro.so

osx-gui: osx
	cd qotpnitro && qmake
	cd qotpnitro && make
	cd qotpnitro && tar -zcf ../qotpnitro-$(VERSION)-osx.tgz qotpnitro.app

scan-build:
	scan-build -v -o /tmp/otpnitro gmake
