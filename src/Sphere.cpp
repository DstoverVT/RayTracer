#include "Sphere.hpp"

#include <vector>	// C++ vector class for dynamic arrays, not to be confused with my defined Vector class
#include <math.h>
using std::vector;

/** Create default sphere (red, with radius 1, and position 0)
*/
Sphere::Sphere() : rad(1), pos(Vector(0, 0, 0)), col(Pixel{ 255, 0, 0, 255 }), amb(0.2)
{}

/** Constructor to create any type of sphere
*/
Sphere::Sphere(double rad, Vector pos, Pixel col, double amb) : rad(rad), pos(pos), col(col), amb(amb)
{}

/** Getter: Return color vector/array of sphere
*/
Pixel Sphere::color() const
{
	return col;
}

/**	Getter: Return sphere position
*/
Vector Sphere::position() const
{
	return pos;
}

/** Getter: Return sphere ambient color (darkest possible color)
*/
double Sphere::ambient() const
{
	return amb;
}

/**
* Intersect method determines if a ray (d) intersects with the sphere using 3D vector arithmetic
*/
Vector Sphere::intersect(const Vector& s, const Vector& d) const
{
	// v = S - C = position of camera - center of sphere
	Vector v = s - pos;

	// ((v dot d)^2 - ((norm v)^2 - r^2))
	double determineIntersect = pow(v * d, 2) - (pow(v.norm(), 2) - pow(rad, 2));

	// Determine if intersects: ((v dot d)^2 - ((norm v)^2 - r^2)) > 0
	// Intersection occurs
	if (determineIntersect > 0) {
		// Find intersection point
		// t = -(v dot d) +- sqrt((v dot d)^2 - (
		double intersectLength = -(v * d) - sqrt((pow(v * d, 2)) - (pow(v.norm(), 2) - pow(rad, 2)));

		// Intersection point at y = S + t*d
		// scalar multiplication
		Vector rayScale = d.scalarMult(intersectLength);
		Vector intersection = s + rayScale;

		return intersection;
	}

	// If no intersection occurs
	return Vector(INFINITY, INFINITY, INFINITY);

}

/** Determine vector normal to Sphere surface at a point on the Sphere
*/
Vector Sphere::normal(const Vector& pos) const
{
	// n = (y - C) / norm(y - C)
	Vector normalVector = pos - this->pos;
	double nNormRecip = 1 / normalVector.norm();
	Vector n(normalVector.getI() * nNormRecip, normalVector.getJ() * nNormRecip, normalVector.getK() * nNormRecip);

	return n;
}

/** Getter: Return sphere radius
*/
double Sphere::radius() const
{
	return rad;
}