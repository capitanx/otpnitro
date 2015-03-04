/**
 * OTPNitro
 *
 *  Copyright 2014-2015 by capi_x <capi_x@haibane.org>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0 <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

#include <stdlib.h>
#include <time.h>

#ifdef __unix__
# include <sys/types.h>
# include <unistd.h>
#elif  __APPLE__
# include <sys/types.h>
# include <unistd.h>
#elif  WIN32
# include <WINDOWS.H>
# include <WINCRYPT.H>
# include <process.h>
# define getpid _getpid
#elif  __OS2__
# include <process.h>
# include <unistd.h>
#endif


/*!
 * @brief This class provides all secure random rutines
 */
class Rand {
	float seed;
	int   fdev;
	int   t_rand();

	public:
		Rand();
		~Rand();
		unsigned long getTicks();
		void  setSeed(float);
		float getSeed();
		float genSeed();
		char  getChar();
		char  getLetter();
		int   getNumber(int);
};

