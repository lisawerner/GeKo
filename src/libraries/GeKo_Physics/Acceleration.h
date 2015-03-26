#pragma once

class Acceleration{
protected:
	double m_acceleration;
	double m_speed; 		 //momentane Geschwindigkeit
	double maxSpeed;    // Man sollte irgendwann aufhören, oder irre ich mich da?
	
public:
	Acceleration();
	Acceleration(double accel, double max);
	~Acceleration();
	void setAcceleration(double newAccel);
	double getAcceleration();
	
	void accelerate();

	void setSpeed(double speed);
	double getSpeed();
};