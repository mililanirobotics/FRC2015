#include "WPILib.h"
#include "Math.h"
class Robot : public SampleRobot {
		Talon leftFront; // Initializing motor 1; front-left motor
		Talon leftBack; // Initializing motor 3; back-left motor
		Talon rightFront;// Initializing motor 2; front-right motor
		Talon rightBack; // Initializing motor 4; back-right motor
		Talon gearBoxOne;
		Talon gearBoxTwo;
		Encoder leftFrontEncoder;
		Encoder leftBackEncoder;
		Encoder rightFrontEncoder;
		Encoder rightBackEncoder;
		Encoder armEncoder;
	    Joystick stickOne; // Logitech Gamepad Controller
	    Joystick stickTwo; // Logitech Gamepad Controller
	    Gyro gyro;
	    AnalogInput sonic;
	    BuiltInAccelerometer accelerometer;
	    double kUpdatePeriod = 0.01;
	    double autonomousLeftFrontCalibration = 1;
	    double autonomousLeftBackCalibration = 1;
	    double autonomousrightFrontCalibration = -1;
	    double autonomousrightBackCalibration = -1;
	    const static int stackingPotential = 1; // HEY DRIVERS (1 = ALLIANCE CAN STACK YELLOW TOTES DURING AUTONOMOUS), (0 = ALLIANCE CAN'T STACK)
	    double dist = 0;
		double initialAngle = 0;
		double angleChange = 0;
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

public:
	Robot(); // Runner file

	// CRITICAL FUNCTIONS
	void SetGearBoxMotors(double gearBoxOneSpeed, double gearBoxTwoSpeed);
	void SetRobotDrive(double leftFrontSpeed, double rightFrontSpeed, double leftBackSpeed, double rightBackSpeed);
	void ResetEncoders();
	double EncoderDistance();

	// AUTONOMOUS FUNCTIONS
	void Autonomous();
	void MainRobotLeftTote();
	void MainMiddleTote();

	// TELEOP FUNCTIONS
	void OperatorControl();
	void MecanumFBTurn();

	// TEST FUNCTIONS
	void Test();
};
