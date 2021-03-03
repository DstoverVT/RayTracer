#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>

#include "Vector.hpp"
#include "Pixel.hpp"

class Sphere
{
public:
  /** 
   * default constructor: creates a purely red sphere with radius one at position (0,0,0) and with ambience of 0.2
   * @return sets data fields appropriately
   */
  Sphere();
  
  /** 
   * parameterized constructor: creates a sphere with user supplied color at given position with specified radius
   * @return sets data fields appropriately
   */
  Sphere(double rad, Vector pos, Pixel col, double amb);

  /** 
   * The color of the sphere
   * @return color sphere: order is rgba with rgb in the interval [0,255] and a = 255;
   */
  Pixel color() const;

  /** 
   * The position of the sphere
   * @return position of sphere (center) w/r/t Vector(0,0,0)
   */
  Vector position() const;

  /** 
   * The ambient of the sphere
   * @return ambience of sphere on the interval [0,1]
   */
  double ambient() const;

  /**
   * calculates the intersection point, if one exists, between the sphere surface and the ray originating from position s with direction d (a unit vector)
   * @return position (as Vector w/r/t (0,0,0)) of where ray with origin s and unit direction d intersects with sphere, (inf,inf,inf) for no intersection
   */
  Vector intersect(const Vector& s, const Vector& d) const;
  
  /**
   * determines the unit normal vector on the surface of the sphere at the position given by the vector pos (w/r/t (0,0,0))
   * @return unit normal vector for the surface of the sphere at a user-specified position on the surface
   */
  Vector normal(const Vector& pos) const;

  /** 
   * This shape (but not all shapes) has a radius, so we add a new member function to allow the user to query it
   * @return the radius of the sphere
   */
  double radius() const;

private:

  double rad;  //radius of sphere
  Vector pos;  //position of sphere (center) w/r/t (0,0,0)
  Pixel col; //color of sphere: struct data is rgba with rgb in the interval [0,255] and a = 255;
  double amb; //ambience of sphere on the interval [0,1] 
};

#endif
