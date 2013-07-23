#include <iostream>

#include "page.h"
#include "otpnitro.h"

using namespace std;


string	Page::dirPath(string id) {
	string dirpath = REL_PATH;
	dirpath.append(id);

	return(dirpath);
}

string	Page::filePath(int page, string id) {
    	char pagetxt[10];
	sprintf(pagetxt,"%i",page);

	string filepath  = REL_PATH;
	filepath.append(id).append("/").append(pagetxt).append(".dat");

	return(filepath);
}

bool	Page::burn(int page, string id) {
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

int	Page::next(string id) {
    	string filename;
	DIR *pDIR;
	struct dirent *entry;
	string path = REL_PATH;
	path.append("/").append(id);
	if( (pDIR = opendir(path.c_str())) != NULL ){
		while((entry = readdir(pDIR)) != NULL){
			if( (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0) ) {
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


bool	Page::write(int page, string id, string ciphertext) {

	// Create OTP folder for ID
#ifdef __unix__
	mkdir(dirPath(id).c_str(), S_IRWXU|S_IRGRP|S_IXGRP);
#else
	mkdir(dirPath(id).c_str());
#endif

	// Write PAGE
	ofstream fpage;
	fpage.open(filePath(page, id).c_str());
	fpage << ciphertext;
	fpage.close();
	
	return true;
}

string	Page::read(int page, string id) {

	// Read PAGE
	ifstream fpage;
	fpage.open(filePath(page, id).c_str());

	string ciphertext( (std::istreambuf_iterator<char>(fpage) ),
		           (std::istreambuf_iterator<char>()    ) );

	fpage.close();

	return(ciphertext);
}

string	Page::get() {
    	string ciphtext;
	Random * rnd = new Random;

	for (int ltr = 0; ltr < (MAX_CHARS); ltr++)
		ciphtext.append(1,rnd->getLetter());

	delete rnd;
	return ciphtext;
}

bool	Page::generate(string id) {

#ifdef	__unix__
	mkdir(REL_PATH, S_IRWXU|S_IRGRP|S_IXGRP);
#else
	mkdir(REL_PATH);
#endif

	for (int pagenum = 0; pagenum < MAX_PAGES; pagenum++) {
		clock_t goal = 1 + clock();
		while (goal > clock());
		string pagetext = this->get();
		this->write(pagenum,id,pagetext);
	}
	return true;
}

string	Page::list() {
	string files;

	DIR *pDIR;
	struct dirent *entry;
	string path = REL_PATH;
//	TODO: add support for list pages for a id
//	path.append("/").append(id);
	if( (pDIR = opendir(path.c_str())) != NULL ){
		while((entry = readdir(pDIR)) != NULL){
			if( (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0) && (strcmp(entry->d_name, ".dummy") != 0) ) {
				files.append(entry->d_name);
				files.append("\n");
				break;
			}
		}
	} else
            return "";

	closedir(pDIR);
	return(files);
}
