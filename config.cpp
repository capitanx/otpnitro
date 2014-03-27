#include <iostream>
#include <stdlib.h>

#include "config.h"
#include "otpnitro.h"

using namespace std;

Config::Config(void)
{
	// Default values
	strncpy(REL_PATH, "PAGES/", MAX_PATH - 1);
	MAX_PAGES	= 1000;
	MAX_CHARS	= 1020;

	// Unix and windows path
#ifdef __unix__
	string cfgPath = getenv("HOME");
	cfgPath.append("/.otpnitro/otpnitro.ini");
#else
	string cfgPath = getenv("APPDATA");
	cfgPath.append("\\otpnitro\\otpnitro.ini");
#endif

	// Open file
	ifstream ifcfg;
	ifcfg.open(cfgPath.c_str());

	if (!ifcfg.is_open())
		return;

	unsigned pos1;
	string line, key, value;
	while( getline(ifcfg, line) )
	{
		// Comments
		if (line[0] == '#')
			continue;

		// TODO: Future sections
		if (line[0] == '[')
			continue;

		pos1  = line.find("=");
		key   = line.substr(0,pos1);
		value = line.substr(pos1+1);

		if (key.compare("path") == 0)
			strncpy(REL_PATH, value.c_str(), MAX_PATH - 1);
		else if (key.compare("pages") == 0)
			MAX_PAGES = atoi(value.c_str());
		else if (key.compare("chars") == 0)
			MAX_CHARS = atoi(value.c_str());
	}

	ifcfg.close();

#ifdef DEBUG
	printf("P: %s A: %i C: %i\n",REL_PATH,MAX_PAGES,MAX_CHARS);
#endif
}

void	Config::saveConfig(void) {

	// Unix and windows path
#ifdef __unix__
	string cfgPath = getenv("HOME");
	cfgPath.append("/.otpnitro/otpnitro.ini");
#else
	string cfgPath = getenv("APPDATA");
	cfgPath.append("\\otpnitro\\otpnitro.ini");
#endif

	// Fill config
	ofstream ofcfg;
	ofcfg.open(cfgPath.c_str());
	ofcfg << "# OTPNITRO config file" << endl;
	ofcfg << "# --------------------" << endl;
	ofcfg << "# Please, use the format key=value whithout spaces near equal char." << endl;
	ofcfg << "# The path must be terminated on '/' or '\\'" << endl << endl;
	ofcfg << "[core]" << endl;
	ofcfg << "path="  << REL_PATH  << endl;
	ofcfg << "pages=" << MAX_PAGES << endl;
	ofcfg << "chars=" << MAX_CHARS << endl;
	ofcfg.close();

}

char *	Config::getPath()
{
	return REL_PATH;
}

int		Config::getChars()
{
	return MAX_CHARS;
}

int		Config::getPages()
{
	return MAX_PAGES;
}

void	Config::setPath( char * path)
{
	strncpy(REL_PATH, path, MAX_PATH - 1);
}

void	Config::setChars(int chars)
{
	MAX_CHARS = chars;
}

void	Config::setPages(int pages)
{
	MAX_PAGES = pages;
}
