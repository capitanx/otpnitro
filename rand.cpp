/**
 * OTPNitro
 *
 *  Copyright 2014 by capi_x <capi_x@haibane.org>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0 <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

#include "rand.h"
#include "otpnitro.h"

#include <sys/time.h>
#include <fcntl.h>
#ifdef DEBUG
# include <iostream>
#endif

#ifdef __HAIKU__
#include <unistd.h>
#endif

/*!
 * @brief The Rand constructor generate a new random seed
 * @return Rand object
 */
Rand::Rand()
{
	srand(this->genSeed());
#ifdef DEBUG
	cout << "Seed: " << seed << endl;
#endif
}

/*!
 * @brief This function get the tick number from the CPU
 * @return (ulong)tsc
 *
 * In ix86 and amd64 uses RDTSC to get the low ticks value. \n
 * In ARMv6 and ARMv7 currently uses a gettimeofday()
 */
unsigned long Rand::getTicks()
{
// TODO: Find a cpu time/ticks asm inline for ARMv6 and ARMv7
#ifdef __arm__
	struct timeval usecs;
	gettimeofday(&usecs, NULL);
	return usecs.tv_usec;
#else
	unsigned int hi,lo;
	unsigned long tsc;
	asm volatile (
			"cpuid \n"
			"rdtsc"
			: "=a"(lo), "=d"(hi)
			: "a"(0)
#ifdef __i386__
			: "%ecx");
#else
			: "%ebx", "%ecx");
#endif
	tsc = (unsigned long)lo;
	return tsc;
#endif
}

/*!
 * @brief Random seed setter
 * @param a The new seed
 */
void Rand::setSeed(float a)
{
	seed = a;
	srand(seed);
#ifdef DEBUG
	cout << "Seed: " << seed << endl;
#endif
}

/*!
 * @brief Tries to find a /dev/random and return a byte, if not uses the rand() function
 * @return (int)rand
 */

int trand() {
	int  fdev;
	char crnd;

	fdev = open("/dev/random", O_RDONLY);

	if(fdev < 0)
		return(rand());

	return((int)read(fdev,&crnd,1));
}

/*!
 * @brief Random sed getter
 * @return (float)seed
 */
float Rand::getSeed()
{
	return(seed);
}

/*!
 * @param Generate a new seed using some black magic
 * @return (float)seed
 *
 * seed = (float)( (usecs.tv_usec + getpid()) ^ (int(Rand::getTicks()) << 16) / 10000 );
 */
float Rand::genSeed()
{
	struct timeval usecs;
	gettimeofday(&usecs, NULL);
	seed = (float)( (usecs.tv_usec + getpid()) ^ (int(Rand::getTicks()) << 16) / 10000 );
	return(seed);
}

/*!
 * @param Get a random char
 * @return (char)rnd
 */
char Rand::getChar()
{
	return trand() % 256;
}

/*!
 * @brief Get a random [A-Z] char
 * @return (char)rnd
 */
char Rand::getLetter()
{
	// TY @MarioVilas for ur help here :-)
	char rnd = '0';

	// Ugly GCC hack, sorry :(
	while(rnd < 0x41 || rnd > 0x5A)
		rnd = trand();

	return rnd;
}

/*!
 * @brief Get a random number
 * @param a number len
 * @return (int)rnd
 */
int  Rand::getNumber(int a)
{
	return trand() % a+1;
}
