#include <iostream>
#include <unistd.h>

#include "text.h"
#include "otpnitro.h"
#include "base24.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc == 1)
		cout << "ERROR: You must enter a valid argument, see -h" << endl << endl;

	// Arguments
	signed char c;
	bool enc = false, dec = false;

	while ( (c = getopt(argc, argv, "h?e:d:")) != -1) {
	    switch (c) {
		case 'e':
			// Encode
			enc = true;
		break;
		case 'd':
			// Decode
			dec = true;
		break;
		case 'h':
		case '?':
			cout <<	endl << "Modes:" << endl;
			cout <<	"\t-e	Encode\t[Message]" << endl;
			cout << "\t-d	Decode\t[Message]" << endl << endl;
			exit(1);
		break;
	    }
	}

	if (enc) {

		if (!argv[2])
			exit(1);

		Text * txt = new Text;

		string msgEnc = txt->encodeB26((unsigned char *)argv[2],strlen(argv[2]));
		cout << msgEnc << endl;

		delete txt;
		exit(0);
	}

	if (dec) {

		if (!argv[2])
			exit(1);

		Text * txt = new Text;

		int decLen = strlen(argv[2]) / 2;
		unsigned char * msgDec = new unsigned char[decLen];

		txt->decodeB26( msgDec, argv[2] );

		cout << msgDec << endl;

		delete txt;
	   	exit(0);
	}

	return(0);
}
