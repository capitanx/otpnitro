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

#include <fstream>
#include <string.h>

#ifndef _MSC_VER
# include <dirent.h>
#endif

#ifdef __unix__
# include <sys/stat.h>
#elif  __APPLE__
# include <sys/stat.h>
#endif

#include "otpnitro.h"

using namespace std;

/*!
 * @brief Configuration, path and pages management
 */
class Config {
		char	REL_PATH[MAX_PATH];
		char	RND_DEV[MAX_PATH];
		int		MAX_CHARS;
		int		MAX_PAGES;

	public:
				Config(void);
		char *	getRndDev();
		int		getChars();
		int		getPages();
		char *	getPath();
		void	setRndDev(char *);
		void	setChars(int);
		void	setPages(int);
		void	setPath( char * );
		void	saveConfig();
};

