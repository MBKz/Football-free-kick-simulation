
class Vector3d{
public:
	double x, y, z;
	Vector3d();
	Vector3d(double x, double y, double z);

	Vector3d getUnitVector();
	
	void scalarMulti(double a);

	Vector3d addVector(Vector3d v);

	Vector3d subtractVector(Vector3d v);

	double dotProduct(Vector3d a);

	double dotProduct(Vector3d a, double angle);

	Vector3d crossProduct(Vector3d a);

	Vector3d crossProduct(Vector3d a,double theta);


	double getMagnitude();


};