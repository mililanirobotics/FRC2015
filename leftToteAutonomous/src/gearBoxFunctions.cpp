#include <Robot.hpp>
void Robot::SetGearBoxMotors(double gearBoxOneSpeed, double gearBoxTwoSpeed)
	{
		gearBoxOne.Set(gearBoxOneSpeed);
		gearBoxTwo.Set(gearBoxTwoSpeed);
	}
