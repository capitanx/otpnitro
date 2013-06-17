#include <stdlib.h>
#include <time.h>
using namespace std;

#ifdef WIN32
# include <process.h>
# define getpid _getpid
#endif

class Random {
	float seed;

	public:
		Random();
		void  setSeed(float);
		int   getSeed();
		float genSeed();
		char  getChar();
		char  getLetter();
		int   getNumber(int);
};

