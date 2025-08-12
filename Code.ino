#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

#define sensorPin A0
#define relayPin 11

// Right Motor
int enableRightMotor = 5; 
int rightMotorPin1 = 7;
int rightMotorPin2 = 8;

// Left Motor
int enableLeftMotor = 6;
int leftMotorPin1 = 9;
int leftMotorPin2 = 10;


// Value for storing water level
int val = 0;



void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
	Serial.begin(9600);

  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);
  rotateMotor(0,0);   
    
  Dabble.begin(9600, 2, 3);
}

void loop() {
  int rightMotorSpeed=0;
  int leftMotorSpeed=0;
  

	int level = readSensor();
  

  Dabble.processInput();

      if (GamePad.isUpPressed())
      {
        rightMotorSpeed = 255;
        leftMotorSpeed = 255;
      }
    
      if (GamePad.isDownPressed())
      {
        rightMotorSpeed = -255;
        leftMotorSpeed = -255;
      }
    
      if (GamePad.isLeftPressed())
      {
        rightMotorSpeed = 255;
        leftMotorSpeed = 0;
      }
    
      if (GamePad.isRightPressed())
      {
        rightMotorSpeed = 0;
        leftMotorSpeed = 255;
      }

      if (GamePad.isTrianglePressed())
      {
        digitalWrite(relayPin, HIGH);
      }

      if (GamePad.isCirclePressed())
      {
        digitalWrite(relayPin, LOW);
      }

    
    
      rotateMotor(rightMotorSpeed, leftMotorSpeed);
  
	
	
}



int readSensor() {
	val = analogRead(sensorPin);
	return val;
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed >= 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed >= 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}