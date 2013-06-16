#include <rand.h>

Random::Random() {
    	seed = time(NULL) * getpid() + clock() * -1000000000;
	srand(seed);
}

void Random::setSeed(int a) {
	seed = a;
	srand(seed);
}

int  Random::getSeed() {
    	return(seed);
}

char Random::getChar() {
    	return rand() % 256;
}

char Random::getLetter() {
    	return (char)(0x41 + (rand() % 26));
}

int  Random::getNumber(int a) {
	return rand() % a+1;
}
