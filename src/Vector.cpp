#include <math.h>

#include "Vector.hpp"

using std::endl;

/**
Default constructor to set all vector components to 0
*/
Vector::Vector() : vx(0), vy(0), vz(0) {
}

/**
Three-argument constructor to set vector components to user-defined values
*/
Vector::Vector(double vx, double vy, double vz)
{
	this->vx = vx;
	this->vy = vy;
	this->vz = vz;
}

/**
return vector i-component scalar
*/
double Vector::getI() const
{
	return vx;
}

/**
return vector j-component scalar
*/
double Vector::getJ() const
{
	return vy;
}

/**
return vector k-component scalar
*/
double Vector::getK() const
{
	return vz;
}

/**
set vector i-component scalar
*/
void Vector::setI(double newVx)
{
	vx = newVx;
}

/**
set vector j-component scalar
*/
void Vector::setJ(double newVy)
{
	vy = newVy;
}

/**
set vector k-component scalar
*/
void Vector::setK(double newVz)
{
	vz = newVz;
}

/**
Determine if two vectors are equal, meaning that all of their vector components are equal, returning true if equal and false otherwise
*/
bool Vector::equal(const Vector& rhs) const
{
	return (getI() == rhs.getI() && getJ() == rhs.getJ() && getK() == rhs.getK());
}

/**
Add two vectors together by adding their vector components together and return the summed vector result
*/
Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(getI() + rhs.getI(), getJ() + rhs.getJ(), getK() + rhs.getK());
}

/**
Subtract two vectors by subtracting their vector components and return the difference vector result
*/
Vector Vector::operator-(const Vector& rhs) const
{
	return Vector(getI() - rhs.getI(), getJ() - rhs.getJ(), getK() - rhs.getK());
}

/**
Find the cross product of two vectors and return the vector output
*/
Vector Vector::cross(const Vector& rhs) const
{
	return Vector(getJ() * rhs.getK() - getK() * rhs.getJ(), getK() * rhs.getI() - getI() * rhs.getK(), getI() * rhs.getJ() - getJ() * rhs.getI());
}

/**
Find the dot product of two vectors and return the scalar output
*/
double Vector::operator*(const Vector& rhs) const
{
	return (getI() * rhs.getI() + getJ() * rhs.getJ() + getK() * rhs.getK());
}

/**
Scalar multiplication of a vector
*/
Vector Vector::scalarMult(const double& mult) const
{
	return Vector(getI() * mult, getJ() * mult, getK() * mult);
}

/**
Calculate the norm of a vector and return the scalar output
*/
double Vector::norm() const
{
	double result = sqrt(pow(getI(), 2) + pow(getJ(), 2) + pow(getK(), 2));
	if (isfinite(result)) {
		return result;
	}
	else {
		return -1;
	}
}

/**
Calculate the angle between two vectors and return the angle output in radians
*/
double Vector::angle(const Vector& rhs) const
{
	if (*this * rhs == 0 && (norm() * rhs.norm() == 0)) {
		return -1;
	}

	double result = acos(*this * rhs / (norm() * rhs.norm()));

	if (isfinite(result)) {
		return result;
	}
	else {
		return -1;
	}
}

/**	Calculate unit vector: v / ||v|| 
*/
Vector Vector::formUnitVector() const
{
	return scalarMult(1 / norm());
}


void Vector::output(std::ostream& out) const
{
	out << vx << "i + " << vy << "j + " << vz << "k" << endl;
}
