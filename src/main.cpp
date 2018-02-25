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
	World world(900, 1200, 100, 100, 0x000000); // create World
	
	SDLDisplay display(700, 500); // create SDL
	world.display = &display; // set World's display to SDL

	Viewport viewport(250, 250, 0xffff00, 0, 1, 0x000000); // create Viewport
	world.viewport = &viewport; // set World's viewport to Viewport

	viewport.add(1,1); // viewport upperleftmost location in SDL
	viewport.setCenter();

	//cout << endl << "Press CTRL + C to quit." << endl;

	// Create Polygon
	Polygon cadl(0x9c6fba, 0, 1, 0x9c6fba, 0, 1);
	Polygon pau(0x9c6fba, 0, 1, 0x9c6fba, 0, 2);
	Polygon perpus(0x9c6fba, 0, 1, 0x9c6fba, 0, 3);
	Polygon cas(0x9c6fba, 0, 1, 0x9c6fba, 0, 4);
	Polygon labtekX(0x9c6fba, 0, 1, 0x9c6fba, 0, 5);
	Polygon oktagon(0x9c6fba, 0, 1, 0x9c6fba, 0, 6);
	Polygon comlabs(0x9c6fba, 0, 1, 0x9c6fba, 0, 7);
	Polygon labtekI(0x9c6fba, 0, 1, 0x9c6fba, 0, 8);
	Polygon tvst(0x9c6fba, 0, 1, 0x9c6fba, 0, 9);
	Polygon pln(0x9c6fba, 0, 1, 0x9c6fba, 0, 10);
	Polygon labtekV(0x9c6fba, 0, 1, 0x9c6fba, 0, 11);
	Polygon labtekVI(0x9c6fba, 0, 1, 0x9c6fba, 0, 12);
	Polygon labtekVII(0x9c6fba, 0, 1, 0x9c6fba, 0, 13);
	Polygon labtekVIII(0x9c6fba, 0, 1, 0x9c6fba, 0, 14);
	Polygon plazaWidya(0x9c6fba, 0, 1, 0x9c6fba, 0, 15);


	//Polygon polygon1(0x9c6fba, 0, 1, 0x9c6fba, 0, 3);
	//Polygon polygon2(0x83cb69, 0, 1, 0x83cb69, 0, 4);

	// Create vector of Transformations for each Polygon
	//vector<ITransform*> v1;
	//vector<ITransform*> v2;

	// Create vector of Transformations for Viewport
	//vector<ITransform*> v3;

	// Add Points to Polygon
	cadl.add(100,20);
	cadl.add(200,20);
	cadl.add(200,120);
	cadl.add(100,120);
	cadl.setCenter();

	pau.add(200,0);
	pau.add(250,0);
	pau.add(250,10);
	pau.add(270,10);
	pau.add(270,20);
	pau.add(280,20);
	pau.add(280,120);
	pau.add(220,120);
	pau.add(220,20);
	pau.add(200,20);
	pau.setCenter();

	perpus.add(350,0);
	perpus.add(450,0);
	perpus.add (450,100);
	perpus.add (350,100);
	perpus.setCenter();

	cas.add(470,0);
	cas.add (570,0);
	cas.add (570,100);
	cas.add (470,100);
	cas.setCenter();

	labtekX.add(0,140);
	labtekX.add (120,140);
	labtekX.add (120,240);
	labtekX.add (0,240);
	labtekX.setCenter();

	oktagon.add(180,140);
	oktagon.add (280,140);
	oktagon.add (280,240);
	oktagon.add (180,240);
	oktagon.setCenter();

	comlabs.add(350,140);
	comlabs.add (450,140);
	comlabs.add (450,240);
	comlabs.add (350,240);
	comlabs.setCenter();

	labtekI.add(470,140);
	labtekI.add (570,140);
	labtekI.add (570,340);
	labtekI.add (470,340);
	labtekI.setCenter();

	tvst.add(180,300);
	tvst.add(280,300);
	tvst.add(280,400);
	tvst.add(180,400);
	tvst.setCenter();

	pln.add(350,300);
	pln.add(450,300);
	pln.add(450,400);
	pln.add(350,400);
	pln.setCenter();

	labtekVI.add(130,500);
	labtekVI.add(280,500);
	labtekVI.add(280,600);
	labtekVI.add(130,600);
	labtekVI.setCenter();

	labtekV.add(130,650);
	labtekV.add(280,650);
	labtekV.add(280,750);
	labtekV.add(130,750);
	labtekV.setCenter();

	labtekVII.add(470,500);
	labtekVII.add(320,500);
	labtekVII.add(320,600);
	labtekVII.add(470,600);
	labtekVII.setCenter();

	labtekVIII.add(470,650);
	labtekVIII.add(320,650);
	labtekVIII.add(320,750);
	labtekVIII.add(470,750);
	labtekVIII.setCenter();

	plazaWidya.add(270,420);
	plazaWidya.add(330,420);
	plazaWidya.add(330,480);
	plazaWidya.add(270,480);
	plazaWidya.setCenter();

	/*polygon1.add(160,160);
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
	polygon2.setCenter();*/
	
	// Create Transformation object
	//Translate translate;
	//Scale scale;
	//Rotate rotate1, rotate2;

	// Add Transformation rules
	//translate.set(5, 0, 30);
	//translate.set(0, 5, 30);
	//translate.set(0, -5, 30);

	//rotate1.set(10.0, 0);
	//rotate2.set(12.0, 0);

	// Add Transformation object to vector
	//v1.push_back(&rotate1);
	//v2.push_back(&rotate2);

	//v3.push_back(&translate);

	// Add Polygon and its vector of Transformation to World
	world.addPolygon(&cadl, NULL);
	world.addPolygon(&pau, NULL);
	world.addPolygon(&perpus, NULL);
	world.addPolygon(&cas, NULL);
	world.addPolygon(&labtekX, NULL);
	world.addPolygon(&oktagon, NULL);
	world.addPolygon(&comlabs, NULL);
	world.addPolygon(&labtekI, NULL);
	world.addPolygon(&tvst, NULL);
	world.addPolygon(&pln, NULL);
	world.addPolygon(&labtekV, NULL);
	world.addPolygon(&labtekVI, NULL);
	world.addPolygon(&labtekVII, NULL);
	world.addPolygon(&labtekVIII, NULL);
	world.addPolygon(&plazaWidya, NULL);
	//world.addPolygon(&polygon2, &v2);

	// Add viewport Transformation to World
	// world.addViewportTrans(&v3);

	// Continuous animation
	// world.resetFPSCount(120, -1);

	// Render World at 60 fps
	world.render(60);

	/*
	cout << "Press any key to continue.." << endl;

	string s;
	getline(cin,s);
	*/

	return 0;
}