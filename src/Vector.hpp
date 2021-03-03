#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>

/**
 * This is a basic C++ class to represent three-dimensional numbers.
 */ 
class Vector
{
public:
  /**
   * Default constructor. It should set the scalar components to 0.
   */ 
  Vector();
  
  /**
   * @param vx - the scalar value to use for i component
   * @param vy - the scalar value to use for j component
   * @param vz - the scalar value to use for k component
   */ 
  Vector( double vx, double vy, double vz );

  /**
   * Returns the scalar of the i component
   * @return vx.
   */ 
  double getI() const;

  /**
   * Returns the scalar of the j component
   * @return vy.
   */ 
  double getJ() const;

  /**
   * Returns the scalar of the k component
   * @return vz.
   */ 
  double getK() const;

  /**
   * Updates the scalar of the i component to the given newVx parameter.
   * @param newVx - the new value to use for the vx field.
   */ 
  void setI(double newVx);
  
  /**
   * Updates the scalar of the i component to the given newVx parameter.
   * @param newVy - the new value to use for the vx field.
   */ 
  void setJ(double newVy);

  /**
   * Updates the scalar of the i component to the given newVx parameter.
   * @param newVz - the new value to use for the vx field.
   */ 
  void setK(double newVz);
  
  /**
   * Returns true if the scalar components for this object and rhs are the same, false otherwise.
   * @return true if scalar components in both objects are the same.
   */ 
  bool equal( const Vector& rhs ) const;

  /**
   * Creates and returns a new Vector object representing the vector addition of two Vector objects
   * @return a new Vector object that contains the appropriate summed components
   * @param rhs - the Vector object to add to this object.
   */
  Vector operator+( const Vector &rhs ) const;

  /**
   * Creates and returns a new Vector object representing the vector subtraction of two Vector objects
   * @return a new Vector object that contains the appropriate difference components
   * @param rhs - the Vector object to subtract from this object.
   */
  Vector operator-( const Vector &rhs ) const;

  /**
   * Creates and returns a new Vector object that is cross product of this and the given Vector object.
   * @return a new Vector object that contains the cross product of this and the given Vector object.
   * @param rhs - the Vector object to cross with this object.
   */
  Vector cross( const Vector &rhs ) const;

  /**
   * Returns the dot product of this and the given Vector object.
   * @return the dot product of this and the given Vector object.
   * @param rhs - the Vector object to dot with this object.
   */
  double operator*( const Vector &rhs ) const;

  /**
  *	@return a vector multiplied by a scalar
  * @param mult - scalar multiplier
  */
  Vector scalarMult(const double& mult) const;

  /**
   * Returns the norm of the Vector object.
   * @return the norm (-1 if magnitude undefined)
   */
  double norm() const;

  /**
   * Returns the angle between two Vector objects in radians (over interval [0,2*pi)).
   * @param rhs - the Vector object to find the angle between with this object.
   * @return the angle (-1 if angle undefined)
   */
  double angle(const Vector &rhs) const;

  /**
  * Used to calculate the unit vector of any vector
  * @return unit vector of any vector (length 1, same direction)
  */
  Vector formUnitVector() const;

  /**
   * Outputs this Vector object on the given ostream.  ``vxi + vyj + vzk'' (for debugging).
   * @param out - the ostream object to use to output.
   */ 
  void output( std::ostream &out ) const;

private:

  double vx;
  double vy;
  double vz;
};

#endif
