#include <iostream>

using namespace std;

class Text {
	public:
		string msg;
		string to;
		string from;
		int    page;

		void replaceAll(string&, const string&, const string&);
		void create(int,string,string,string);
		void print(int);
		void parse(string);
};

