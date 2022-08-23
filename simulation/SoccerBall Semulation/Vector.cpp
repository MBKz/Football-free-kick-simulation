#include "Vector.h"
#include <cmath>
#include <iostream>
using namespace std;
Vector3d::Vector3d(){}

Vector3d::Vector3d(double x, double y, double z){
	this->x = x;
	this->y = y;
	this->z = z;
	
}


Vector3d Vector3d::getUnitVector(){
	return  Vector3d(x / sqrt(x*x + y*y + z*z), y / sqrt(x*x + y*y + z*z), z / sqrt(x*x + y*y + z*z));
}

void Vector3d::scalarMulti(double a){
	this->x *= a;
	this->y *= a;
	this->z *= a;
}

Vector3d Vector3d::addVector(Vector3d v){
	return Vector3d(this->x + v.x, this->y + v.y, this->z + v.z);
}


Vector3d Vector3d::subtractVector(Vector3d v){
	return Vector3d(this->x - v.x, this->y - v.y, this->z - v.z);
}

double Vector3d::dotProduct(Vector3d a){
	return this->x*a.x + this->y*a.y + this->z*a.z;
}

double Vector3d::dotProduct(Vector3d a, double angle)	{
	return (sqrt(x*x + y*y + z*z))*a.getMagnitude()*cos(angle);
}


Vector3d Vector3d::crossProduct(Vector3d a){
	return Vector3d(this->y*a.z - this->z*a.y, -(this->x*a.z - this->z*a.x), this->x*a.y - this->y*a.x);
}

Vector3d Vector3d::crossProduct(Vector3d a,double theta){
	return Vector3d(this->getMagnitude()*a.getMagnitude()*sin(theta), this->getMagnitude()*a.getMagnitude()*sin(theta), this->getMagnitude()*a.getMagnitude()*sin(theta));
}



double Vector3d::getMagnitude(){ 
	
	return sqrt(x*x + y*y + z*z);
}