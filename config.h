#include <fstream>
#include <string.h>

#include "otpnitro.h"

using namespace std;

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

