#include "rand.h"
#include "otpnitro.h"

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

void Rand::setSeed(float a)
{
	seed = a;
	srand(seed);
#ifdef DEBUG
	cout << "Seed: " << seed << endl;
#endif
}

int  Rand::getSeed()
{
	return(seed);
}

float Rand::genSeed()
{
	seed = time(0) * getpid() + clock() * MAGIC_K;
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
