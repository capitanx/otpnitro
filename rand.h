#include <stdlib.h>
#include <time.h>

#ifdef __unix__
# include <sys/types.h>
# include <unistd.h>
#endif

//using namespace std;

#ifdef WIN32
# include <process.h>
# define getpid _getpid
#endif

class Rand {
	float seed;

	public:
		Rand();
		unsigned long getTicks();
		void  setSeed(float);
		int   getSeed();
		float genSeed();
		char  getChar();
		char  getLetter();
		int   getNumber(int);
};

