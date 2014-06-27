#include <iostream>

using namespace std;

/*!
 * @brief Text and encoding related functions
 */
class Text {
	public:
		//! @brief Message string
		string	msg;
		//! @brief Book ID
		string	book;
		//! @brief Sender identificative string (3 letters, for example: AVD)
		string	from;
		//! @brief Page num (int)
		int		page;

		void	replaceAll(string&, const string&, const string&);
		void	create(int,string,string,string);
		string	print(int);
		string	encodeB26(unsigned char *, long);
		void	decodeB26(unsigned char *, string);
		void	parse(string);
};

