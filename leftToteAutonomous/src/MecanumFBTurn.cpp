#include <Robot.hpp>
void Robot::MecanumFBTurn()
{
	float x = 0; // x-axis motion-right (+), left (-)
	float y = 0; // y-axis motion-forward (+), backward (-)
	float z = 0; // z-axis motion-clockwise (+), counterclockwise (-)
	float yPercent;
	float zPercent;
	float theta;
	// UPDATING JOYSTICK AXES
	if (fabs(stickOne.GetRawAxis(0)) > .1)
		z = stickOne.GetRawAxis(0); // x-axis threshold
	else
		z = 0;
	if (fabs(stickOne.GetRawAxis(1)) > .1)
		y = -(stickOne.GetRawAxis(1)); // y-axis threshold
	else
		y = 0;
	if (fabs(stickTwo.GetRawAxis(0)) > .1)
		x = stickTwo.GetRawAxis(0); // z-axis threshold
	else
		x = 0;
	theta = atan((fabs(y))/(fabs(z))) * (180 / M_PI);


	// IMPLEMENTING CONCURRENT FORWARD & TURNING MOVEMENT
	//yPercent = abs(y)/(abs(y+z));
	//zPercent = abs(z)/(abs(y+z));

	// Y-AXIS MOTION AND ROTATIONAL MOTION
	if(fabs(y) > fabs(z) && theta >= 70) // GO FORWARD AND BACKWARD
	{
		leftFront.Set(y * leftFrontPolarity);
		rightFront.Set(y * rightFrontPolarity);
		leftBack.Set(y * leftBackPolarity);
		rightBack.Set(y * rightBackPolarity);
	}
	else if(fabs(z) > fabs(y) && theta <= 20)
	{
		leftFront.Set(z * leftFrontPolarity * 1);
		rightFront.Set(z * rightFrontPolarity * -1);
		leftBack.Set(z * leftBackPolarity * 1);
		rightBack.Set(z * rightBackPolarity * -1);
	}
	else if (theta > 20 && theta < 70)
	{
		leftFront.Set(((y * leftFrontPolarity + z * leftFrontPolarity * 1 )/2));
		rightFront.Set(((y * rightFrontPolarity + z * rightFrontPolarity * -1)/2 ));
		leftBack.Set(((y * leftBackPolarity  + z * leftBackPolarity * 1))/2);
		rightBack.Set(((y * rightBackPolarity  + z * rightBackPolarity * -1))/2);
	}

	// X-AXIS STRAFE MOTION
	else if (fabs(x) > fabs(y) && fabs(x) > fabs(z))
	{
		if(x > 0) //tote at bottom (5 deg, cg is 2")
		{
			leftFront.Set(x * leftFrontPolarity * leftFrontRS);
			rightFront.Set(x * rightFrontPolarity * -1 * rightFrontRS);
			leftBack.Set(x * leftBackPolarity * -1 * leftBackRS);
			rightBack.Set(x * rightBackPolarity * rightBackRS);
		}
		/*else if(x < 0) //max load, 5 deg
		{
			leftFront.Set(x * leftFrontPolarity * 0.72);
			rightFront.Set(x * rightFrontPolarity * -0.80);
			leftBack.Set(x * leftBackPolarity * -1);
			rightBack.Set(x * rightBackPolarity * 0.75);
		}*/
		else if(x < 0) //tote at bottom (5 deg, cg is 2")
		{
			leftFront.Set(x * leftFrontPolarity * leftFrontLS);
			rightFront.Set(x * rightFrontPolarity * -1 * rightFrontLS);
			leftBack.Set(x * leftBackPolarity * -1 * leftBackLS);
			rightBack.Set(x * rightBackPolarity * rightBackLS);
		}
	}
	else if (stickOne.GetRawButton(4))
	{
		ResetEncoders();
		SetRobotDrive(-1*leftFrontLS*0.975,1*leftBackLS,1*rightFrontLS,-1*rightBackLS*0.975);
		Wait(1.0);
	}
	else if(stickOne.GetRawButton(10))
	{
		ResetEncoders();
		SetRobotDrive(-0.4,-0.4,-0.4,-0.4);
		Wait(2.5);
	}
	else if(stickOne.GetRawButton(11))
	{
		ResetEncoders();
		SetRobotDrive(0.4,0.4,0.4,0.4);
		Wait(2.5);
	}

	else // otherwise sticks are not pushed
	{
		SetRobotDrive(0,0,0,0);
	}
}
