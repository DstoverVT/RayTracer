#include "RayTracer.hpp"
#include "Sphere.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using std::rand;
using std::srand;

/**
* Create RayTrace scenes using RayTracer constructor or setter methods
* Create shapes (spheres only) using Sphere constructor
* add shape to RayTracer to addShape method
* render scene using renderScene method
* use saveSceneToPNG(filename) to save scene as PNG to output file, relative directory: src/out/build/x64-Debug/
*/
// Think of everything on a 3D coordinate system (x = front/back, y = vertical, z = horizontal, where Vector(x, y, z))

int main() {
	RayTracer r1;

	// Generate random shapes and light location
	// Random seed
	srand(time(0));
	int randLightX = rand() % 10;	// 0 - 9
	int randLightY = rand() % 21 - 10;	// -10 - 10
	int randLightZ = rand() % 11 - 5;	// -5 - 5
	r1.changeLightLocation(Vector(randLightX, randLightY, randLightZ));

	for (int i = 0; i < 10; i++) {
		int randRadius = rand() % 3 + 1;	// 1 - 3
		int randX = rand() % 21 - 10;	// -10 - 10	
		int randY = rand() % 21 - 10;
		int randZ = rand() % 21 - 10;	
		unsigned char randRed = rand() % 205 + 50;	// 50 - 254
		unsigned char randGreen = rand() % 205 + 50;
		unsigned char randBlue = rand() % 205 + 50;	
		Sphere s(randRadius, Vector(randX, randY, randZ), Pixel{ randRed, randGreen, randBlue }, 0.2);
		r1.addShape(s);
	}

	r1.renderScene();
	r1.saveSceneToPNG("Renders/Main/raytracing_scene_random10.png");
}