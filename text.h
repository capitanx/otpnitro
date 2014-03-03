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
		void	parse(string);
};

