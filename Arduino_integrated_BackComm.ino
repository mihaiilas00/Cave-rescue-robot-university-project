#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <math.h>
#include <SPI.h>
#include <WiFiNINA.h>


#include "declarations.h" // Remember to declare any new functions in "declarations.h"


// initialise all the global variables
void initialise()
{
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	length_robot = 50;
	minimum_grabber = 2000; minimum_robot = 2000;
  triage_x=100, triage_y=200;                          //CHANGE!!!
  finish_x=100, finish_y=200;                          //CHANGE!!!
	turning_point1_x = 70; turning_point1_y = 282; // Table 2
	// turning_point2_x = 499; turning_point2_y = 225; // Table 3
	K1 = 0.2; K2 = 0.5; K3 = 1; // K1 for rotation, K2 for straight moment, K3 for straight movement through tunnel
	turning_time = 6600;
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
  Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
  Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);
	AFMS.begin();

	int status = WL_IDLE_STATUS;
	WiFiServer server(23); // This is the specified port number for telnet communications

	pinMode(9, OUTPUT);		 // set the LED pin mode
	pinMode(8, OUTPUT);		 // set the LED pin mode
	pinMode(7, OUTPUT);		 // set the LED pin mode
}


void setup()
{
	
	initialise();
	digitalWrite(7, LOW);
	digitalWrite(8, LOW);
	digitalWrite(9, LOW);
	setup_wifi();
	digitalWrite(8, HIGH);
}

void
dumpcoordinates()
{
	Serial.print("\n");
	for (int i = 0; i < DATAQUANTITY ; i++)
	{
		Serial.print(coordinates[i]);
		Serial.print(", ");
	}
	Serial.print(">>>\n\n");
}

void assign_coordinates()
{
	robot_x = coordinates[0];
	robot_y = coordinates[1];
	grabber_x = coordinates[2];
	grabber_y = coordinates[3];
	for (int j = 0; j < 4; j++)
	{
		victim[j][0] = coordinates[4 + 2 * j];
		victim[j][1] = coordinates[4 + 2 * j + 1];
	}
}

void loop()
{
	Serial.print(sizeof(int));
  	
	wifi_loop();
	Serial.print("First wifi loop done");
	assign_coordinates();
	//digitalWrite(8, LOW);
//	enter_tunnel();
///delay(2000);
	//digitalWrite(8, HIGH);
	//requestUpdate("well hello");

//	Serial.println("returned");
//	requestUpdate("got it");
//
//	assign_coordinates();
//
//	Serial.print("Corrdinates are:");
//	for (int i = 0; i < 12; i++)
//	{
//		Serial.print(coordinates[i]);
//	}
//
	if (length_flag == 0 && validcoordinates) //measure the length of the robot only once
	{
		length_robot = sqrt(sq(grabber_x - robot_x) + sq(grabber_y - robot_y));
		length_flag = 1;
	}
//
	if (tunnel_flag == 0)								 //enter tunnel if not done alreay
	{
		enter_tunnel(turning_point1_x, turning_point1_y, tunnel1_x, tunnel1_y);
		tunnel_flag = 1;
	}
	else																//search victims one by one
	{
		search_victim();
	}
  
}
