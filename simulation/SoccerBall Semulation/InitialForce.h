#include "Vector.h"


class InitialForce :public Vector3d{
	//maybe should use an angles here
	InitialForce(double x, double y, double z) :Vector3d(x, y, z){}
};

