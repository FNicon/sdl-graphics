#include <iostream>

#include "World.h"
#include "SDLDisplay.h"
#include "Polygon.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"
#include "Viewport.h"

using namespace std;

int main()
{
	World world(800, 600, 100, 100, 150, 150); // create World
	SDLDisplay sdl(600, 400); // create SDL
	Viewport viewport(300, 200, 0xff0000, 0, 3); // create Viewport

	world.display = &sdl; // set World's display to SDL
	world.viewport = &viewport; // set World's viewport to Viewport

	cout << endl << "Press CTRL + C to quit." << endl;

	Polygon polygon1(0x9c6fba, 0, 2, 0, 0, 3);
	Polygon polygon2(0x83cb69, 0, 2, 0, 0, 4);

	vector<ITransform*> v1;
	vector<ITransform*> v2;

	polygon1.add(250,150);
	polygon1.add(350,150);
	polygon1.add(350,250);
	polygon1.add(250,250);
	polygon1.setCenter();
	
	polygon2.add(250,150);
	polygon2.add(350,150);
	polygon2.add(350,250);
	polygon2.add(250,250);
	polygon2.setCenter();
	
	Translate translate1;
	Scale scale1;
	Rotate rotate1, rotate2;

	translate1.set(-6.0, 0.0, 20);
	translate1.set(0.0, 6.0, 20);
	translate1.set(6.0, 0.0, 20);
	translate1.set(0.0, -6.0, 20);
	rotate2.set(8.0, 80);
	
	rotate1.set(5.0, 60);
	scale1.set(1.1, 30);
	scale1.set(0.9, 30);

	v2.push_back(&translate1);
	v1.push_back(&rotate1);
	v1.push_back(&scale1);
	v2.push_back(&rotate2);

	world.addPolygon(&polygon1, &v1);
	world.addPolygon(&polygon2, &v2);

	world.render(10);

	return 0;
}