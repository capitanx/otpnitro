#include <algorithm>

#include "crypto.h"
#include "otpnitro.h"

/*!
 * replaceAll( str, from, to ) \n
 * @brief Replace all characters from a string
 * @param str The string pointer
 * @param from Character to be replaced
 * @param to Replace character
 */
void Crypto::replaceAll(std::string& str, const std::string& from, const std::string& to)
{
	if(from.empty())
		return;

	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

/*!
 * @brief Crypt a text string
 * @param in Original (not crypted) string
 * @param out The ciphered text to sum(26)
 * @return The crypted string
 *
 * This function also remove the newline chars and replace all spaces to the "JQ" from the original text before to be crypted
 */
string Crypto::encrypt(string in, string out)
{
	// To upper :-)
	transform(in.begin(), in.end(), in.begin(), ::toupper);

	// Replace spaces to JQ char
	this->replaceAll(in," ","JQ");
	
	// Remove newlines
	this->replaceAll(in,"\n","");
	this->replaceAll(in,"\r","");
	string crypted;

	// Add padding to complete the spacing
	if (in.length() % SPACING != 0) {
		int extra = SPACING - in.length() % SPACING;
		for (int i = 0; i < extra; i++)
		{
			if ((extra - i) > 1) {
				in.append(1,'J');
				i++;
				in.append(1,'Q');
			} else {
				in.append(1,'X');
			}
		}
	}

	// Crypted modulo sum(26) from in + otp
	for (unsigned int i = 0; i<in.length(); i++)
		if (in[i] <= 0x5A && in[i] >= 0x41)
			crypted.append(1,(char)(((in[i] + out[i] + 1) % 26) + 0x41));
		else
			crypted.append(1,(char)((('X' + out[i] + 1) % 26) + 0x41));

	return crypted;
}

/*!
 * @brief Decrypt a text (crypted) string
 * @param crypted Original (crypted) string
 * @param out The ciphered text to sum(26)
 * @return The decrypted string
 *
 * This function also replaces all "JQ" ocurrences from the decrypted text to spaces
 */ 
string Crypto::decrypt(string crypted, string out)
{
	// To upper
	transform(crypted.begin(), crypted.end(), crypted.begin(), ::toupper);

	// Decrypted modulo sum(26) from in - otp
	string decrypted;
	for (unsigned int i = 0; i<crypted.length(); i++)
		decrypted.append(1,(char)(((crypted[i] - out[i] - 1 + 26) % 26) + 0x41));

	// Replace "JQ" to spaces
	this->replaceAll(decrypted, "JQ", " ");

	return decrypted;
}
