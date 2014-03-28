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

CXX = clang++
#CXX = g++
PACKAGE = otpnitro
VERSION = 0.2
PREFIX = /usr

CPPFLAGS = -O3 -Wall -Wextra -pedantic -I.
#CPPFLAGS += -ggdb
#CPPFLAGS += --analyze
#CPPFLAGS += -DDEBUG

ifdef SystemRoot
	RM = cmd /c del /Q otpnitro.exe
	LIBNAME = otpnitro.dll
	EXTRAS  = -static-libgcc -static-libstdc++
	INSTALL = candle packages\\windows\\otpnitro.wxs & light otpnitro.wixobj
else
	RM = rm -f otpnitro
	LIBNAME = libotpnitro.so
	EXTRAS  =
	CPPFLAGS += -fPIC
	INSTALL = cp -f otpnitro $(PREFIX)/bin && cp -f libotpnitro.so $(PREFIX)/lib
endif

MODULES  = rand.o page.o crypto.o text.o config.o

Debug: all

Release: all

all: $(MODULES) otpnitro-lib otpnitro

otpnitro:
	$(CXX)  $(CPPFLAGS) -L. otpnitro.cpp  $(EXTRAS) -o otpnitro -lotpnitro

prngtest:
	$(CXX)  $(CPPFLAGS) -L. prngtest.cpp  $(EXTRAS) -o prngtest -lotpnitro

otpnitro-lib:
	$(CXX)  $(CPPFLAGS) -shared $(EXTRAS) $(MODULES) -o $(LIBNAME)

install:
	$(INSTALL)

clean:
	$(RM) $(MODULES) $(LIBNAME)

windows: all
	candle packages\\windows\\otpnitro.wxs
	light otpnitro.wixobj

freebsd: all
	mkdir -p packages/freebsd/otpnitro/usr/local/bin
	mkdir -p packages/freebsd/otpnitro/usr/local/lib
	cp otpnitro packages/freebsd/otpnitro/usr/local/bin
	cp libotpnitro.so packages/freebsd/otpnitro/usr/local/lib
	mkdir -p packages/freebsd/otpnitrogui/usr/local/bin
	cp $(HOME)/.upp/_out/otpnitrogui/GCC.Blitz.Force_Speed.Gui.Shared.Sse2/otpnitrogui packages/freebsd/otpnitrogui/usr/local/bin
	pkg create -f txz -r packages/freebsd/otpnitro -m packages/freebsd/otpnitro
	pkg create -f txz -r packages/freebsd/otpnitrogui -m packages/freebsd/otpnitrogui

debian: all
	mkdir -p packages/debian/otpnitro/usr/bin
	mkdir -p packages/debian/otpnitro/usr/lib
	cp otpnitro packages/debian/otpnitro/usr/bin
	cp libotpnitro.so packages/debian/otpnitro/usr/lib
	mkdir -p packages/debian/otpnitrogui/usr/bin
	cp $(HOME)/.upp/_out/otpnitrogui/CLANG.Blitz.Force_Speed.Gui.Shared.Sse2/otpnitrogui packages/debian/otpnitrogui/usr/bin
	fakeroot dpkg-deb --build packages/debian/otpnitro otpnitro_0.2_amd64.deb
	fakeroot dpkg-deb --build packages/debian/otpnitrogui otpnitrogui_0.2_amd64.deb

scan-build:
	scan-build -v -o /tmp/otpnitro gmake
