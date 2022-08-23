class WeightForce:public Vector3d{
public:
	WeightForce(double m):Vector3d(0,-m*9.8,0){
	}
};