#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//------------- Constants ---------------------
int kBlue = 45;
int kRed  = 30;
int kGrey = 78;
int kWhite = 89;

long kLowRackPos = 600;
long kMidRackPos = 2000;
long kHighRackPos = 2800;
long armPosition = kLowRackPos;

//------------- Globals -----------------------
//for user feedback
long reading;
long readingHead;

//------------- Function Declarations ---------
void resetDriveEncoders();
void initializeRobot();
void leftSide(int power);
void rightSide(int power);
void stopDriving();
void driveForwardSpeed(int speed);
void driveForwardTime(int speed, int time);
void driveForwardToLine(int speed, int lightVal);
void driveForwardEncoder(int speed, long ticks);
void driveForwardSonar(int speed, int dist);
void driveBackwardSpeed(int speed);
void driveBackwardEncoder(int speed, long ticks);
void turnLeftSpeed(int speed);
void turnRightSpeed(int speed);
void turnLeftGyro(int speed, int heading);
void turnRightGyro(int speed, int heading);

void closeGripper();
void openGripper();
task gripperUp();
task liftArm();
task lowerArm();
task readSonar();





task main() {
  initializeRobot();
	StartTask(gripperUp);

	armPosition = kLowRackPos;
	StartTask(liftArm);
	//------------------ Score on left Bonus Peg -----------------------------
	turnLeftGyro(100, -415);
	driveForwardEncoder(100, (6*1440) );	//drive close to the center white line
	turnRightGyro(100, 0);
	driveForwardEncoder(100, 1440);
	openGripper();
	driveBackwardEncoder(100, 1440);
	closeGripper();
	turnLeftGyro(100, -415);
  driveForwardEncoder(100, 6*1440);
	driveForwardToLine(50, kWhite);				//detect the center white line

	turnLeftGyro(100, -950);
	driveForwardSonar(100, 3);		//drive forward to the wall
	openGripper();
	driveForwardTime(100, 750);			//ram the wall for auto-alignment
/*//------------------- Score on Left Bonus Peg x2 -------------------------
	driveBackwardEncoder(100, 1440);
	closeGripper();
	turnLeftGyro(100, -1300);
	driveBackwardEncoder(100, 5.5*1440);
	driveForwardEncoder(100, 5*1440);
	driveForwardToLine(50, kWhite);

	turnRightGyro(100, -950);
	driveForwardSonar(100, 3);
	openGripper();
	driveForwardTime(100, 750);
*/
	//------------------- Score on right Bonus peg ---------------------------
	driveBackwardEncoder(100, 1440);			//align and drive to next reload station
	closeGripper();
	turnLeftGyro(100, -1100);
	driveBackwardEncoder(100, (15*1440));

	turnLeftGyro(100, -2200);									//align and drive to white line TODO Add distance failsafe: if over distance, turn slightly and back up
	driveForwardEncoder(100, (4.5*1440));
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -2750);				//score ring on bonus peg
	driveForwardSonar(100, 3);
	openGripper();
	driveForwardTime(100, 500);
