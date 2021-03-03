#ifndef _RAYTRACER_HPP_
#define _RAYTRACER_HPP_

#include <iostream>
#include <vector>

#include "Sphere.hpp"
#include "Vector.hpp"


/**
 * A simple ray tracer in C++: currently only supports one object in scene
 */
class RayTracer
{
public:
	/**
	 * Default constructor. renders a scene with default sphere, light source at (0,10,0), and camera at (5,0,0) with
	 * target at (0,0,0), and black background
	 */
	RayTracer();

	/**
	 * @param light - position (Vector w/r/t (0,0,0)) of light source
	 * @param camera - position (Vector w/r/t (0,0,0)) of camera source
	 * @param target - position (Vector w/r/t (0,0,0)) of target (where camera is looking)
	 * @param shape - the shape to render in the scene
	 */
	RayTracer(Vector light, Vector camera, Vector target, std::vector<Sphere> shapes, int width, int height, int hx, int hy, Pixel bgColor);

	/**
	 * Create png of rendered scene with name of the file given by filename (use scene.png if filename is empty)
	 * @return whether was scene was successfully written to disk as .png
	 */
	bool saveSceneToPNG(std::string filename); //write image of scene as <filename>.png

	/**
	 * Create png of rendered scene with name of file `scene.png'
	 * @return whether was scene was successfully written to disk as .png
	 */
	bool saveSceneToPNG(); //write image of scene as `scene.png'

	/**
	 * Color each pixel in scene
	 */
	void renderScene();

	/**
	 * Setter methods to change scene parameters - call renderScene to see updates
	 */
	void changeLightLocation(const Vector& newLight);
	void changeCameraLocation(const Vector& newCamera);
	void changeTargetLocation(const Vector& newTarget);

	/**
	 * Add a shape to the scene - call renderScene to see updates
	 */
	void addShape(Sphere newShape);


private:
	//width and height (in pixels) of the image (changeable)
	const int WIDTH;
	const int HEIGHT;
	//width and height (in coordinate system) of our veiwport (changeable)
	// WARNING: HX/Y ratio should match the WIDTH/HEIGHT ratio
	const int HX;
	const int HY;
	Pixel backgroundColor;

	// Think of everything on a 3D coordinate system (x = front/back, y = vertical, z = horizontal)
	Vector light;	// Location of light source
	Vector camera;	// Location of camera
	Vector target;	// Location camera is looking towards (target - camera = direction of camera)
	std::vector<Sphere> shapes;	// Multiple shapes
	std::vector<Vector> view; //normalized vectors leaving our camera

	// One-dimensional vector being used to represented two-dimensional pixels on the view (more efficient)
	std::vector<Pixel> pixels; //RGBA values for each pixel in image
	bool VALID_SCENE; //true if scene is renderable

	/**
	 * Establish normalized vector from camera/eye to image plane, used as main ray tracing rays from camera
	 * CHANGES: view vector member data
	 */
	void generateView();

	/**
	* Ensure that camera position and direction are valid (set to VALID_SCENE)
	* CHANGES: VALID_SCENE member data
	*/
	void checkSceneValidity();

	/**
	* Algorithm to color each pixel corresponding of the image, shading each shape corresponding to the light source location
	* CHANGES: pixels vector member data
	*/
	void colorPixels();

	/**
	* lodepng library requires pixel RGBA values to be in a vector where each pixel RGBA corresponds to 4 elements in vector instead of Pixel struct
	*/
	std::vector<unsigned char> createLoadablePixelVector();

};

#endif
