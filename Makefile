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
	RM = del /Q
	LIBNAME = otpnitro.dll
	INSTALL = mkdir "%ProgramFiles%\otpnitro" & copy /E otpnitro.exe "%ProgramFiles%\otpnitro" & copy /E otpnitro.dll "%ProgramFiles%\otpnitro" & copy /E PAGES "%ProgramFiles%\otpnitro"
else
	RM = rm -f
	LIBNAME = otpnitro.so
	INSTALL = cp -f otpnitro /usr/bin && cp -f otpnitro.so /usr/lib && mkdir -p /usr/share/PAGES
endif

CPPFLAGS = -O3 -Wall -Wextra -pedantic -I. -L.
MODULES  = rand.o page.o crypto.o text.o

all: $(MODULES) otpnitro-lib otpnitro

otpnitro:
	$(CC)  $(CPPFLAGS) otpnitro.cpp -o otpnitro -lotpnitro

otpnitro-lib:
	$(CC)  $(CPPFLAGS) -shared $(MODULES) -o $(LIBNAME)

install:
	$(INSTALL)

clean:
	$(RM) $(MODULES) otpnitro otpnitro.exe $(LIBNAME)
