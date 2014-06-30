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
#include <fstream>
#include "rand.h"

#define LOOPCNT 1000000

using namespace std;

int main()
{
    	int i=0;
	Rand * rnd = new Rand;
	cout << "[*] Generating 100 seeds...\t\tseeds.txt" << endl;
	ofstream fseed ("seeds.txt");
	for (i=0; i<100; i++)
		fseed   << rnd->genSeed() << endl;
	fseed.close();

	cout << "[*] Generating " << LOOPCNT << " chars...\t\tchars.txt" << endl;
	ofstream fchar ("chars.txt");
	for (i=0; i<LOOPCNT; i++)
		fchar   << rnd->getChar();
	fchar.close();

	cout << "[*] Generating " << LOOPCNT << " letters...\tletters.txt" << endl;
	ofstream fletter ("letters.txt");
	for (i=0; i<LOOPCNT; i++)
		fletter << rnd->getLetter();
	fletter.close();

	delete rnd;

	cout << endl << endl << "[I] Now you can run these tools:" << endl << "[I] $> cntchar letters.txt" << endl << "[I] $> derandom  chars.txt 1000" << endl << endl << "[I] Those tools are part of the jr-tools project:" << endl << "[I] $> git clone https://code.haibane.org/tools/jr-tools" << endl;

	
	return 0;
}
