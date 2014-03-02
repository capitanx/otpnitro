#include <stdlib.h>
#include <algorithm>
#include <sstream>

#include "text.h"
#include "otpnitro.h"

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

void Text::create(int page, string from, string to, string msg)
{
	this->page = page;
	this->from = from;
	this->to   = to;
	this->msg  = msg;
}

string Text::print(int spa)
{
	std::stringstream sout;

	// Print Header
	sout << this->to << " DE " << this->from << " " << this->page << " = ";

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

void Text::parse(string text)
{
	transform(text.begin(), text.end(), text.begin(), ::toupper);

	unsigned pos1 = text.find('=');
	unsigned pos2 = text.find('=',pos1+1);
	string   head = text.substr(0,pos1-1);		// Get HEAD
	string    msg = text.substr(pos1+1,pos2-pos1-1);// Get MSG

	// Parse HEAD elements
	pos1 = head.find(' ');
	string to = head.substr(0,pos1);

	pos2 = head.find(" ",pos1+1);
	pos1 = head.find(" ",pos2+1);
	string from = head.substr(pos2+1,pos1-pos2-1);

	pos1 = head.find(" ",pos2+1);
	int page = atoi(head.substr(pos1+1).c_str());

	// Remove spaces on msg
	this->replaceAll(msg," ","");

	this->from = from;
	this->to   = to;
	this->page = page;
	this->msg  = msg;
}
