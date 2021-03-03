#include "RayTracer.hpp"
#include "Vector.hpp"
#include "Sphere.hpp"

#include <string>
#include <vector>
#include <math.h>
#include <lodepng.h>    // Used to create the RayTracer rendered PNG image

using std::string;
using std::vector;
using std::cout;
using std::endl;

/** Default scene parameters with light source at (0,10,0), and camera at (5,0,0) with target (direction of camera) at (0,0,0)
* And dimensions of 1024x1024 with image width/height of 5 units in coordinate system. Default background color of black
* Need to add shapes - default has no shapes
*/
RayTracer::RayTracer() : RayTracer(Vector(0, 10, 0), Vector(5, 0, 0), Vector(0, 0, 0), vector<Sphere>(), 1024, 1024, 5, 5, Pixel())
{}

/** Create a ray tracing 3D scene specifying locations of light, camera, target, as well as shapes, and the dimensions and size of scene and background color
*/
RayTracer::RayTracer(Vector light, Vector camera, Vector target, vector<Sphere> shapes, int height, int width, int hx, int hy, Pixel bgColor) :
    light(light), camera(camera), target(target), shapes(shapes), HEIGHT(height), WIDTH(width), HX(hx), HY(hy), backgroundColor(bgColor), pixels(vector<Pixel>(WIDTH * HEIGHT)), view(vector<Vector>(WIDTH * HEIGHT))
{
    checkSceneValidity();
    generateView();
}

// Output png file of scene
bool RayTracer::saveSceneToPNG(string filename)
{
    // Can't render scene
    if (!VALID_SCENE) {
        return false;
    }

    // Render PNG named filename
    bool flag = false;
    unsigned error;

    //write png
    if (filename.empty()) {
        error = lodepng::encode("scene.png", createLoadablePixelVector(), WIDTH, HEIGHT);
        cout << "Scene was saved with name scene.png" << endl;
    }
    else {
        error = lodepng::encode(filename, createLoadablePixelVector(), WIDTH, HEIGHT);
        cout << "Scene was saved with name " << filename << endl;
    }

    if (error == 0)
        flag = true;

    return flag;
}

// Output png file of scene with default name
bool RayTracer::saveSceneToPNG()
{
    return saveSceneToPNG("scene.png");
}

/** Vector arithmetic to calculate each ray pointing to each pixel on the view (stored in view vector/array)
*/
void RayTracer::generateView()
{
    Vector cameraDirection = target - camera;
    Vector unitCameraDirection = cameraDirection.formUnitVector();

    // Arbitrary camera distance set to 1
    double cameraDistance = 1;

    // Width of half of viewport
    double g_x = HX / 2.0;
    // Height of half of viewport
    double g_y = HY / 2.0;

    // vector facing across image
    Vector viewHorizontalDirection = cameraDirection.cross(Vector(0, 1, 0));
    Vector unitHorizontal = viewHorizontalDirection.formUnitVector();
    // vector facing down image
    Vector viewVerticalDirection = unitCameraDirection.cross(unitHorizontal);
    Vector unitVertical = viewVerticalDirection.formUnitVector();

    // First pixel: p_11 = t_n(d) - g_x(b_n) - g_y(v_n)
    Vector viewDistance = unitCameraDirection.scalarMult(cameraDistance);   // t_n(d)
    Vector viewLeftSide = unitHorizontal.scalarMult(g_x);   // g_x(b_n)
    Vector viewTop = unitVertical.scalarMult(g_y);  // g_y(v_n)
    Vector p_11 = viewDistance - viewLeftSide - viewTop;

    // Using the first pixel, find the direction of all pixels on the viewport
    for (int i = 0; i < view.size(); i++) {

        // k = WIDTH, m = HEIGHT, j = row, i = column in comments
        int row = (i / (WIDTH)) + 1;
        int column = (i + 1) - double((row - 1.0) * WIDTH);

        // q_x = (2g_x/(k-1)) * b_n - depends on position of pixel
        double x_scaleToScreen = (2 * g_x) / (WIDTH - 1.0);
        Vector pixel_x_start = unitHorizontal.scalarMult(x_scaleToScreen);

        // q_y = (2g_y/(m-1)) * v_n
        double y_scaleToScreen = (2 * g_y) / (HEIGHT - 1.0);
        Vector pixel_y_start = unitVertical.scalarMult(y_scaleToScreen);

        // Each pixel: p_ij = p_11 + q_x(i-1) + q_y(j-1)
        Vector pixel_x_coord = pixel_x_start.scalarMult(column - 1.0);
        Vector pixel_y_coord = pixel_y_start.scalarMult(row - 1.0);
        Vector p_ij = p_11 + pixel_x_coord + pixel_y_coord;

        // Generates view rays (for ray tracing)
        Vector p_ij_normalized = p_ij.formUnitVector();
        view[i] = p_ij_normalized;
    }
}

