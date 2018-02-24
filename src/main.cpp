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
	World world(800, 600, 100, 100); // create World
	
	SDLDisplay display(600, 400); // create SDL
	world.display = &display; // set World's display to SDL

	Viewport viewport(250, 250, 0xff0000, 0, 1); // create Viewport
	viewport.add(1,1); // viewport upperleftmost location in SDL
	world.viewport = &viewport; // set World's viewport to Viewport

	cout << endl << "Press CTRL + C to quit." << endl;

	// Create Polygon
	Polygon polygon1(0x9c6fba, 0, 1, 0x9c6fba, 0, 3);
	Polygon polygon2(0x83cb69, 0, 1, 0x83cb69, 0, 4);

	// Create vector of Transformations for each Polygon
	vector<ITransform*> v1;
	vector<ITransform*> v2;

	// Add Points to Polygon
	polygon1.add(160,160);
	polygon1.add(220,160);
	polygon1.add(250,212);
	polygon1.add(220,263);
	polygon1.add(160,263);
	polygon1.add(130,212);
	polygon1.setCenter(); // set Polygon's center point (for floodfill, self-scaling and self-rotate)
	
	polygon2.add(190,190);
	polygon2.add(250,190);
	polygon2.add(280,242);
	polygon2.add(250,297);
	polygon2.add(190,297);
	polygon2.add(160,242);
	polygon2.setCenter();
	
	// Create Transformation object
	Rotate rotate1, rotate2;

	// Add Transformation rules
	rotate1.set(10.0, 0);
	rotate2.set(12.0, 0);

	// Add Transformation object to vector
	v1.push_back(&rotate1);
	v2.push_back(&rotate2);

	// Add Polygon and its vector of Transformation to World
	world.addPolygon(&polygon1, &v1);
	world.addPolygon(&polygon2, &v2);

	// Render World at 60 fps
	world.render(60);

	/*
	cout << "Press any key to continue.." << endl;

	string s;
	getline(cin,s);
	*/

	return 0;
}