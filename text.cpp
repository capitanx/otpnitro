#include <stdlib.h>
#include <algorithm>
#include <sstream>

#include "text.h"
#include "otpnitro.h"

/*!
 * replaceAll( str, from, to ) \n
 * @brief Replace all characters from a string
 * @param str The string pointer
 * @param from Character to be replaced
 * @param to Replace character
 */
void   Text::replaceAll(std::string& str, const std::string& from, const std::string& to)
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
 * @brief Set the Text object parameters
 * @param page Page num
 * @param book Book ID
 * @param from A sender id for identification
 * @param msg The cleartext message
 */
void Text::create(int page, string book, string from, string msg)
{
	this->page = page;
	this->from = from;
	this->book = book;
	this->msg  = msg;
}

/*!
 * @brief Print a human friendly Text object
 * @param spa Space num
 * @return sout.str()
 */
string Text::print(int spa)
{
	std::stringstream sout;

	// Print Header
	sout << this->book << " DE " << this->from << " " << this->page << " = ";

	// Add spacing and print chars
	int a = 0;
	for (unsigned int i = 0; i<this->msg.length(); i++) {
		if (a == 5 && spa == 1) {
			a=0;
			sout << " ";
		}
		sout << this->msg[i];
		a++;
	}
	sout << " = " << endl << endl;

	return sout.str();
}

/*!
 * @brief Parse and set the Text object with a formatted (headed) message
 * @param text The formatted message string
 */
void Text::parse(string text)
{
	transform(text.begin(), text.end(), text.begin(), ::toupper);

	unsigned pos1 = text.find('=');
	unsigned pos2 = text.find('=',pos1+1);
	string   head = text.substr(0,pos1-1);		// Get HEAD
	string    msg = text.substr(pos1+1,pos2-pos1-1);// Get MSG

	// Parse HEAD elements
	pos1 = head.find(' ');
	string book = head.substr(0,pos1);

	pos2 = head.find(" ",pos1+1);
	pos1 = head.find(" ",pos2+1);
	string from = head.substr(pos2+1,pos1-pos2-1);

	pos1 = head.find(" ",pos2+1);
	int page = atoi(head.substr(pos1+1).c_str());

	// Remove spaces on msg
	this->replaceAll(msg," ","");
	this->replaceAll(msg,"\r","");
	this->replaceAll(msg,"\n","");

	this->from = from;
	this->book = book;
	this->page = page;
	this->msg  = msg;
}

/*!
 * @brief Returns the text encoded in Base26
 * @param text Text to encode
 * @param len Text len
 * @return Encoded text (string)
 */
string Text::encodeB26(unsigned char * text, long len)
{
	string output;

	for(int i = 0; i<len; i++) {
		output.push_back(int(text[i] / 26) + 0x41);
		output.push_back((text[i] % 26)    + 0x41);
	}

	return output;
}

/*!
 * @brief Returns the text decoded in Base26
 * @param output Text decoded
 * @param text Encoded text
 */
void Text::decodeB26(unsigned char * output, string text)
{
	unsigned char current = 0x00;

	int a = 0;
	for(unsigned long i = 1; i<text.length(); i+=2) {
		current =  int((int(text[i-1]) - 0x41) * 26);
		current += int((text[i] - 0x41) % 26);
		output[a] = current;
		a++;
	}

	return;
}
