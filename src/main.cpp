#include <iostream>

#include "World.h"
#include "SDLDisplay.h"
#include "Polygon.h"

using namespace std;

int main()
{
	World world(800, 600, 100, 100); // create World
	SDLDisplay sdl(600, 400); // create SDL

	world.display = &sdl; // set World's display to SDL
	
	/*
	// World setter/getter test

	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			if(i == j) world.set(i, j, Pixel(0x9c3f88, 0, 2));
			else if(i+j == 99) world.set(i, j, Pixel(0x3fde47, 0, -1));
		}
	}
	

	// Draw line test
	
	Line line1(0, 0, 100, 100, 0xff0000, 0, 1);
	Line line2(50, 0, 50, 100, 0x00ff00, 0, 8);
	Line line3(100, 0, 0, 100, 0x0000ff, 0, 4);
	Line line4(100, 50, 0, 50, 0xffff00, 0, 5);
	line1.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	line2.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	line3.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	line4.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	
	Line line5(100, 100, 0, 0, 0xff00ff, 0, 3);
	Line line6(50, 100, 50, 0, 0x00ffff, 0, 1);
	Line line7(0, 100, 100, 0, 0xffffff, 0, 2);
	Line line8(0, 50, 100, 50, 0x3fde47, 0, 7);
	line5.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	line6.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	line7.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	line8.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	

	// Draw polygon test
	
	Polygon polygon1(0x9c6fba, 0, 1, 0, 0);

	polygon1.add(0,0);
	polygon1.add(100,0);
	polygon1.add(100,100);
	polygon1.add(0,100);

	polygon1.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	
	Polygon polygon2(0x9c6fba, 0, 1, 0, 0);

	polygon2.add(-1,-1);
	polygon2.add(99,-1);
	polygon2.add(99,99);
	polygon2.add(-1,99);

	polygon2.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);
	*/
	Polygon polygon3(0x9c6fba, 0, 1, 0, 0);

	polygon3.add(50,50);
	polygon3.add(120,75);
	polygon3.add(200,160);
	polygon3.add(168,299);
	polygon3.add(45,201);
	polygon3.add(20,80);

	polygon3.draw(world.buffer, world.SDL_origin_row, world.SDL_origin_col);

	world.render();

	cout << endl << "Press any key to continue..." << endl;
	
	string dummy;
	getline(cin, dummy);

	return 0;
}