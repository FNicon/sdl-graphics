#include <iostream>

#include "SDLDisplay.h"
#include "RawPixel.h"

using namespace std;

int main()
{
	SDLDisplay display(600, 400);
	RawPixel raw;

	raw.r = 0xff;
	raw.g = 0x0;
	raw.b = 0xff;

	for(int i=0;i<10;i++)
	{
		display.set(i, i, raw);
	}

	display.render();

	cout << endl << "Press any key to continue..." << endl;
	
	string dummy;
	getline(cin, dummy);

	return 0;
}