/*//-------------------- Score on right Bonus Peg x2 -----------------------
	driveBackwardEncoder(100, 1440);
	closeGripper();
	turnRightGyro(100, -2200);
	driveBackwardEncoder(100, 5.75*1440);
	driveForwardEncoder(100, 5*1440);
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -2750);
	driveForwardSonar(100, 3);
	openGripper();
	driveForwardTime(100, 500);
*/
	//-------------------- Score on low peg 1 --------------------------------
	driveBackwardEncoder(100, 1440);		//align robot and drive to next reload station
	closeGripper();
	turnLeftGyro(100, -3100);
	driveBackwardEncoder(100, (5.5*1440));

	turnLeftGyro(100, -3800);								//align and drive to Centerline
	driveForwardEncoder(100, (3*1440));
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -4500);		//align and drive to low center rack
	driveForwardEncoder(100, (2*1440));
	openGripper();

  //-------------------- Score on low peg 2 --------------------------------
	driveBackwardEncoder(100, 1440);	//align and drive to next reload station
	closeGripper();
	turnLeftGyro(100, -5200);
	driveBackwardEncoder(100, (5*1440));

	turnRightGyro(100, -4850);             //align and drive to center line
	driveForwardEncoder(100, (6.5*1440));
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -6200);             //align and drive to low center rack
	driveForwardEncoder(100, (0.75*1440));
	openGripper();

	//-------------------- Score on mid peg 2 --------------------------------
	driveBackwardEncoder(100, 1440);  //align and drive to next reload station
	closeGripper();
	turnRightGyro(100, -5700);
	driveBackwardEncoder(100, (4.75*1440));
	armPosition = kMidRackPos;
	StartTask(liftArm);

	driveForwardEncoder(100, (3*1440)); //align and drive to centerLine
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -6350);               //align and drive to mid 2 center rack
	driveForwardEncoder(100, (1.5*1440));
	openGripper();

  //-------------------- Score on high peg 2 --------------------------------
	driveBackwardEncoder(100, (1.5*1440));    //align and drive to next reload station
	closeGripper();
	turnRightGyro(100, -5700);
	driveBackwardEncoder(100, (5.5*1400));
	armPosition = kHighRackPos;
	StartTask(liftArm);

	driveForwardEncoder(100, (3*1440)); //align and drive to centerline
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -6350);               //align and drive to high 2 center rack
	driveForwardEncoder(100, (1.5*1400));
	openGripper();

	//-------------------- Score on high peg 1 --------------------------------
	driveBackwardEncoder(100, 1440);    //align and drive to next reload station
	closeGripper();
	turnLeftGyro(100, -6950);
	driveBackwardEncoder(100, (6*1440));

	turnRightGyro(60, -6650);               //align and drive to centerline
	driveForwardEncoder(100, (8*1440));
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -8050);               //align and drive to high 1 center rack
	driveForwardEncoder(100, (1.5*1440));
	openGripper();

	//-------------------- Score on mid peg 1 --------------------------------
	driveBackwardEncoder(100, (1.5*1440));  //align and drive to next Reload Station
	closeGripper();
	turnRightGyro(100, -7600);
	driveBackwardEncoder(100, (4.5*1440));
	armPosition = kMidRackPos;
	StartTask(lowerArm);

	driveForwardEncoder(100, (3*1440));   //align and drive to centerline
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -8100);
	driveForwardEncoder(100, (1.25*1440));   //align and drive to mid 1 center rack
	openGripper();

	//-------------------- Score on mid peg 1 x2 -----------------------------
	driveBackwardEncoder(100, 1.5*1440);
	closeGripper();
	turnRightGyro(100, -7600);
	driveBackwardEncoder(100, 4.75*1440);

	driveForwardEncoder(100, 3*1440);
	driveForwardToLine(50, kWhite);

	turnLeftGyro(100, -8100);
	driveForwardEncoder(100, 1.25*1400);
	openGripper();
	driveBackwardEncoder(100, 1440);


	stopDriving();
	wait1Msec(30000);

}





//------------- Function Definitions -----------
void resetDriveEncoders() {
  nMotorEncoder[motorF] = 0;
	nMotorEncoder[motorG] = 0;
}

void initializeRobot() {
	nMotorEncoder[motorH] = 0;
	nMotorEncoder[motorB] = 0;

	motor[motorA] = 100;			//closes the gripper
	wait1Msec(250);						//and sets position 0
	motor[motorA] = 0;				//to closed
	nMotorEncoder[motorA] = 0;
}

void leftSide(int power) {
  motor[motorE] = power;
  motor[motorG] = power;
}

void rightSide(int power) {
  motor[motorD] = power;
  motor[motorF] = power;
}

void stopDriving() {
	leftSide(0);
	rightSide(0);
}

void driveForwardSpeed(int speed) {
	leftSide(speed);
	rightSide(speed);
}

void driveForwardTime(int speed, int time) {
  driveForwardSpeed(speed);
  wait1Msec(time);
  stopDriving();
}

void driveForwardToLine(int speed, int lightVal) {
	driveForwardSpeed(speed);

	while( SensorValue[lightSensor] < lightVal ) {
		wait1Msec(50);					//continously check sensor
	}													//reading until light value is reached
	stopDriving();
}

void driveForwardEncoder(int speed, long ticks) {
	resetDriveEncoders();
	driveForwardSpeed(speed);

	while( (nMotorEncoder[motorF] < ticks) || (nMotorEncoder[motorG] > -ticks) ) {
		wait1Msec(10);
	}
	stopDriving();
}

