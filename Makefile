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

CC = g++
PACKAGE = otpnitro
VERSION = 0.1

ifdef SystemRoot
	RM = del /Q otpnitro.exe otpnitro.wixobj otpnitro.wixpdb otpnitro.msi
	LIBNAME = otpnitro.dll
	EXTRAS  = -static-libgcc -static-libstdc++
	INSTALL = candle otpnitro.wxs & light otpnitro.wixobj
else
	RM = rm -f otpnitro
	LIBNAME = libotpnitro.so
	EXTRAS  =
	INSTALL = cp -f otpnitro /usr/bin && cp -f libotpnitro.so /usr/lib
endif

CPPFLAGS = -O3 -Wall -Wextra -pedantic -I. -L.
#CPPFLAGS += -DDEBUG
MODULES  = rand.o page.o crypto.o text.o

all: $(MODULES) otpnitro-lib otpnitro

otpnitro:
	$(CC)  $(CPPFLAGS) otpnitro.cpp  $(EXTRAS) -o otpnitro -lotpnitro

prngtest:
	$(CC)  $(CPPFLAGS) prngtest.cpp  $(EXTRAS) -o prngtest -lotpnitro

otpnitro-lib:
	$(CC)  $(CPPFLAGS) -fPIC -shared $(EXTRAS) $(MODULES) -o $(LIBNAME)

install:
	$(INSTALL)

clean:
	$(RM) $(MODULES) $(LIBNAME)
