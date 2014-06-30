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

#include <fstream>
#include <string.h>

#ifndef _MSC_VER
# include <dirent.h>
#endif

#ifdef __unix__
# include <sys/stat.h>
#elif __APPLE__
# include <sys/stat.h>
#endif

#include "rand.h"
#include "otpnitro.h"

using namespace std;

/*!
 * @brief Page operations class
 */
class Page {
		char	REL_PATH[MAX_PATH];
		int		MAX_CHARS;
		int		MAX_PAGES;
    	string	dirPath(string);
    	string	filePath(int, string);

	public:
				Page(void);
		bool	generate(string);
		bool	write(int, string, string);
		int		next(string);
		bool	burn(int,string);
		string	read(int, string);
		string	get();
		string	list();
};

