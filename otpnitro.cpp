#include <unistd.h>

#include "page.h"
#include "crypto.h"
#include "text.h"
#include "otpnitro.h"


int main(int argc, char **argv) {

    	// Header
    	cout << "OTP Nitro " << VERSION << endl << "-------------" << endl;
	if (argc == 1)
		cout << "ERROR: You must enter a valid argument, see -h" << endl << endl;

	// Arguments
	char c;
	bool gen = false, enc = false, dec = false, brn = false;
	string send, id, msg, file;
	int pnum = 0;

	while ( (c = getopt(argc, argv, "h?gedbs:r:m:p:f:")) != -1) {
	    switch (c) {
		case 'g':
			// Generate OTP
			gen = true;
		break;
		case 'e':
			// Encrypt
			enc = true;
		break;
		case 'd':
			// Decrypt
			dec = true;
		break;
		case 'b':
			// Burn page
			brn = true;
		break;
		case 's':
			// sender
			send = optarg;
		break;
		case 'r':
			// recv id
			id   = optarg;
		break;
		case 'm':
			// Message
			msg  = optarg;
		break;
		case 'p':
			// Page num
			if(optarg)
				pnum = atoi(optarg);
		break;
		case 'f':
			// File to parse
			file = optarg;
		break;
		case 'h':
		case '?':
			printf("\n"
				"Modes:\n"			\
				"\t-g	Write pages	[-r]\n"	\
				"\t-b	Burn  page	[-r -p]\n"	\
				"\t-e	Encrypt		[-s -r -m]\n"		\
				"\t-d	Decrypt		[-s -r -m -p] [-f]\n"	\
				"\n"				\
				"Opts:\n"			\
				"\t-s	<sender>\n"		\
				"\t-r	<recv id>\n"		\
				"\t-p	<page num>\n"		\
				"\t-m	<\"message text\">\n"	\
				"\t-f	<crypted file>\n\n");
		exit(1);
		break;
	    }
	}

	if (gen) {
	    	Page   * page   = new Page;

		// Generate OTP for ID
		cout << "[I] Generating OTP: " << id;
		page->generate("TST");
		cout << ". OK" << endl;

		delete page;
		exit(0);
	}

	if (enc) {
	    	cout << "[I] Encrypted msg:" << endl << endl;

	    	Page   * page   = new Page;
		Crypto * crypto = new Crypto;

		// Get a usable page
		pnum = page->next(id);

		// Read page X from RECV ID
		string out = page->read(pnum,id);

		// Crypto
		string encrypted = crypto->encrypt(msg,out);

		// Print page
		Text * txt = new Text;
		txt->create(pnum,id,send,encrypted);
		txt->print();

		delete txt;
		delete page;
		delete crypto;
	    	exit(0);
	}

	if (dec) {
	    	cout << "[I] Decrypt msg" << endl;

	    	Page   * page   = new Page;
		Crypto * crypto = new Crypto;

		// Read page X from RECV ID
		string out = page->read(pnum,id);

		// Crypto
		crypto->replaceAll(msg," ","");
		string decrypted = crypto->decrypt(msg,out);

		cout << send << " DE " << id << " " << pnum << endl;
		cout << "DECRYPTED: " << decrypted << endl;

		delete page;
		delete crypto;
	   	exit(0);
	}

	if (brn) {
	    	cout << "[I] Burn page " << pnum;

	    	Page   * page   = new Page;
	    	if (page->burn(pnum,id))
			cout << ". OK"   << endl;
		else
			cout << ". FAIL" << endl;
		delete page;
	    	exit(0);
	}

	return(0);
}
