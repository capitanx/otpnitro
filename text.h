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

