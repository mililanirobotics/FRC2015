#include <Robot.hpp>

void Robot::MainRobotLeftTote()
	{

		// LIFTING THE TOTE
		/*while (armEncoder.GetDistance() < 5 && IsAutonomous()) // 5 inches off the ground
		{*/

			SetGearBoxMotors(-0.75, -0.75);
			Wait(1);
		//}
		SetGearBoxMotors(0,0);
		//double initialAngle = gyro.GetAngle(); // Here for testing etc.
		/**DRIVE BACKWARD 89.5"**/
		ResetEncoders();
		double dist = sonic.GetValue() / (9.766 * 2);
		while (fabs(rightFrontEncoder.GetDistance()) < (89.5-2.95) && IsAutonomous())// 89.5 inches traveled
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

		/**DRIVE BACKWARD 106.5**/
		dist = sonic.GetValue() / (9.766 * 2);
		while (fabs(rightFrontEncoder.GetDistance()) < (106.95-7.95) && IsAutonomous())// 106.95 inches traveled
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
#ifdef dontDrive
		/**DRIVE BACKWARD 112.55**/
		ResetEncoders();
		dist = sonic.GetValue() / (9.766 * 2);
		while (fabs(rightFrontEncoder.GetDistance()) < ((112.55-6.95)/10) && IsAutonomous())// 89.5 inches traveled
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
		setRobotDrive(0,0,0,0);
		resetEncoders();
#endif
#if 0
		// LIFTING THE TOTE
		while (armEncoder.GetDistance() < 5) // 5 inches off the ground
		{
			SetGearBoxMotors(0.75, 0.75);
		}
		SetGearBoxMotors(0,0);

		// DRIVING BACKWARDS
		while (rightFrontEncoder.GetDistance() < 89.5)// 89.5 inches traveled
		{
			SetRobotDrive(-0.8,-0.8,-0.8,-0.8); // Backwards movement
		}
		SetRobotDrive(0,0,0,0);
		ResetEncoders();
		//initialAngle = gyro.GetAngle();

		// ROTATING CLOCKWISE
		/*while (fabs(initialAngle - gyro.GetAngle()) < 90) // change in rotatation less than 90
		{
			setRobotDrive(0.8,0.8,-0.8,-0.8); // clockwise rotational movement
		}
		gyro.Reset();*/
		SetRobotDrive(0,0,0,0);

		// DRIVING BACKWARDS
		while (rightFrontEncoder.GetDistance() < 106.95) // 106.95 inches traveled
		{
			SetRobotDrive(-0.8,-0.8,-0.8,-0.8);
		}
		SetRobotDrive(0,0,0,0);
		resetEncoders();

		// LOWERING THE TOTE IF THERE IS STACKING POTENTIAL
		if (stackingPotential == 1)
		{
			while (armEncoder.GetDistance() < 5) // 5 inches off the ground
			{
				SetGearBoxMotors(-0.75, -0.75);
			}
			SetGearBoxMotors(0,0);
		}

		// DRIVING BACKWARDS
		while (rightFrontEncoder.GetDistance() < 112.55)// 112.55 inches traveled
		{
			SetRobotDrive(-0.8,-0.8,-0.8,-0.8); // Backwards movement
		}
		SetRobotDrive(0,0,0,0);
		ResetEncoders();
#endif
	}
