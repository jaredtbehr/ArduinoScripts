#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <GamePadModule.h>
#include <Dabble.h>
int ENABLE = 11;   //These are the pins for our motor driver IC
int DIRA = 9;
int DIRB = 10;


void setup() 
{
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT); 
  pinMode(DIRB, OUTPUT);

  Serial.begin(250000);    // Set your Serial Monitor is set at 250000
  Dabble.begin(9600);      // This is the baude rate of the HM-10
}

void loop() {
Dabble.processInput();  // This line is crucial in grabbing our data  
  
  if (GamePad.isUpPressed())       
  {
    Serial.println("Forward");
    delay(1000);
    analogWrite(ENABLE, 255);
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
  }

  else if (GamePad.isDownPressed())
  {
    Serial.println("Backward");
    delay(1000);
    analogWrite(ENABLE, 255);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
  }

  else if (GamePad.isLeftPressed())
  {
    Serial.println("Left");
    delay(1000);
  }

  else if (GamePad.isRightPressed())
  {
    Serial.println("Right");
    delay(1000);
  }
  else 
  {
    Serial.println("Stopped");
    analogWrite(ENABLE, 0);
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
  }
}