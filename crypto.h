#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Crypto {
	public:
		void   replaceAll(string&, const string&, const string&);
		string decrypt(string,string);
		string encrypt(string,string);
};

