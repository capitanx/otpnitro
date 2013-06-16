#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>


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
};

