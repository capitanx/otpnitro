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
	LIBNAME = lib\\otpnitro.dll
else
	RM = rm -f
	LIBNAME = lib/otpnitro.so
endif

CPPFLAGS = -O3 -Wall -Wextra -pedantic -I.
MODULES  = rand.o page.o crypto.o text.o

all: $(MODULES) otpnitro otpnitro-lib

otpnitro:
	$(CC)  $(CPPFLAGS) $(MODULES) otpnitro.cpp -o otpnitro

otpnitro-lib:
	$(CC)  $(CPPFLAGS) -shared $(MODULES) -o $(LIBNAME)

clean:
	$(RM) $(MODULES) otpnitro otpnitro.exe $(LIBNAME)