void driveForwardSonar(int speed, int dist) {
	driveForwardSpeed(speed);

	while( SensorValue[sonarSensor] > dist ) {
		reading = SensorValue[sonarSensor];
		wait1Msec(10);
	}
	stopDriving();
}

void driveBackwardSpeed(int speed) {
	motor[motorD] = -speed;
	motor[motorF] = -speed;
	motor[motorE] = -speed;
	motor[motorG] = -speed;
}

void driveBackwardEncoder(int speed, long ticks) {
	resetDriveEncoders();
	driveBackwardSpeed(speed);

	while( (nMotorEncoder[motorF] > -ticks) || (nMotorEncoder[motorG] < ticks) ) {
		reading = nMotorEncoder[motorG];
		wait1Msec(10);
	}
	stopDriving();
}

void turnLeftSpeed(int speed) {
  leftSide(-speed);
  rightSide(speed);
}

void turnRightSpeed(int speed) {
  leftSide(speed);
  rightSide(-speed);
}

void turnLeftGyro(int speed, int heading) {
  while (SensorValue[Gyro] > heading) { //turns to the heading at
    turnLeftSpeed(speed);               //high speed to get an approximate heading
  }
  while (SensorValue[Gyro] < heading) { //turn back to the heading
    turnRightSpeed(speed/5);            //at a slower speed for a finer heading
  }
  stopDriving();
  readingHead = SensorValue[Gyro];
}

void turnRightGyro(int speed, int heading) {
  while (SensorValue[Gyro] < heading) {
    turnRightSpeed(speed);
  }
  while (SensorValue[Gyro] > heading) {
    turnLeftSpeed(speed/5);
  }
  stopDriving();
  readingHead = SensorValue[Gyro];
}

void turnGyro(int speed, int heading) {
	int largeThreshold = 45;		//stair stepped threshold values
	int threshold = 0.5;				//large threshold for a general heading range, and then a threshold for fine tuning

	while( abs(heading-SensorValue[Gyro]) > threshold ) {	//loop until within smaller threshold
		if( abs(heading-SensorValue[Gyro]) > largeThreshold ) { //Drive fast in the large threshold
			if ( (heading-SensorValue[Gyro]) > 0 ) {
				turnRightSpeed(speed);
			}
			else {
				turnLeftSpeed(speed);
			}
		}
		else {
			if ( (heading-SensorValue[Gyro]) > 0 ) {	//drive at 1/2 speed when within larger threshold
			turnRightSpeed(speed/7);												//for fine tuning of heading
			}
			else {
				turnLeftSpeed(speed/7);
			}
		}
		reading = SensorValue[Gyro];
	}
	stopDriving();
}

void closeGripper() {
	while( nMotorEncoder[motorA] < -20 ) {	//closes the 		TODO: add timeout
		motor[motorA] = 100;									//gripper to a
	}																				//set position
	motor[motorA] = 0;
}

void openGripper() {
	while( nMotorEncoder[motorA] > -40 ) {	//opens the 		TODO: add timeout
		motor[motorA] = -100;									//gripper to a
	}																				//set position
	motor[motorA] = 0;
}
task gripperUp() {
  nMotorEncoder(motorB) = 0;

  motor[motorB] = 100;  //move motor outside of sticking point
  wait1Msec(100);
  motor[motorB] = 0;

  motor[motorB] = 50;   //move motor to specified up position
  while (nMotorEncoder[motorB] < 150) {
    reading = nMotorEncoder[motorB];
  }
  motor[motorB] = 0;
  StopTask(gripperUp);
}

task liftArm() {
  motor[motorH] = 50;
	while (nMotorEncoder[motorH] < armPosition) {
	  reading = nMotorEncoder[motorH];
	}
	motor[motorH] = 0;
	StopTask(liftArm);
}

task lowerArm() {
  motor[motorH] = -50;
  while (nMotorEncoder[motorH] > armPosition) {
  }
  motor[motorH] = 0;
  StopTask(lowerArm);
}

task readSonar() {
	while(true) {
		reading = SensorValue[sonarSensor];
		wait1Msec(50);
	}
}