/** Ensure that scene is valid (renderable)
*/
void RayTracer::checkSceneValidity()
{
    // Camera can't be looking at itself
    if (target.getI() == camera.getI() && target.getK() == camera.getK()) {
        VALID_SCENE = false;
    }
    else {
        VALID_SCENE = true;
    }
}

/**
 * Color each pixel in scene
 */
void RayTracer::renderScene()
{
    colorPixels();
    cout << "Scene rendered, ready to export to PNG" << endl;
}

/**
 * Setter methods to change scene parameters - call renderScene to see updates
 */
void RayTracer::changeLightLocation(const Vector& newLight)
{
    light = newLight;
}

void RayTracer::changeCameraLocation(const Vector& newCamera)
{
    camera = newCamera;
}

void RayTracer::changeTargetLocation(const Vector& newTarget)
{
    target = newTarget;
}

/**
 * Add a shape to the scene - call renderScene to see updates
 */
void RayTracer::addShape(Sphere newShape)
{
    shapes.push_back(newShape);
}

/** Determine coloring of pixels in scene based
*/
void RayTracer::colorPixels()
{
    // Code to determine color at each pixel using Lambertian shading 
    // Loop through rays in view
    for (int i = 0; i < view.size(); i++) {
        // Current row
        int row = (i / (WIDTH)) + 1;

        // Current ray tracing vector
        Vector ray = view[i];

        // Loop through each shape and determine coloring based on:
        /*
        (1) If there is a shape at that pixel (ray intersects with shape)
            -> How incident is that shape intersection vector with the light source
        (2) If there is no shape at that pixel
            -> Color with background color
        */
        bool intersectedShape = false;
        for (int n = 0; n < shapes.size(); n++) {

            Sphere shape = shapes.at(n);

            Vector intersectPoint = shape.intersect(camera, ray);

            // If ray intersects sphere
            if (!isinf(intersectPoint.getI()) && !isinf(intersectPoint.getJ()) && !isinf(intersectPoint.getK())) {
                // Calculate color of shape based on light intensity at intersection point
                Vector lightVector = (light - intersectPoint).formUnitVector();

                // 1 = most lit by light
                // 0 = not lit by light (use ambient color)
                double incidentLight = lightVector * (shape.normal(intersectPoint));
                if (incidentLight < 0.0)
                    incidentLight = 0.0;

                // Pixel colors before scaled by ambience
                Pixel shapeColorUnscaled = shape.color();

                // Pixel color scale factor
                double RGBShading = shape.ambient() + (1 - shape.ambient()) * incidentLight;

                Pixel pixelColor;
                //R 
                pixelColor.R = shapeColorUnscaled.R * RGBShading;
                //G
                pixelColor.G = shapeColorUnscaled.G * RGBShading;
                //B
                pixelColor.B = shapeColorUnscaled.B * RGBShading;

                pixels.at(i) = pixelColor;
                intersectedShape = true;
            }

            if (intersectedShape) {
                break;  // Can only intersect one shape
            }
        }

        // Color with background color
        if (!intersectedShape) {
            pixels.at(i) = backgroundColor;
        }
    }
}

/** Loop through each Pixel struct and extract each pixel's RGBA value to add to vector to create PNG
*/
vector<unsigned char> RayTracer::createLoadablePixelVector()
{
    vector<unsigned char> rawPixels;

    for (int i = 0; i < pixels.size(); i++) {
        rawPixels.push_back(pixels.at(i).R);
        rawPixels.push_back(pixels.at(i).G);
        rawPixels.push_back(pixels.at(i).B);
        rawPixels.push_back(pixels.at(i).A);
    }

    return rawPixels;
}
