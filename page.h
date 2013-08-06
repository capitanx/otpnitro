#include <fstream>
#include <string.h>

#ifndef _MSC_VER
# include <dirent.h>
#endif

#ifdef __unix__
# include <sys/stat.h>
#endif

#include "rand.h"
#include "otpnitro.h"

using namespace std;

class Page {
    	string	dirPath(string);
    	string	filePath(int, string);
	public:
		bool   generate(string);
		bool   write(int, string, string);
		int    next(string);
		bool   burn(int,string);
		string read(int, string);
		string get();
		string list();
};

