#include <iostream>

#include "World.h"
#include "SDLDisplay.h"
#include "Pixel.h"

using namespace std;

int main()
{
	World world(800, 600, 100, 100); // create World
	SDLDisplay sdl(600, 400); // create SDL

	world.display = &sdl; // set World's display to SDL

	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			if(i == j) world.set(i, j, Pixel(0x9c3f88, 0, 2));
			else if(i+j == 99) world.set(i, j, Pixel(0x3fde47, 0, -1));
		}
	}

	world.render();

	cout << endl << "Press any key to continue..." << endl;
	
	string dummy;
	getline(cin, dummy);

	return 0;
}