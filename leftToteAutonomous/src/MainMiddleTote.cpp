#include <Robot.hpp>

void Robot::MainMiddleTote()
	{
	// LIFTING THE TOTE
		/*while (armEncoder.GetDistance() < 5 && IsAutonomous()) // 5 inches off the ground
		{*/
			SetGearBoxMotors(-0.75, -0.75);
			Wait(1);
		//}
		SetGearBoxMotors(0,0);
		//double initialAngle = gyro.GetAngle(); // Here for testing etc.

		/**Strafes Left 33"**/
		// left front backward
		// left back forward
		// right front forward
		// right back backward
		ResetEncoders();
		double dist = sonic.GetValue() / (9.766 * 2);
		while (fabs(rightFrontEncoder.GetDistance()) < (33) && IsAutonomous())// 89.5 inches traveled
		{
			//setRobotDrive(0,0,0,0);
			//Wait(0.1);
			if(dist > 20)
			{
				SetRobotDrive(-0.5,0.5,0.5,-0.5);
			}
			else
			{
				SetRobotDrive(0,0,0,0);
			}
			dist = sonic.GetValue() / (9.766 * 2);
			SmartDashboard::PutNumber("Ultrasonic number: ", dist);
		}
		SetRobotDrive(0,0,0,0);
		ResetEncoders();
		/**TURN 90 DEG**/
		initialAngle = gyro.GetAngle();
		while (angleChange < 85) // change in rotatation less than 90
		{
			SetRobotDrive(0.5, -0.5,0.5, /*-0.5, 0.5,*/ -0.5); // clockwise rotational movement
			angleChange = fabs(fabs(initialAngle) - fabs(gyro.GetAngle()));
		}
		gyro.Reset();
		angleChange = 0;
		SetRobotDrive(0,0,0,0);

		/**DRIVE BACKWARD 56"**/
		dist = sonic.GetValue() / (9.766 * 2);
		while (fabs(rightFrontEncoder.GetDistance()) < (56) && IsAutonomous())// 56 inches traveled
		{
			//setRobotDrive(0,0,0,0);
			//Wait(0.1);
			if(dist > 20)
			{
				SetRobotDrive(-0.5,-0.5,-0.5,-0.5);
			}
			else
			{
				SetRobotDrive(0,0,0,0);
			}
			dist = sonic.GetValue() / (9.766 * 2);
			SmartDashboard::PutNumber("Ultrasonic number: ", dist);
		}
		SetRobotDrive(0,0,0,0);
		ResetEncoders();


		/** LOWERING THE 4 BAR **/
		/*while (armEncoder.GetDistance() < 5 && IsAutonomous()) // 5 inches off the ground
		{*/
			SetGearBoxMotors(0.4, 0.4);
			Wait (0.35);
		//}

		SetGearBoxMotors(0,0);
	}
