#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//#ifdef __WINDOWS__
#include <process.h>
# define getpid _getpid
//#endif

class Random {
	float seed;

	public:
		Random();
		void setSeed(int);
		int  getSeed();
		char getChar();
		char getLetter();
		int  getNumber(int);
};

