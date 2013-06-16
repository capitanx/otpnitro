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
else
	RM = rm -f
endif

CPPFLAGS = -O3 -Wall -Wextra -pedantic -I.
MODULES  = rand.o page.o crypto.o text.o

all: $(MODULES) otpnitro

otpnitro:
	$(CC)  $(CPPFLAGS) $(MODULES) otpnitro.cpp -o otpnitro

clean:
	$(RM) $(MODULES) otpnitro otpnitro.exe
