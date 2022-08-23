#include "WeightForce.h"
#include "DragForce.h"
#include "MagnusForce.h"

class BallLogic{
	SoccerBall *ball;
	double airDensity;
	double airVisocity;
	double Wx , Wz ;
	double u;
	bool isRolling;
	double e;

public:
	BallLogic(SoccerBall *ball,double airdensity,double visocity,double frictionFactor,double e,double windX,double windZ){
		this->ball = ball;
		this->airDensity = airdensity;
		this -> Wx = windX ;
		this -> Wz = windZ;
		this -> u =frictionFactor ;
		this->isRolling=false;
		this->airVisocity=visocity;
		this->e=e;
	}

	void draw(){
		this->ball->draw();
	}

	void applyInitialForce(Vector3d initialForce)
	{
		ball->applyInitialForce(initialForce);
	}
	
	void applyDragTorque()
	{
		double dragtorqueX, dragtorqueY, dragtorqueZ;
		dragtorqueX = -6*PI*airVisocity*ball->getRadius()*ball->getAngulerVelocityX();
		dragtorqueY = -6 * PI*airVisocity*ball->getRadius()*ball->getAngulerVelocityY();
		dragtorqueZ = -6 * PI*airVisocity*ball->getRadius()*ball->getAngulerVelocityZ();

		cout <<"dragTorqueX: "<< dragtorqueX << endl;

		cout << "dragTorqueY: " << dragtorqueY << endl;

		cout << "dragTorqueZ: " << dragtorqueZ << endl;

		ball->applyDragTorque(dragtorqueX,dragtorqueY,dragtorqueZ);

	}


	void move(){
	Vector3d weight, drag, magnus,total;


	if(ball->getZ()>=-720)
	{
		
		weight = getWeightForce();
		drag = getDragForce();
		magnus = getMagnusForce();
		total = weight;
		total = total.addVector(magnus);
		total = total.addVector(drag);
		ball->applyForce(total , Wx,Wz);
		applyDragTorque();
		if (ball->getY()<=0)
		{
			hitTheGround();
		}

		ball->rotate();

	}
	else {
	
		ball->stop();
	}
		
	}

	void hitTheGround(){

		ball->resetY();
		cout << "**************************************  hit the ground  ******************************************" << endl;
		double vx0, vy0, vz0, wx0, wy0, wz0;
		vx0 = ball->getVelocityX();
		vy0 = ball->getVelocityY();
		vz0 = ball->getVelocityZ();
		wx0 = ball->getAngulerVelocityX();
		wy0 = ball->getAngulerVelocityY();
		wz0 = ball->getAngulerVelocityZ();


//		cout << "vx0: " << ball->getVelocityX() << " vy0: " << ball->getVelocityY() << " vz0: " << ball->getVelocityZ() << endl;
//		cout << "wx0: " << ball->getAngulerVelocityX() << " wy0: " << ball->getAngulerVelocityY() << " wz0: " << ball->getAngulerVelocityZ() << endl;
		double limit=2/(5*u*(1+e));//2/(5*u*(1+e));//the condition to move from bouncing
		cout<<"limit: "<<limit<<endl;
		if(isRolling)
		{
			
				

			cout<<"-------------------------------------start rolling----------------------------------"<<endl;
			ball->changeVelocity(ball->getAngulerVelocityZ()*ball->getRadius(),0,ball->getAngulerVelocityX()*ball->getRadius());
			double frictionTorque=ball->getMass()*9.8*u*ball->getRadius();
			cout<<"friction torque: "<<frictionTorque<<endl;
			double ftx=0,fty=0,ftz=0;
			if(ball->getAngularVelocity()!=0)
			{
				ftx=-frictionTorque*ball->getAngulerVelocityX()/ball->getAngularVelocity();
				fty=-frictionTorque*ball->getAngulerVelocityY()/ball->getAngularVelocity();
				ftz=-frictionTorque*ball->getAngulerVelocityZ()/ball->getAngularVelocity();
			}
		
			cout<<"ftx: "<<ftx<<endl;
			
			cout<<"fty: "<<fty<<endl;
			
			cout<<"ftz: "<<ftz<<endl;
			
			ball->applyFrictionTorque(ftx,fty,ftz);
		}
		else{
			
			if((ball->getVelocityX()!=0&&ball->getVelocityY()/ball->getVelocityX()<=limit)||(ball->getVelocityZ()!=0&&ball->getVelocityY()/ball->getVelocityZ()<=limit))
				isRolling=true;	

			ball->changeVelocity(0.6*vx0 + 0.4*wz0*(ball->getRadius()), -e*vy0, 0.6*vz0 + 0.4*wx0*(ball->getRadius()));

			ball->changeAngularVelocity(0.4*wx0 + ((0.6*vz0) / (ball->getRadius())), e*wy0, 0.4*wz0 + ((0.6*vx0) / ball->getRadius()));
				

		}

		
	


	//	cout << "vx: " << ball->getVelocityX() << " vy: " << ball->getVelocityY() << " vz: " << ball->getVelocityZ() << endl;
	//	cout << "wx: " << ball->getAngulerVelocityX() << " wy: " << ball->getAngulerVelocityY() << " wz: " << ball->getAngulerVelocityZ() << endl;
		

	}

	Vector3d getDragForce(){
		double re=airDensity*ball->getVelocity().getMagnitude()*2*ball->getRadius()/airVisocity;
		cout<<"Re: "<<re<<endl;
		double cd;

		if(re<100000)
			cd=0.47;
		else if(re <135000)
			cd=0.47-0.25*((re-100000)/35000);
		else 
			cd=0.22;

		cout<<"cd: "<<cd<<endl;
		return DragForce(airDensity,cd,ball->getArea(),ball->getVelocity());
	}
	


	Vector3d getMagnusForce(){
		return MagnusForce(airDensity,ball->getArea(), ball->getRadius(),ball->getVelocity(),ball->getAngulerVelocityX(),ball->getAngulerVelocityY(),ball->getAngulerVelocityZ());
	}

	
	Vector3d getWeightForce(){
		return WeightForce(ball->getMass());
	}

	SoccerBall* getBall(){ return ball; }

	void reset(double airDensity,double airVisocity,double u,double e,double wx,double wz,double mass,double radios,double Wx,double Wy,double Wz,double ballX, double ballY,double ballZ){
		this->airDensity=airDensity;
		this->airVisocity=airVisocity;
		this->Wx=wx;
		this->Wz=wz;
		this->u=u;
		this->e=e;
		ball->reset(mass,radios,Wx,Wy,Wz,ballX, ballY, ballZ);
		this->isRolling=false;
	}

};