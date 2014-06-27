#include <iostream>

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

