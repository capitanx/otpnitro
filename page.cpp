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
#include <algorithm>

#include "page.h"
#include "config.h"

#ifdef __HAIKU__
#include <sys/stat.h>
#endif

using namespace std;

/*!
 * @brief The constructor sets all parameters from the Config object
 * @return Page object
 */
Page::Page(void)
{
	Config * cfg = new Config;
	strncpy(REL_PATH, cfg->getPath(), MAX_PATH - 1);
	MAX_PAGES	= cfg->getPages();
	MAX_CHARS	= cfg->getChars();
}

/*!
 * @brief Returns the PATH of a given book
 * @param id ID of a valid book
 * @return dirpath
 */
string Page::dirPath(string id)
{
	string dirpath = REL_PATH;
	dirpath.append(id);

	return(dirpath);
}

/*!
* @brief Make the PATH of a given book (mkdir)
* @param id ID of a valid book
* @return ret
*/
int	Page::genPath(string id)
{
	int ret = 0;

	// Create OTP folder for ID
#if     defined(__unix__) || defined(__APPLE__) || defined(__HAIKU__)
	ret = mkdir(dirPath(id).c_str(), S_IRWXU|S_IRGRP|S_IXGRP);
#elif   __OS2__
	ret = mkdir(dirPath(id).c_str(), 0777);
#else
	ret = mkdir(dirPath(id).c_str());
#endif
	return(ret);
}


/*!
 * @brief Returns the file path of a book for a given page
 * @param page Page num
 * @param id   Book ID
 * @return filepath
 */
string Page::filePath(int page, string id)
{
	char pagetxt[10];
	sprintf(pagetxt,"%i",page);

	string filepath  = REL_PATH;
	filepath.append(id).append("/").append(pagetxt).append(".dat");

	return(filepath);
}

/*!
 * @brief Secure page file delete
 * @param page Page num
 * @param id   Book ID
 * @return (bool) true == ok
 */
bool Page::burn(int page, string id)
{
	// Open file
	ifstream ifpage;
	ifpage.open(filePath(page, id).c_str());

	// Get file size
	int begin = ifpage.tellg();
	ifpage.seekg (0, ios::end);
	int end  = ifpage.tellg();
	int size = end - begin;

	if (size == 0)
		return false;

	ifpage.close();

	// Fill zeros
	ofstream ofpage;
	ofpage.open(filePath(page, id).c_str());
	for (int a=0; a<size; a++)
	ofpage.put(0x00);
	ofpage.close();

	// Remove file
	remove(filePath(page, id).c_str());

	return true;

}

/*!
 * @brief Returns the next unused page num for a book
 * @param id Book ID
 * @return (int)pagenum
 */
int	Page::next(string id)
{
	string filename;
	DIR *pDIR;
	struct dirent *entry;
	string path = REL_PATH;
	path.append("/").append(id);
	if( (pDIR = opendir(path.c_str())) != 0 ){
		while((entry = readdir(pDIR)) != 0 ){
			if( (strcmp(entry->d_name, ".") != 0) &&
			    (strcmp(entry->d_name, "..") != 0) ) {
				
				filename = entry->d_name;
				break;
			}
		}
	} else
		return -1;

	closedir(pDIR);

	if (filename.length() == 0)
		return -1;

	unsigned pos = filename.find(".");
	return atoi(filename.substr(0,pos).c_str());
}

/*!
 * @brief Returns the last generated page num for a book
 * @param id Book ID
 * @return (int)pagenum
 */
int	Page::last(string id)
{
	string filename;
	DIR *pDIR;
	struct dirent *entry;
	string path = REL_PATH;
	unsigned pos = 0;
	unsigned pgn = 0;
	unsigned cur = 0;

	path.append("/").append(id);
	if( (pDIR = opendir(path.c_str())) != 0 ){
		while((entry = readdir(pDIR)) != 0 ) {
            filename = entry->d_name;
            pos = filename.find(".");
            cur = atoi(filename.substr(0,pos).c_str());
            if (pgn < cur)
                pgn = cur;
		}
	} else
		return -1;

	closedir(pDIR);

	if (filename.length() == 0)
		return -1;

    return pgn;
}

bool Page::write(int page, string id, string ciphertext)
{
	// Write PAGE
	ofstream fpage;
	fpage.open(filePath(page, id).c_str());
	fpage << ciphertext;
	fpage.close();

	return true;
}

/*!
 * @brief Get the ciphertext page from a given book
 * @param page Page num
 * @param id Book ID
 * @return ciphertext
 */
string Page::read(int page, string id)
{
	// Read PAGE
	ifstream fpage;
	fpage.open(filePath(page, id).c_str());

	string ciphertext( (std::istreambuf_iterator<char>(fpage) ),
					   (std::istreambuf_iterator<char>()    ) );

	fpage.close();

	return(ciphertext);
}

/*!
 * @brief Get page length
 * @param page Page num
 * @param id Book ID
 * @return ciphertext
 */
int	Page::getLength(int page, string id)
{
	// Return PAGE len
	return this->read(page,id).size();
}

/*!
 * @brief Generate ciphertext page using the Rand class
 * @return ciphertext
 */
string Page::get()
{
	string ciphtext;
	Rand * rnd = new Rand;

	for (int ltr = 0; ltr < (MAX_CHARS); ltr++)
		ciphtext.append(1,rnd->getLetter());

	delete rnd;
	return ciphtext;
}

/*!
 * @brief Generate a complete Book using Page::get() and write it to the disk
 * @param id New book ID
 * @return (bool) true == ok
 */
bool Page::generate(string id)
{
    // Create new dir
    genPath(id);

    int pagenum = 0;

    if (this->last(id) >= 0) {
        pagenum = this->last(id);
	}

	for (; pagenum < MAX_PAGES; pagenum++) {
		clock_t goal = 1 + clock();
		while (goal > clock());
		string pagetext = this->get();
		this->write(pagenum,id,pagetext);
	}
	return true;
}

/*!
 * @brief Returns a list of valid books
 * @return files
 */
string Page::list()
{
	string files;
	DIR *pDIR;
	string path = REL_PATH;

	if( (pDIR = opendir(path.c_str())) != 0 ){
		struct dirent *entry;
		while((entry = readdir(pDIR)) != 0 ){
			if( (strcmp(entry->d_name, ".") != 0)  &&
			    (strcmp(entry->d_name, "..") != 0) &&
			    (strcmp(entry->d_name, ".dummy") != 0) &&
			    (strcmp(entry->d_name, ".DS_Store") != 0) ) {
				
				files.append(entry->d_name);
				files.append("\n");
				continue;
			}
		}
	} else
		return "";

	closedir(pDIR);
	
	transform(files.begin(), files.end(), files.begin(), ::toupper);
	return(files);
}
