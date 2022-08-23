#include<cmath>

class MagnusForce:public Vector3d{
	double cl;
public:
	MagnusForce(double airDensity,double area,double r, Vector3d velocity,double wx,double wy,double wz){
	
		this->x = 0.5*airDensity*area*0.01*r*((wy*velocity.z)-(wz*velocity.y));
		this->y = -0.5*airDensity*area*0.01*r*((wz*velocity.x) - (wx*velocity.z));
		this->z = 0.5*airDensity*area*0.01*r*((wx*velocity.y) - (wy*velocity.x));
		cout << "fmx:  " << x << endl;
		cout << "fmy:  " << y << endl;
		cout << "fmz:  " << z << endl;
	}
};

