#include <iostream>

#include "World.h"
#include "SDLDisplay.h"
#include "Polygon.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"
#include "Viewport.h"

using namespace std;

int main(int argc, char** argv)
{
	string arg;

	if(argc == 1) arg = "--show-all";
	else arg = argv[1];

	World world(2000, 3500, 700, 500, 0x000000); // create World
	
	SDLDisplay display(700, 500); // create SDL
	world.display = &display; // set World's display to SDL

	Viewport viewport(698, 498, 0xffff00, 0, 1, 0x000000); // create Viewport
	world.viewport = &viewport; // set World's viewport to Viewport

	viewport.add(1,1); // viewport upperleftmost location in SDL
	viewport.setCenter();

	//cout << endl << "Press CTRL + C to quit." << endl;

	// Create shape
	Polygon road(0xdddddd, 0, 1, 0xdddddd, 0, 0);
	Polygon cadl(0x9c6fba, 0, 1, 0x9c6fba, 0, 1);
	Polygon boundaryLabtek(0x000000, 0, 1, 0x000000, 0, 2);
	Polygon boundaryLabtek2(0x000000, 0, 1, 0x000000, 0, 3);
	Polygon pau(0x9c6fba, 0, 1, 0x9c6fba, 0, 4);
	Polygon perpus(0x9c6fba, 0, 1, 0x9c6fba, 0, 5);
	Polygon cas(0x9c6fba, 0, 1, 0x9c6fba, 0, 6);
	Polygon labtekX(0x9c6fba, 0, 1, 0x9c6fba, 0, 7);
	Polygon oktagon(0x9c6fba, 0, 1, 0x9c6fba, 0, 8);
	Polygon comlabs(0x9c6fba, 0, 1, 0x9c6fba, 0, 9);
	Polygon labtekI(0x9c6fba, 0, 1, 0x9c6fba, 0, 10);
	Polygon tvst(0x9c6fba, 0, 1, 0x9c6fba, 0, 11);
	Polygon pln(0x9c6fba, 0, 1, 0x9c6fba, 0, 12);
	Polygon labtekV(0x9c6fba, 0, 1, 0x9c6fba, 0, 13);
	Polygon labtekVI(0x9c6fba, 0, 1, 0x9c6fba, 0, 14);
	Polygon labtekVII(0x9c6fba, 0, 1, 0x9c6fba, 0, 15);
	Polygon labtekVIII(0x9c6fba, 0, 1, 0x9c6fba, 0, 16);
	Polygon labtekXI(0x9c6fba, 0, 1, 0x9c6fba, 0, 17);
	Polygon plazaWidya(0x9c6fba, 0, 1, 0x9c6fba, 0, 18);
	Circle intel(337, 300, 55, 0x0000ff, 0, 0x0000ff, 0, 19);

	//Polygon polygon1(0x9c6fba, 0, 1, 0x9c6fba, 0, 3);
	//Polygon polygon2(0x83cb69, 0, 1, 0x83cb69, 0, 4);

	// Create vector of Transformations for each shape
	vector<ITransform*> v1;
	vector<ITransform*> v2;

	// Create vector of Transformations for Viewport
	//vector<ITransform*> v3;

	// Add Points to Polygon

	cadl.add(100,10);
	cadl.add(200,10);
	cadl.add(200,60);
	cadl.add(100,60);
	cadl.setCenter();

	pau.add(200,0);
	pau.add(250,0);
	pau.add(250,5);
	pau.add(270,5);
	pau.add(270,10);
	pau.add(280,10);
	pau.add(280,60);
	pau.add(220,60);
	pau.add(220,10);
	pau.add(200,10);
	pau.setCenter();

	perpus.add(330,0);
	perpus.add(430,0);
	perpus.add(430,50);
	perpus.add(330,50);
	perpus.setCenter();

	cas.add(450,0);
	cas.add(550,0);
	cas.add(550,50);
	cas.add(450,50);
	cas.setCenter();

	labtekX.add(0,70);
	labtekX.add(120,70);
	labtekX.add(120,120);
	labtekX.add(0,120);
	labtekX.setCenter();

	labtekXI.add(0,150);
	labtekXI.add(120,150);
	labtekXI.add(120,200);
	labtekXI.add(0,200);
	labtekXI.setCenter();

	oktagon.add(195,70);
	oktagon.add(245,70);
	oktagon.add(270,85);
	oktagon.add(270,105);
	oktagon.add(245,120);
	oktagon.add(195,120);
	oktagon.add(170,105);
	oktagon.add(170,85);
	oktagon.setCenter();

	comlabs.add(330,70);
	comlabs.add(430,70);
	comlabs.add(430,120);
	comlabs.add(330,120);
	comlabs.setCenter();

	labtekI.add(450,70);
	labtekI.add(550,70);
	labtekI.add(550,200);
	labtekI.add(450,200);
	labtekI.setCenter();

	tvst.add(195,150);
	tvst.add(245,150);
	tvst.add(245,165);
	tvst.add(270,165);
	tvst.add(270,185);
	tvst.add(245,185);
	tvst.add(245,200);
	tvst.add(195,200);
	tvst.add(195,185);
	tvst.add(170,185);
	tvst.add(170,165);
	tvst.add(195,165);
	tvst.setCenter();

	pln.add(330,150);
	pln.add(430,150);
	pln.add(430,200);
	pln.add(330,200);
	pln.setCenter();

	labtekVI.add(80,280);
	labtekVI.add(280,280);
	labtekVI.add(280,330);
	labtekVI.add(80,330);
	labtekVI.setCenter();

	labtekV.add(80,345);
	labtekV.add(280,345);
	labtekV.add(280,395);
	labtekV.add(80,395);
	labtekV.setCenter();

	labtekVII.add(520,280);
	labtekVII.add(320,280);
	labtekVII.add(320,330);
	labtekVII.add(520,330);
	labtekVII.setCenter();

	labtekVIII.add(520,345);
	labtekVIII.add(320,345);
	labtekVIII.add(320,395);
	labtekVIII.add(520,395);
	labtekVIII.setCenter();

	plazaWidya.add(280,210);
	plazaWidya.add(320,210);
	plazaWidya.add(340,225);
	plazaWidya.add(320,240);
	plazaWidya.add(280,240);
	plazaWidya.add(260,225);
	plazaWidya.setCenter();

	road.add(290,500);
	road.add(290,420);
	road.add(1,420);
	road.add(1,400);
	road.add(30,400);
	road.add(30,270);
	road.add(1,270);
	road.add(1,250);
	road.add(580,250);
	road.add(580,140);
	road.add(320,140);
	road.add(320,210);
	road.add(280,210);
	road.add(280,140);
	road.add(150,140);
	road.add(150,250);
	road.add(130,250);
	road.add(130,140);
	road.add(1,140);
	road.add(1,130);
	road.add(130,130);
	road.add(130,60);
	road.add(150,60);
	road.add(150,130);
	road.add(280,130);
	road.add(280,50);
	road.add(320,50);
	road.add(320,130);
	road.add(580,130);
	road.add(580,1);
	road.add(600,1);
	road.add(600,420);
	road.add(310,420);
	road.add(310,500);
	road.setCenter();

	boundaryLabtek.add(50,270);
	boundaryLabtek.add(50,400);
	boundaryLabtek.add(280,400);
	boundaryLabtek.add(280,270);
	boundaryLabtek.setCenter();

	boundaryLabtek2.add(320,270);
	boundaryLabtek2.add(320,400);
	boundaryLabtek2.add(580,400);
	boundaryLabtek2.add(580,270);
	boundaryLabtek2.setCenter();

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
	Scale scale1, scale2;
	scale1.set(350, 250, 1.0, 10);
	scale1.set(350, 250, 1.5, 1);
	scale2.set(1.0, 10);
	scale2.set(1.5, 1);

	//Rotate rotate1, rotate2;

	// Add Transformation rules
	//translate.set(5, 0, 30);
	//translate.set(0, 5, 30);
	//translate.set(0, -5, 30);

	//rotate1.set(10.0, 0);
	//rotate2.set(12.0, 0);

	// Add Transformation object to vector
	v1.push_back(&scale1);
	v2.push_back(&scale2);
	//v2.push_back(&rotate2);

	//v3.push_back(&translate);

	// Add shape and its vector of Transformation to World
	
	if(arg == "--show-all" || arg == "--show-road") world.addShape(&road, &v1);

	if(arg == "--show-all" || arg == "--show-building")
	{
		world.addShape(&cadl, &v1);
		world.addShape(&boundaryLabtek, &v1);
		world.addShape(&boundaryLabtek2, &v1);
		world.addShape(&pau, &v1);
		world.addShape(&perpus, &v1);
		world.addShape(&cas, &v1);
		world.addShape(&labtekX, &v1);
		world.addShape(&labtekXI, &v1);
		world.addShape(&oktagon, &v1);
		world.addShape(&comlabs, &v1);
		world.addShape(&labtekI, &v1);
		world.addShape(&tvst, &v1);
		world.addShape(&pln, &v1);
		world.addShape(&labtekV, &v1);
		world.addShape(&labtekVI, &v1);
		world.addShape(&labtekVII, &v1);
		world.addShape(&labtekVIII, &v1);
		world.addShape(&plazaWidya, &v1);
		world.addShape(&intel,&v2);
	}

	//world.addShape(&polygon2, &v2);

	// Add viewport Transformation to World
	// world.addViewportTrans(&v3);

	// Continuous animation
	// world.resetFPSCount(120, -1);

	// Render World at 60 fps
	world.render(10);

	/*
	cout << "Press any key to continue.." << endl;

	string s;
	getline(cin,s);
	*/

	return 0;
}