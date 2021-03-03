#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include <math.h>
#include <iostream>
#include <vector>

#include "catch.hpp"
#include "RayTracer.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

using std::vector;
using std::cout;
using std::endl;

// This is just a simple example for demonstration - black screen
TEST_CASE( "Test default constructor and no shapes", "[RayTracer]" ) 
{
  RayTracer r;
  r.renderScene();
  r.saveSceneToPNG("Renders/Tests/TEST_DEFAULT.png");
}

TEST_CASE("Test default constructor and one shape", "[RayTracer]")
{
	RayTracer r;
	Sphere s;
	r.addShape(s);
	r.renderScene();
	r.saveSceneToPNG("Renders/Tests/TEST_ONEDEFAULTSHAPE.png");
}

TEST_CASE("Test default constructor and custom shapes", "[RayTracer]")
{
	RayTracer r1;
	r1.changeLightLocation(Vector(0, 10, 0));
	Sphere s1(2, Vector(0, -6, 0), Pixel{ 255, 0, 0 }, 0.1);
	Sphere s2(2, Vector(0, 0, 0), Pixel{ 0, 255, 0 }, 0.1);

	r1.addShape(s1);
	r1.addShape(s2);

	r1.renderScene();
	r1.saveSceneToPNG("Renders/Tests/TEST_CUSTOMSHAPES_3.png");
}

/*
TEST_CASE( "Test parameterized constructor", "[RayTracer]" ) {
  Vector light(-5,5,5), camera(0,0,5), target(0,0,0);

  //a large magenta sphere with lots of internal light
  std::vector<unsigned char> col = {255,0,255,255};
  Sphere sph(2, Vector(0,0,0), col, 0.5);
  
  RayTracer r(light, camera, target, sph);
  r.getScene("scene_parameterized.png");
}

/* TEST for 3x3 pixel view - commented out because I cannot change WIDTH and HEIGHT to 3x3 just for this test
TEST_CASE("Test genView method", "[RayTracer]") {
	Vector light(0, 10, 0), camera(0, 0, 5), target(0, 0, 0);
	Sphere sph;

	RayTracer r(light, camera, target, sph);

	// For HEIGHT and WIDTH of 3 pixels
	vector<Vector> correctView = {Vector(-2, 2, -1), Vector(0, 2, -1), Vector(2, 2, -1), Vector(-2, 0, -1), Vector(0, 0, -1),
										Vector(2, 0, -1), Vector(-2, -2, -1), Vector(0, -2, -1), Vector(2, -2, -1)};

	// For HEIGHT and WIDTH of 2 pixels
	//vector<Vector> correctView2 = { Vector(-2, 2, -1), Vector(2, 2, -1), Vector(-2, -2, -1), Vector(2, -2, -1) };

	for (int i = 0; i < r.getView().size(); i++) {
		cout << "RayTracer view: " << endl;
		r.getView()[i].output(cout);

		cout << "Correct: " << endl;
		correctView[i].output(cout);

		CHECK(r.getView()[i].equal(correctView[i]));
	}
	
}

TEST_CASE("Test intersect method", "[Sphere]") {
	Vector light(5, 0, 0), camera(0, 1, 0), target(0, 2, 0);

	//a large magenta sphere with lots of internal light
	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(2, Vector(0, 0, 0), col, 0.5);

	RayTracer r(light, camera, target, sph);

	// All p_ij rays should not intersect with the shape
	vector<Vector> rayView = r.getView();

	bool noneIntersect = true;
	for (int i = 0; i < rayView.size(); i++) {
		Vector result = sph.intersect(camera, rayView[i]);
		// One vector does intersect
		if (!(isinf(result.getI()) && isinf(result.getJ()) && isinf(result.getK())))
			noneIntersect = false;
	}

	REQUIRE(noneIntersect == true);
}

TEST_CASE("Test Sphere normal method", "[Sphere]") {
	
	std::vector<unsigned char> col = { 255,0,255,255 };
	Vector pos(1, 0, -1);

	Sphere sph(2, pos, col, 0.5);

	double x = 5;
	double y = 2;
	double z = -1;

	Vector testVector(x, y, z);
	Vector normalVector = sph.normal(testVector);
	
	Vector normalTest = testVector.sub(pos);
	double denominator = 1 / normalTest.norm();

	Vector normalOutput(normalTest.getI() * denominator, normalTest.getJ() * denominator, normalTest.getK() * denominator);
	
	REQUIRE(normalOutput.getI() == (x-1) * denominator);
	REQUIRE(normalOutput.getJ() == y * denominator);
	REQUIRE(normalOutput.getK() == (z+1) * denominator);
}

TEST_CASE("Test getScene method with invalid camera placement", "[Sphere]") {
	Vector light(5, 0, 0), camera(0, 1, 0), target(0, 2, 0);

	//a large magenta sphere with lots of internal light
	std::vector<unsigned char> col = { 255,0,255,255 };
	Sphere sph(2, Vector(0, 0, 0), col, 0.5);

	RayTracer r(light, camera, target, sph);

	REQUIRE(r.getScene() == false);
}
*/



