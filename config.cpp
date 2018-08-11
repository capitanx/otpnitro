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

#include <iostream>
#include <stdlib.h>

#include "config.h"

#ifdef __HAIKU__
#include <sys/stat.h>
#endif

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
	strncpy(REL_PATH, "PAGES/",       MAX_PATH - 1);
	strncpy(RND_DEV,  "/dev/urandom", MAX_PATH - 1);
	MAX_PAGES	= 1000;
	MAX_CHARS	= 1020;

	// Unix and windows path
#if	!defined(__DJGPP__) && (defined(__unix__) || defined(__APPLE__) || defined(__HAIKU__))
	string cfgPath = getenv("HOME");
	cfgPath.append("/.otpnitro");
	string pagesPath = cfgPath;
	pagesPath.append("/PAGES/");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(cfgPath.c_str(), S_IRWXU|S_IRGRP|S_IXGRP);
	mkdir(pagesPath.c_str(), S_IRWXU|S_IRGRP|S_IXGRP);
	cfgPath.append("/otpnitro.ini");
#elif __OS2__
	string cfgPath = getenv("HOME");
	cfgPath.append("\\.otpnitro");
	string pagesPath = cfgPath;
	pagesPath.append("\\PAGES\\");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(cfgPath.c_str(), 0777);
	mkdir(pagesPath.c_str(), 0777);
	cfgPath.append("\\otpnitro.ini");
#elif !defined(WIN9X) && defined(_WIN32)
	string cfgPath = getenv("APPDATA");
	cfgPath.append("\\otpnitro");
	string pagesPath = cfgPath;
	pagesPath.append("\\PAGES\\");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(cfgPath.c_str());
	mkdir(pagesPath.c_str());
	cfgPath.append("\\otpnitro.ini");
#elif WIN9X
	string cfgPath   = "";
	string pagesPath = cfgPath;
	pagesPath.append("PAGES\\");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(pagesPath.c_str());
	cfgPath.append("otpnitro.ini");
#else
	string cfgPath   = "";
	string pagesPath = cfgPath;
	pagesPath.append("PAGES\\");
	strncpy(REL_PATH, pagesPath.c_str(), MAX_PATH - 1);
	mkdir(pagesPath.c_str(),S_IRWXU|S_IRGRP|S_IXGRP);
	cfgPath.append("otpnitro.ini");
#endif

	// Open file
	ifstream ifcfg;
	ifcfg.open(cfgPath.c_str());

	if (!ifcfg.is_open()) {
		saveConfig();
		return;
	}

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
		else if (key.compare("rnddev") == 0)
			strncpy(RND_DEV, value.c_str(), MAX_PATH - 1);
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
void Config::saveConfig(void) {

	// Unix and windows path
#if	!defined(__DJGPP__) && (defined(__unix__) || defined(__APPLE__) || defined(__HAIKU__))
	string cfgPath = getenv("HOME");
	cfgPath.append("/.otpnitro/otpnitro.ini");
#elif !defined(WIN9X) && defined(_WIN32)
	string cfgPath = getenv("APPDATA");
	cfgPath.append("\\otpnitro\\otpnitro.ini");
#else
	string cfgPath = "otpnitro.ini";
#endif

	// Fill config
	ofstream ofcfg;
	ofcfg.open(cfgPath.c_str());
	ofcfg << "# OTPNITRO config file" << endl;
	ofcfg << "# --------------------" << endl;
	ofcfg << "# Please, use the format key=value whithout spaces near equal char." << endl;
	ofcfg << "# The path must be terminated on '/' or '\\'" << endl << endl;
	ofcfg << "[core]"  << endl;
	ofcfg << "path="   << REL_PATH  << endl;
	ofcfg << "pages="  << MAX_PAGES << endl;
	ofcfg << "chars="  << MAX_CHARS << endl;
	ofcfg << "rnddev=" << RND_DEV   << endl;
	ofcfg.close();

}

/*!
 * @brief Returns the current RND device
 */
char * Config::getRndDev()
{
	return RND_DEV;
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
int Config::getChars()
{
	return MAX_CHARS;
}

/*!
 * @brief Returns the number of generated pages
 * @return MAX_PAGES
 */
int	Config::getPages()
{
	return MAX_PAGES;
}

/*!
 * @brief Set a new RND device
 */
void Config::setRndDev( char * rnd )
{
	strncpy(RND_DEV, rnd,  MAX_PATH - 1);
}


/*!
 * @brief Set a new PATH to be used
 */
void Config::setPath( char * path )
{
	strncpy(REL_PATH, path, MAX_PATH - 1);
}

/*!
 * @brief Set the max PATH length
 * @param chars MAX_CHARS (int)
 */
void Config::setChars(int chars)
{
	MAX_CHARS = chars;
}

/*!
 * @brief Set the num of pages to be generated
 * @param pages MAX_PAGES (int)
 */
void Config::setPages(int pages)
{
	MAX_PAGES = pages;
}
