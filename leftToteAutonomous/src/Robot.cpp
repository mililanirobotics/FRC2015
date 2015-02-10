#include <Robot.hpp>
	Robot:: Robot():
		 leftFront(0), // leftFront motor uses PWM port 1
		 leftBack(1), // leftBack motor uses PWM port 2
		 rightFront(2), // rightBack motor uses PWM port 3
		 rightBack(3), // rightBack motor uses PWM port 4
		 gearBoxOne(4),
		 gearBoxTwo(5),
		 // Channel A Encoder Wires are colored White
		 leftFrontEncoder(8, 9, false, Encoder::k4X), // Green Encoder x4 sampling, no reverse
		 leftBackEncoder(6, 7, false, Encoder::k4X), // Blue Encoder x4 sampling, no reverse
		 rightFrontEncoder(0, 1, false, Encoder::k4X), // Orange Encoder x4 sampling, no reverse
		 rightBackEncoder(2, 3, false, Encoder::k4X), // Red Encoder x4 sampling, no reverse
		 armEncoder(4,5, false, Encoder::k4X),
		 stickOne(0), // Logitech Game Controller with Driverstation port 0
		 stickTwo(1), // Joystick with driverstation port 1
		 gyro(0),
		 sonic(1),
		 accelerometer(Accelerometer::Range::kRange_8G)
	{
		leftFrontEncoder.SetSamplesToAverage(5);
		leftFrontEncoder.SetDistancePerPulse(2.0*3.14*3.0/360);
		leftFrontEncoder.SetMinRate(1.0);

		leftBackEncoder.SetSamplesToAverage(5);
		leftBackEncoder.SetDistancePerPulse(2.0*3.14*3.0/360);
		leftBackEncoder.SetMinRate(1.0);

		rightFrontEncoder.SetSamplesToAverage(5);
		rightFrontEncoder.SetDistancePerPulse(2.0*3.14*3.0/360);
		rightFrontEncoder.SetMinRate(1.0);

		rightBackEncoder.SetSamplesToAverage(5);
		rightBackEncoder.SetDistancePerPulse(2.0*3.14*3.0/360);
		rightBackEncoder.SetMinRate(1.0);

		armEncoder.SetSamplesToAverage(5);
		armEncoder.SetDistancePerPulse(92.0/360);
		armEncoder.SetMinRate(1.0);

		gyro.InitGyro();
	}

	void Robot::SetRobotDrive(double leftFrontSpeed, double rightFrontSpeed, double leftBackSpeed, double rightBackSpeed)
	{
		leftFront.Set(leftFrontSpeed*autonomousLeftFrontCalibration);
		leftBack.Set(leftBackSpeed*autonomousLeftBackCalibration);
		rightFront.Set(rightFrontSpeed*autonomousrightFrontCalibration);
		rightBack.Set(rightBackSpeed*autonomousrightBackCalibration);
	}
	void Robot::ResetEncoders()
	{
		leftFrontEncoder.Reset();
		leftBackEncoder.Reset();
		rightFrontEncoder.Reset();
		rightBackEncoder.Reset();
		gyro.Reset();
	}
	double Robot::EncoderDistance()
	{
		double totalRecordedDistance = /*fabs(leftFrontEncoder.GetDistance())+ */ fabs(rightFrontEncoder.GetDistance()) + fabs(leftBackEncoder.GetDistance()) + fabs(rightBackEncoder.GetDistance());
		double distanceTraveled = totalRecordedDistance / 3;
		return distanceTraveled;
	}
	void Robot::Autonomous()
	{
		//while(IsAutonomous() && IsEnabled()) {}
			// if dial amoount ~=1
			MainRobotLeftTote();
	}
	void Robot::OperatorControl()
	{
		/*
		//gyro.Reset();
		int leftFrontPolarity = 1; // These variables flip the sign value of
		int leftBackPolarity = 1; // the motors in the situation that they are
		int rightFrontPolarity = -1; // flipped
		int rightBackPolarity = -1;

		//MOTOR STRAFE CG PRESET VARIABLES
		float leftFrontRS = 1;		//RIGHT STRAFE VARIABLES
		float rightFrontRS = 0.9;
		float leftBackRS = 1;
		float rightBackRS = 0.783;

		float leftFrontLS = 0.83;		//LEFT STRAFE VARIABLES
		float rightFrontLS = 0.80;
		float leftBackLS = 0.854;
		float rightBackLS = 0.83;

		*/
		int presetStatus = 0;
/*
		float x = 0; // x-axis motion-right (+), left (-)
		float y = 0; // y-axis motion-forward (+), backward (-)
		float z = 0; // z-axis motion-clockwise (+), counterclockwise (-)
*/

		while (IsOperatorControl() && IsEnabled())
		{
			MecanumFBTurn();
#if 0
			if (fabs(stickOne.GetRawAxis(0)) > .2)
				z = stickOne.GetRawAxis(0); // x-axis threshold
			else
				z = 0;
			if (fabs(stickOne.GetRawAxis(1)) > .2)
				y = -(stickOne.GetRawAxis(1)); // y-axis threshold
			else
				y = 0;
			if (fabs(stickTwo.GetRawAxis(0)) > .2)
				x = stickTwo.GetRawAxis(0); // z-axis threshold
			else
				x = 0;

			// y-axis motion
			if (fabs(y) > 0.2 || fabs(z) > 0.2)
			{
				leftFront.Set((y * leftFrontPolarity + z * leftFrontPolarity * 1));
				rightFront.Set((y * rightFrontPolarity + z * rightFrontPolarity * -1));
				leftBack.Set((y * leftBackPolarity + z * leftBackPolarity * 1));
				rightBack.Set((y * rightBackPolarity + z * rightBackPolarity * -1));
			}
			else // Otherwise sticks are not pushed
			{
				leftFront.Set(0);
				leftBack.Set(0);
				rightFront.Set(0);
				rightBack.Set(0);
			}


			if (stickTwo.GetRawButton(6)) //no tote, 5 degree preset
			{
				leftFrontRS = 1;
				rightFrontRS = 0.9;
				leftBackRS = 1;
				rightBackRS = 0.87;
				leftFrontLS = 0.83;
				rightFrontLS = 0.80;
				leftBackLS = 0.96;
				rightBackLS = 0.83;

				presetStatus = 0; //When preset active, displays 0
			}
			if (stickTwo.GetRawButton(7)) //one tote , 5 degree preset
			{
				leftFrontRS = 0.84;
				rightFrontRS = 1;
				leftBackRS = 1;
				rightBackRS = 0.80;
				leftFrontLS = 0.72;
				rightFrontLS = 0.84;
				leftBackLS = 1;
				rightBackLS = 0.75;

				presetStatus = 1; //When preset active, displays 1
			}
			if (stickTwo.GetRawButton(10)) //two tote & max load, 5 degree preset
			{
				leftFrontRS = 1;
				rightFrontRS = 1;
				leftBackRS = 1;
				rightBackRS = 1;
				leftFrontLS = 0.72;
				rightFrontLS = 0.80;
				leftBackLS = 1;
				rightBackLS = 0.75;

				presetStatus = 2; //When preset active, displays 2
			}
			if (stickTwo.GetRawButton(11)) //OTHER, 5 degree preset
			{
				leftFrontRS = 1;
				rightFrontRS = 1;
				leftBackRS = 1;
				rightBackRS = 1;
				leftFrontLS = 1;
				rightFrontLS = 1;
				leftBackLS = 1;
				rightBackLS = 1;
				presetStatus = -1;
			}
			if (stickTwo.GetRawButton(4)) // left strafe
			{
				leftFront.Set(.8*leftFrontPolarity);
				rightFront.Set(.8*rightFrontPolarity * -1);
				leftBack.Set(.8*leftBackPolarity * -1 );
				rightBack.Set(.8*rightBackPolarity);
			}

			else if (stickTwo.GetRawButton(5)) // right strafe
			{
				leftFront.Set(.8*leftFrontPolarity);
				rightFront.Set(.8*rightFrontPolarity * -1);
				leftBack.Set(.8*leftBackPolarity * -1);
				rightBack.Set(.8*rightBackPolarity);
			}
			// y-axis motion
			if (fabs(y) > fabs(x) && fabs(y) > fabs(z))
			{
				leftFront.Set(y * leftFrontPolarity);
				rightFront.Set(y * rightFrontPolarity);
				leftBack.Set(y * leftBackPolarity);
				rightBack.Set(y * rightBackPolarity);
			}


			// x-axis motion
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

			// rotational motion
			else if (fabs(z) > fabs(y) && fabs(z) > fabs(x))
			{
				leftFront.Set(z * leftFrontPolarity * 1);
				rightFront.Set(z * rightFrontPolarity * -1);
				leftBack.Set(z * leftBackPolarity * 1);
				rightBack.Set(z * rightBackPolarity * -1);
			}

			// Small turn motion
			else if(stickOne.GetRawButton(5)) //turn left
			{
				leftFront.Set(0.5);
				rightFront.Set(0.3);
				leftBack.Set(0.5);
				rightBack.Set(0.3);
			}
			else if(stickOne.GetRawButton(4)) //turn right
			{
				leftFront.Set(-0.3);
				rightFront.Set(-0.5);
				leftBack.Set(-0.3);
				rightBack.Set(-0.5);
			}

			else // Otherwise sticks are not pushed
			{
				leftFront.Set(0);
				leftBack.Set(0);
				rightFront.Set(0);
				rightBack.Set(0);
			}
			x = 0; // x-axis motion-right (+), left (-)
			y = 0; // y-axis motion-forward (+), backward (-)
			z = 0; // z-axis motion-clockwise (+), counterclockwise (-)
			// Gearbox Motor 1 and Motor 2 Code
			/*if (stickTwo.GetRawButton(1)) //neg is up
			{
				gearBoxOne.Set(-1);
				gearBoxTwo.Set(-1);
			}*/
#endif
			if (stickTwo.GetRawButton(1))
			{
				gearBoxOne.Set(-1 * stickTwo.GetY());
				gearBoxTwo.Set(-1 * stickTwo.GetY());
			}
			else
			{
				gearBoxOne.Set(0);
				gearBoxTwo.Set(0);
			}
			// Encoder Reset Code
			if (stickOne.GetRawButton(8) || stickOne.GetRawButton(9))
			{
				leftFrontEncoder.Reset();
				leftBackEncoder.Reset();
				rightFrontEncoder.Reset();
				rightBackEncoder.Reset();
				gyro.Reset();
			}

			SmartDashboard::PutNumber("Preset Status", presetStatus);

			SmartDashboard::PutNumber("LF Encoder Distance", leftFrontEncoder.GetDistance());
			SmartDashboard::PutNumber("LF Encoder Rate", (leftFrontEncoder.GetRate()*60));

			SmartDashboard::PutNumber("LB Encoder Distance", leftBackEncoder.GetDistance());
			SmartDashboard::PutNumber("LB Encoder Rate", (leftBackEncoder.GetRate()*60));

			SmartDashboard::PutNumber("RF Encoder Distance", rightFrontEncoder.GetDistance());
			SmartDashboard::PutNumber("RF Encoder Rate", (rightFrontEncoder.GetRate()*60));

			SmartDashboard::PutNumber("RB Encoder Distance", rightBackEncoder.GetDistance());
			SmartDashboard::PutNumber("RB Encoder Rate", (rightBackEncoder.GetRate()*60));
			SmartDashboard::PutNumber("Gyro: ", gyro.GetAngle());
			SmartDashboard::PutNumber("Ultrasonic: ", sonic.GetValue() / (9.766 * 2));
			SmartDashboard::PutNumber("Accelerometer: ", accelerometer.GetZ());
			Wait(kUpdatePeriod); // Wait 5ms for the next update.
		}
	}
	void Robot::Test()
	{
		double dist = 0;
		double initialAngle = 0;
		double angleChange = 0;
		//double initialAngle = gyro.GetAngle(); // Here for testing etc.
		while (IsTest())
		{
			/*if(stickOne.GetRawButton(6))
			{
				// LIFTING THE TOTE
				while (armEncoder.GetDistance() < 5) // 5 inches off the ground
				{
					setGearBoxMotors(0.75, 0.75);
				}
				setGearBoxMotors(0,0);
			}*/
			if(stickOne.GetRawButton(7))
			{
				ResetEncoders();
				// DRIVING BACKWARDS
				dist = sonic.GetValue() / (9.766 * 2);
				while (fabs(rightFrontEncoder.GetDistance()) < (59) && IsEnabled() && fabs(stickOne.GetY()) < 0.2)// 89.5 inches traveled
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
				//initialAngle = gyro.GetAngle();
			}
			initialAngle = gyro.GetAngle();
			if(stickOne.GetRawButton(8))
			{
				// ROTATING CLOCKWISE
				while (angleChange < 85) // change in rotatation less than 90
				{
					SetRobotDrive(0.5, -0.5,0.5, /*-0.5, 0.5,*/ -0.5); // clockwise rotational movement
					angleChange = fabs(fabs(initialAngle) - fabs(gyro.GetAngle()));
				}
				gyro.Reset();
				angleChange = 0;
				SetRobotDrive(0,0,0,0);
			}
			if(stickOne.GetRawButton(9))
			{
				ResetEncoders();
				// DRIVING BACKWARDS
			while (fabs(rightFrontEncoder.GetDistance()) < 106.95-7.95) // 106.95 inches traveled
			{
				SetRobotDrive(-0.5,-0.5,-0.5,-0.5);
			}
			SetRobotDrive(0,0,0,0);
			ResetEncoders();
			}

			/*if(stickOne.GetRawButton(10))
			{
				// LOWERING THE TOTE IF THERE IS STACKING POTENTIAL
				if (stackingPotential == 1)
				{
					while (armEncoder.GetDistance() < 5) // 5 inches off the ground
					{
						setGearBoxMotors(-0.75, -0.75);
					}
					setGearBoxMotors(0,0);
				}
			}*/
			if(stickOne.GetRawButton(11))
			{/*
				// DRIVING BACKWARDS
				resetEncoders();
				while (fabs(rightFrontEncoder.GetDistance()) < 112.55-6.95)// 89.5 inches traveled
				{
					setRobotDrive(-0.5,-0.5,-0.5,-0.5); // Backwards movement
				}
				setRobotDrive(0,0,0,0);
				resetEncoders();*/
				SetGearBoxMotors(0.35, 0.35);
			}
			else
				SetGearBoxMotors(0, 0);
			SmartDashboard::PutNumber("LF Encoder Distance", leftFrontEncoder.GetDistance());
			SmartDashboard::PutNumber("LF Encoder Rate", (leftFrontEncoder.GetRate()*60));

			SmartDashboard::PutNumber("LB Encoder Distance", leftBackEncoder.GetDistance());
			SmartDashboard::PutNumber("LB Encoder Rate", (leftBackEncoder.GetRate()*60));

			SmartDashboard::PutNumber("RF Encoder Distance", rightFrontEncoder.GetDistance());
			SmartDashboard::PutNumber("RF Encoder Rate", (rightFrontEncoder.GetRate()*60));

			SmartDashboard::PutNumber("RB Encoder Distance", rightBackEncoder.GetDistance());
			SmartDashboard::PutNumber("RB Encoder Rate", (rightBackEncoder.GetRate()*60));
		}
	}
	START_ROBOT_CLASS(Robot);
