/**
 * OTPNitro
 *
 *  Copyright 2014 by capi_x <capi_x@haibane.org>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0 <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

#include <iostream>
#include "otpnitro.h"

using namespace std;

/*!
 * @brief Crypt and decrypt class
 */
class Crypto {
		void   replaceAll(string&, const string&, const string&);

	public:
		string decrypt(string,string);
		string encrypt(string,string);
};

