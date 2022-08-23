
class DragForce:public Vector3d{
	double cd;
public:
	DragForce(double airDensity,double cd,double area,Vector3d velocity){

		cout<<"airDensity :"<<airDensity<<endl;
		cout<<"cd :"<<cd<<endl;
		cout<<"area :"<<area<<endl;
		cout<<"vx :"<<velocity.x<<endl;
		
		cout<<"vy :"<<velocity.y<<endl;
		
		cout<<"vz :"<<velocity.z<<endl;

		double fd = 0.5*airDensity*pow(velocity.getMagnitude(), 2)*cd*area*0.1;
		
		if (velocity.getMagnitude() != 0)
		{
			this->x = -fd*velocity.x / velocity.getMagnitude();
			this->y = -fd*velocity.y / velocity.getMagnitude();
			this->z = -fd*velocity.z / velocity.getMagnitude();
		}
		else
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}
		cout << "F drag: " << fd << endl;
		cout << "fdx:  " << x << endl;
		cout << "fdy:  " << y << endl;
		cout << "fdz:  " << z << endl;
	}
};