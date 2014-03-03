#include "rand.h"
#include "otpnitro.h"

#include <sys/time.h>
#ifdef DEBUG
# include <iostream>
#endif

Rand::Rand()
{
	srand(this->genSeed());
#ifdef DEBUG
	cout << "Seed: " << seed << endl;
#endif
}

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
			: "%ebx", "%ecx");
	tsc = ((unsigned long)lo) | (((unsigned long)hi) << 32);
	return tsc;
#endif
}

void Rand::setSeed(float a)
{
	seed = a;
	srand(seed);
#ifdef DEBUG
	cout << "Seed: " << seed << endl;
#endif
}

float Rand::getSeed()
{
	return(seed);
}

float Rand::genSeed()
{
	struct timeval usecs;
	gettimeofday(&usecs, NULL);
	seed = (usecs.tv_usec + getpid()) ^ (int(Rand::getTicks()) / 100000);
	return(seed);
}

char Rand::getChar()
{
	return rand() % 256;
}

char Rand::getLetter()
{
	// TY @MarioVilas for ur help here :-)
	char rnd = '0';

	// Ugly GCC hack, sorry :(
	while(rnd < 0x41 || rnd > 0x5A)
		rnd = rand();

	return rnd;
}

int  Rand::getNumber(int a)
{
	return rand() % a+1;
}
