#include <rand.h>
#include "otpnitro.h"

#ifdef DEBUG
# include <iostream>
#endif

Random::Random() {
	srand(this->genSeed());
#ifdef DEBUG
	cout << "Seed: " << seed << endl;
#endif
}

void Random::setSeed(float a) {
	seed = a;
	srand(seed);
#ifdef DEBUG
	cout << "Seed: " << seed << endl;
#endif
}

int  Random::getSeed() {
    	return(seed);
}

float Random::genSeed() {
    	seed = time(NULL) * getpid() + clock() * MAGIC_K;
	return(seed);
}

char Random::getChar() {
    	return rand() % 256;
}

char Random::getLetter() {
    	// TY @MarioVilas for ur help here :-)
    	char rnd = '0';

	// Ugly GCC hack, sorry :(
    	while(rnd < 0x41 || rnd > 0x5A)
		rnd = rand();

    	return rnd;
}

int  Random::getNumber(int a) {
	return rand() % a+1;
}
