#include <unistd.h>

#include "page.h"
#include "crypto.h"
#include "text.h"
#include "otpnitro.h"

int main(int argc, char **argv)
{
	// Header
	cout << "OTP Nitro " << VERSION << endl << "-------------" << endl;
	if (argc == 1)
	cout << "ERROR: You must enter a valid argument, see -h" << endl << endl;

	// Arguments
	signed char c;
	bool gen = false, enc = false, dec = false, brn = false, lst = false;
	string send, id, msg, file;
	int pnum = 0;

	while ( (c = getopt(argc, argv, "h?gledbs:r:m:p:f:")) != -1) {
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
		case 'l':
			// List available pages
			lst = true;
		break;
		case 's':
			// sender
			send = optarg;
		break;
		case 'r':
			// book - recv id
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
				"\t-l	List  pages	\n"	\
				"\t-b	Burn  page	[-r -p]\n"	\
				"\t-e	Encrypt		[-s -r -m]\n"		\
				"\t-d	Decrypt		[-s -r -m -p] [-f]\n"	\
				"\n"				\
				"Opts:\n"			\
				"\t-s	<sender>\n"		\
				"\t-r	<code book>\n"		\
				"\t-p	<page num>\n"		\
				"\t-m	<\"message text\">\n"	\
				"\t-f	<\"crypted format\">\n\n");
		exit(1);
		break;
	    }
	}

	if (gen) {
		Page   * page   = new Page;

		// Generate OTP for ID
		cout << "[I] Generating OTP: " << id;
		page->generate(id);
		cout << ". OK" << endl << endl;

		delete page;
		exit(0);
	}

	if (enc) {
		cout << "[I] Encrypted msg:" << endl;

		Page   * page   = new Page;
		Crypto * crypto = new Crypto;

		// Get a usable page
		pnum = page->next(id);
		if (pnum == -1) {
			cout << "[E] Not found pages in book: " << id << endl;
			cout << "[I] You can generate them with: otpnitro -g -r " << id << endl << endl;
			exit(1);
		}

		// Read page X from Book (RECV ID)
		string out = page->read(pnum,id);

		// Crypto
		string encrypted = crypto->encrypt(msg,out);

		// Print page
		Text * txt = new Text;
		txt->create(pnum,id,send,encrypted);
		cout << txt->print(1);

		delete txt;
		delete page;
		delete crypto;
		exit(0);
	}

	if (dec) {
		cout << "[I] Decrypted msg:" << endl;

		Page   * page   = new Page;
		Crypto * crypto = new Crypto;
		Text   * txt    = new Text;

		if (file.length() > 0)
			txt->parse(file);
		else
			txt->create(pnum,id,send,msg);

		// Read page X from Book (RECV ID)
		string out = page->read(txt->page,txt->book);

		if (out.length() == 0) {
			cout << "[E] The page " << pnum << " in the book " << id << " dont exist." << endl;
			cout << "[I] You can check if you recieved the " << id << " book, or if it was burned." << endl;
			cout << "[I] Check: otpnitro -l" << endl << endl;
			exit(1);
		}

		// Crypto
		crypto->replaceAll(txt->msg," ","");
		txt->msg = crypto->decrypt(txt->msg,out);

		// Print MSG
		cout << txt->print(0);

		delete txt;
		delete page;
		delete crypto;
	   	exit(0);
	}

	if (brn) {
		cout << "[I] Burn page " << pnum;

		Page   * page   = new Page;
		if (page->burn(pnum,id))
		cout << ". OK"   << endl << endl;
		else
		cout << ". FAIL" << endl << endl;
		delete page;
		exit(0);
	}

	if (lst) {
		Page   * page   = new Page;

		cout << "[I] Available books:" << endl;
		cout << page->list();
		cout << endl;

		delete page;
		exit(0);
	}

	return(0);
}
