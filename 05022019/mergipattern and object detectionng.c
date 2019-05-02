#pragma config(Sensor, S4,     Colour,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S1,     Colour2,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorD,          motorLeft,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorA,          motorRight,    tmotorEV3_Large, PIDControl, encoder)
#pragma config(Sensor, S3,     IRDistance1,    sensorEV3_IRSensor, modeEV3IR_Proximity)
#pragma DebuggerWindows("debugStream")

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int leftmotor = 0;
int rightmotor = 0;

// for wandering
int totalleft= 0;
int totalright = 0;
int difference = 0;


// speed for object detect
int currentDistance = 0;




// Method for going forward
void moveForward() {


	leftmotor = random(90);
	rightmotor = random(90);

	totalleft += leftmotor;
	totalright += rightmotor;
	difference = totalleft - totalright;
	if(difference <= 10000 && difference >= -10000){
		setMotorSpeed(motorLeft, leftmotor);
	  setMotorSpeed(motorRight, rightmotor);
}
	else if(difference > 10000){
        setMotorSpeed(motorLeft, 0);
        setMotorSpeed(motorRight, 100);
        totalleft -= 100;
	} else if(difference < -10000)  {
        setMotorSpeed(motorLeft, 100);
        setMotorSpeed(motorRight, 0);
        totalright -= 100;

 } else{
		setMotorSpeed(motorLeft, 100);
		setMotorSpeed(motorRight, 100);


	}


}



int left = 10;
int right = 10;
int max = 10;

int wheel = 0;

//for color
short rightcurrentColour;
short leftcurrentColour;

bool leftBlack;
bool rightBlack;

task main()
{
	while (true)
	{
		// read distance object censor
		currentDistance = SensorValue[IRDistance1];

		displayCenteredBigTextLine(1, "Dist: %d", currentDistance);

		// color detect
		rightcurrentColour = SensorValue[Colour];
		leftcurrentColour = SensorValue[Colour2];

		displayCenteredBigTextLine(7, " %d", rightcurrentColour);



		if((currentDistance < 1000) && currentDistance > 40){
				setMotorSpeed(motorLeft, currentDistance/10);
				setMotorSpeed(motorRight, currentDistance/10);

	} else if(currentDistance < 40){
		motor[motorLeft] = 0;
			motor[motorRight] = 0;
			sleep(2000);
			motor[motorLeft] = -30;
			motor[motorRight] = 0;
			sleep(1000);

}

else if((SensorValue[Colour] < 20) || ( SensorValue[Colour2] < 20)){
			displayBigTextLine(9 ,"inside statement");
			//playTone(100, true);
			if(SensorValue[Colour] < SensorValue[Colour2]) {
				int difference = (SensorValue[Colour2] - SensorValue[Colour]);
				if(difference > max) {
					difference = max - 3;
				}
				setMotorSpeed(motorLeft, left);
				setMotorSpeed(motorRight, right-difference);
				// displayBigTextLine(
				} else {
				int difference = (SensorValue[Colour] - SensorValue[Colour2]);
				if(difference > max) {
					difference = max - 3;
				}
				//float speedChange = base * ((SensorValue[Colour2] + 1) / (SensorValue[Colour] + 1 + SensorValue[Colour2]));
				setMotorSpeed(motorLeft, left-difference );
				setMotorSpeed(motorRight, right);
			}

			}else{
			setMotorSpeed(motorLeft, left);
			setMotorSpeed(motorRight, right);
			displayBigTextLine(9 ,"not inside statement");
		}
	//
	//else{

//	moveForward();
	//	}
	}
}
