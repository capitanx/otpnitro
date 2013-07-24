#include <algorithm>

#include "crypto.h"
#include "otpnitro.h"

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

string Crypto::encrypt(string in, string out)
{
	// To upper :-)
	transform(in.begin(), in.end(), in.begin(), ::toupper);

	// Replace spaces to XX char
	this->replaceAll(in," ","XX");
	string crypted;

	// Add padding to complete the spacing
	if (in.length() % SPACING != 0) {
		int extra = SPACING - in.length() % SPACING;
		for (int i = 0; i < extra; i++)
			in.append(1,'X');
	}

	// Crypted modulo sum(26) from in + otp
	for (unsigned int i = 0; i<in.length(); i++)
		crypted.append(1,(char)(((in[i] + out[i] + 1) % 26) + 0x41));

	return crypted;
}

string Crypto::decrypt(string crypted, string out)
{
	// To upper
	transform(crypted.begin(), crypted.end(), crypted.begin(), ::toupper);

	// Decrypted modulo sum(26) from in - otp
	string decrypted;
	for (unsigned int i = 0; i<crypted.length(); i++)
		decrypted.append(1,(char)(((crypted[i] - out[i] - 1 + 26) % 26) + 0x41));

	// Replace "XX" to spaces
	this->replaceAll(decrypted, "XX", " ");

	return decrypted;
}
