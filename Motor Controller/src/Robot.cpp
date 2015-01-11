#include "WPILib.h"

/**
 * Encoder Test Using Motor
 */
class Robot : public SampleRobot {
	Encoder encoder;
	Joystick logitech;
	Talon talon;

	// update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;
	double wheelRadius = 3; // Wheel radius in inches

public:
	Robot() :
			encoder(1, 2, false, Encoder::k4X),
			logitech(0), // Initialize logitech on port 0.
			talon(0) // Initialize the Talon on channel 0.
	{
		encoder.SetSamplesToAverage(5);
		//encoder.SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * wheelRadius);
		//encoder.SetDistancePerPulse(1);
		encoder.SetDistancePerPulse(1.0/360);
		encoder.SetMinRate(1.0);
		// Getrate is distance/second
	}
	void OperatorControl()
	{
		encoder.Reset();
		while (IsOperatorControl() && IsEnabled())
		{
			talon.Set(logitech.GetY()); //gets the y-axis on the LEFT logitech
			while(encoder.GetDistance() < 2)
			{
				talon.Set(-0.2);
			}
#if 0
			if (logitech.GetRawButton(5) == 1) // Left top
			{
				talon.Set(0.1);
				Wait(5);
			}
			else if (logitech.GetRawButton(7) == 1) // Left bottom
			{
				talon.Set(0.2);
				Wait(5);
			}
			else if (logitech.GetRawButton(6) == 1) // Right top
			{
				talon.Set(0.3);
				Wait(5);
			}

			else if (logitech.GetRawButton(8) == 1) // Right bottom
			{
				talon.Set(0.4);
				Wait(5);
			}

			else if (logitech.GetRawButton(9) == 1) // Back button
			{
				talon.Set(0.5);
				Wait(5);
			}
#endif
			talon.Set(0.0);
			SmartDashboard::PutNumber("Encoder Distance", encoder.GetDistance()); // prints displacement in inches
			SmartDashboard::PutNumber("Encoder Rate", encoder.GetRate());
			//SmartDashboard::PutString("DB/String 0", "String 1 Test");
			//SmartDashboard::PutString("DB/String 1", "Is this working?");
			//SmartDashboard::PutString("DB/String 2", "Is this working?");
			//std::string dashData = SmartDashboard::GetString("DB/String 0", "myDefaultData");
			//SmartDashboard::
			Wait(kUpdatePeriod);
		}
	}
	/*
	void Test()
	{
		while (IsTest)
		{
			if (logitech.GetRawButton(5) == 1) // Left top
			{
				talon.Set(0.1);
				Wait(5);
			}
			if (logitech.GetRawButton(7) == 1) // Left bottom
			{
				talon.Set(0.2);
				Wait(5);
			}
			if (logitech.GetRawButton(6) == 1) // Right top
			{
				talon.Set(0.3);
				Wait(5);
			}

			if (logitech.GetRawButton(8) == 1) // Right bottom
			{
				talon.Set(0.4);
				Wait(5);
			}

			if (logitech.GetRawButton(9) == 1) // Back button
			{
				talon.Set(0.5);
				Wait(5);
			}
			if (logitech.GetRawButton(3))
			{
				talon.Set(0);
			}
			SmartDashboard::PutNumber("Encoder Distance", encoder.GetDistance()); // prints displacement in inches
			SmartDashboard::PutNumber("Encoder Rate", encoder.GetRate());
			Wait(kUpdatePeriod);
		}
	}*/
};

START_ROBOT_CLASS(Robot);
