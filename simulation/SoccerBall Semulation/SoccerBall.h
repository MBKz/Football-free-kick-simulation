#include <glaux.h>	
#include <cmath>
#include "Torque.h"
#define dt 0.05

class SoccerBall
{
	Model_3DS ball;
	double r;
	double x, y, z;
	double angleX,angleY,angleZ;

	Vector3d velocity;
	double wx, wy, wz;
	double ax, ay, az;

	double angularAccelerationX;
	double angularAccelerationY;
	double angularAccelerationZ;

	
	double momentOfInertia;
	
	double m;
	double area;
public:
	SoccerBall(){
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->m = 0.4;
		this->r = 0.11;
		this->area = PI*pow(r, 2);
		this->momentOfInertia = 0.66 * m * r * r;
		this->angleX = 0;
		this->angleY = 0;
		this->angleZ = 0;
		this->wx = 0;
		this->wy = 0;
		this->wz = 0;
		this->angularAccelerationX = 0;
		this->angularAccelerationY = 0;
		this->angularAccelerationZ = 0;
		this->ax = 0;
		this->ay = 0;
		this->az = 0;
		this->velocity = Vector3d(0, 0, 0);
	}
	SoccerBall(double m,double r, double x, double y, double z,double wx,double wy,double wz,Model_3DS ball){
		this->r = r;
		this->x = x;
		this->y = y;
		this->z = z;
		this->m = m;
		this->area = PI*pow(r,2);
		this->ball = ball;
		this->momentOfInertia = 0.66 * m * r * r;
		this->angleX = 0;
		this->angleY = 50;
		this->angleZ = 0;
		this->wx = wx;
		this->wy = wy;
		this->wz = wz;
		this->angularAccelerationX = 0;
		this->angularAccelerationY = 0;
		this->angularAccelerationZ = 0;
		this->ax = 0;
		this->ay = 0;
		this->az = 0;
		this->velocity = Vector3d(0,0,0);
	}

	void draw()
	{
		cout << " x:" << x << " y:" << y << " z:" << z << endl;
		glPushMatrix();
		glTranslated(x,y+5,z);
		ball.scale = r ;

		ball.rot.x = angleX;
		ball.rot.y = angleY;
		ball.rot.z = angleZ;
		
		ball.Draw();
		glPopMatrix();
	}

	void applyInitialForce(Vector3d initialForce)
	{

		cout <<"init Fx: " << initialForce.x << " init Fy: " << initialForce.y << " init Fz: " << initialForce.z << endl;
		ax = initialForce.x / m;
		ay = initialForce.y / m;
		az = initialForce.z / m;

		velocity.x += ax*dt ;
		velocity.y += ay*dt;
		velocity.z += az*dt ;

	}
	void applyForce(Vector3d force, double Wx , double Wz){

		ax = force.x/m;
		ay = force.y / m;
		az = force.z / m;
		
	//	cout << "ax:" << ax << " ay:" << ay << " az:" << az << endl;
		

		if (!isAroundZero(velocity.getMagnitude()))
		{
	//		cout <<"velocity magnitude: "<< velocity.getMagnitude() << endl;
			velocity.x += ax*dt - Wx;
			velocity.y += ay*dt;
			velocity.z += az*dt - Wz;
		}
			
	//	cout << " vx:" << velocity.x << " vy:" << velocity.y << " vz:" << velocity.z << endl;

		x += velocity.x*dt + 0.5*ax*pow(dt, 2);
		y += velocity.y*dt + 0.5*ay*pow(dt, 2);
		z += velocity.z*dt + 0.5*az*pow(dt, 2);

	
//		cout << " x:" << x << " y:" << y << " z:" << z << endl;


	}

	void rotate(){

		
		wx += angularAccelerationX*dt;
		wy += angularAccelerationY*dt;
		wz += angularAccelerationZ*dt;
		
		cout << " wx:" << wx << " wy:" << wy << " wz:" << z << endl;

		angleX += wx*dt + angularAccelerationX*dt*dt;
		angleY += wy*dt + angularAccelerationY*dt*dt;
		angleZ += wz*dt + angularAccelerationZ*dt*dt;
		
		cout << " anglex:" << angleX << " angley:" << angleY << " anglez:" << angleZ << endl;

	}

	void applyFrictionTorque(double ftx,double fty,double ftz){

		angularAccelerationX = ftx/ momentOfInertia;
		angularAccelerationY =fty/ momentOfInertia;
		angularAccelerationZ = ftz/ momentOfInertia;

	}

	void applyDragTorque(double draqTorqueX,double dragTorqueY,double dragTorqueZ){

		angularAccelerationX = draqTorqueX / momentOfInertia;
		angularAccelerationY = dragTorqueY / momentOfInertia;
		angularAccelerationZ = dragTorqueZ / momentOfInertia;

		cout << "AngularAccelerationX: " << angularAccelerationX << endl;

		cout << "AngularAccelerationY: " << angularAccelerationY << endl;

		cout << "AngularAccelerationZ: " << angularAccelerationZ << endl;

		cout << "____________________________________________________" << endl;

	
	}

	bool isAroundZero(double x){
		if (x<=0.1 && x>=0)
			return true;
		else
			return false;

	}

	double getX(){ return this->x; }

	double getY(){ return this->y; }

	double getZ(){ return this->z; }

	double getAx(){ return this->ax; }

	double getAy(){ return this->ay; }

	double getAz(){ return this->az; }

	double getArea(){ return PI*pow(this->r,2); }

	double getRadius(){ return this->r; }

	double getMass(){ return this->m; }

	double getAngulerVelocityX(){ return this->wx; }

	double getAngulerVelocityY(){ return this->wy; }
	
	double getAngulerVelocityZ(){ return this->wz; }
	
	Vector3d getVelocity(){ return this->velocity; }

	double getVelocityX(){ return this->velocity.x; }

	double getVelocityY(){ return this->velocity.y; }

	double getVelocityZ(){ return this->velocity.z; }

	double getAngularVelocity(){ return sqrt(wx*wx+wy*wy+wz*wz);}

	void resetY(){ this->y = 0; }
	
	/*void editVelocity(double a)
	{
		this->velocity.scalarMulti(a);
	}*/

	void changeVelocity(double x,double y, double z)
	{
		this->velocity.x = x;
		this->velocity.y = y;
		this->velocity.z = z;
	}

	void changeAngularVelocity(double x, double y, double z)
	{
		this->wx = x;
		this->wy = y;
		this->wz = z;
	}

	void reset(double m,double r,double wx,double wy,double wz,double x0, double y0, double z0){
		this->x = x0;
		this->y = y0;
		this->z = z0;
		this->m=m;
		this->r=r;

		this->angleX = 0;

		this->angleY = 0;

		this->angleZ = 0;

		this->wx = wx;

		this->wy = wy;
		
		this->wz = wz;

		this->velocity = Vector3d(0,0,0);
		this->angularAccelerationX=0;
		this->angularAccelerationY=0;
		this->angularAccelerationZ=0;

	}

	void stop(){
		this->ax=0;
		this->ay=0;
		this->az=0;
		this->velocity=Vector3d(0,0,0);

		}

};

