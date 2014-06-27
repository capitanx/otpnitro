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
		int		MAX_CHARS;
		int		MAX_PAGES;

	public:
				Config(void);
		int		getChars();
		int		getPages();
		char *	getPath();
		void	setChars(int);
		void	setPages(int);
		void	setPath( char * );
		void	saveConfig();
};

