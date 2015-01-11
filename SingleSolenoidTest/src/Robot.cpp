#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	Joystick stick; // only joystick
	Compressor compressor;
	Solenoid piston;
public:
	Robot() :
			stick(0), //the joystick is in the first USB port
			compressor(0),
			piston(0)
	{
		compressor.SetClosedLoopControl(true);
	}
	void Autonomous()
	{
		while(IsAutonomous())
		{
			//do stuff
		}
	}

	void OperatorControl()
	{
		compressor.Start();
		while (IsOperatorControl())
		{
			if(stick.GetRawButton(6)) //press the upper right trigger
			{
				piston.Set(true);
			}
			else if(stick.GetRawButton(8)) //press the lower right trigger
			{
				piston.Set(false);
			}
		}
		compressor.Stop();
	}
	void Test()
	{
		while(IsTest())
		{
			//do stuff
		}
	}
};

START_ROBOT_CLASS(Robot);
