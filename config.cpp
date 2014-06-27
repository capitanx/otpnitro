#include <iostream>
#include <stdlib.h>

#include "config.h"
#include "otpnitro.h"

using namespace std;

/*!
 * @brief Config constructor
 * @return Config object
 *
 * <b>Default PATH</b> \n
 * \t Win32: The PATH is \%APPDATA\%\\\.otpnitro\\ \n
 * \t Unix:  The PATH is $HOME/.otpnitro/ \n
 * \n
 * <b>Files</b> \n
 * The config file is always otpnitro.ini in the PATH root. \n
 * The pages are stored on the PAGES folder from the PATH root.
 */
Config::Config(void)
{
	// Default values
	strncpy(REL_PATH, "PAGES/", MAX_PATH - 1);
	MAX_PAGES	= 1000;
	MAX_CHARS	= 1020;

	// Unix and windows path
#ifdef __unix__
	string cfgPath = getenv("HOME");
	cfgPath.append("/.otpnitro");
	string pagesPath = cfgPath;
	pagesPath.append("/PAGES/");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(cfgPath.c_str(), S_IRWXU|S_IRGRP|S_IXGRP);
	cfgPath.append("/otpnitro.ini");
#elif  __APPLE__
	string cfgPath = getenv("HOME");
	cfgPath.append("/.otpnitro");
	string pagesPath = cfgPath;
	pagesPath.append("/PAGES/");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(cfgPath.c_str(), S_IRWXU|S_IRGRP|S_IXGRP);
	cfgPath.append("/otpnitro.ini");
#else
	string cfgPath = getenv("APPDATA");
	cfgPath.append("\\otpnitro");
	string pagesPath = cfgPath;
	pagesPath.append("\\PAGES\\");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(cfgPath.c_str());
	cfgPath.append("\\otpnitro.ini");
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

/*!
 * @brief Save the config to the default PATH \n
 * If the config file doesnt exist it will create it with default values
 */
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

/*!
 * @brief Returns the current PATH
 */
char *	Config::getPath()
{
	return REL_PATH;
}

/*!
 * @brief Returns the max PATH length
 * @return MAX_CHARS
 */
int		Config::getChars()
{
	return MAX_CHARS;
}

/*!
 * @brief Returns the number of generated pages
 * @return MAX_PAGES
 */
int		Config::getPages()
{
	return MAX_PAGES;
}

/*!
 * @brief Set a new PATH to be used
 */
void	Config::setPath( char * path)
{
	strncpy(REL_PATH, path, MAX_PATH - 1);
}

/*!
 * @brief Set the max PATH length
 * @param chars MAX_CHARS (int)
 */
void	Config::setChars(int chars)
{
	MAX_CHARS = chars;
}

/*!
 * @brief Set the num of pages to be generated
 * @param pages MAX_PAGES (int)
 */
void	Config::setPages(int pages)
{
	MAX_PAGES = pages;
}
