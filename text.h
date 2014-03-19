#include <iostream>

using namespace std;

class Text {
	public:
		string	msg;
		string	book;
		string	from;
		int		page;

		void	replaceAll(string&, const string&, const string&);
		void	create(int,string,string,string);
		string	print(int);
		string	encodeB26(unsigned char *, long);
		void	decodeB26(unsigned char *, string);
		void	parse(string);
};

