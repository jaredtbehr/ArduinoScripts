#define ENABLE 5
#define DIRA 3
#define DIRB 4
//#define buttonA 8
//#define buttonB 9

#include <Servo.h>
#include "IRremote.h"
Servo myservo;

int i;
int receiver = 11;
int iteration = 0;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup() 
{
  Serial.begin(9600);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  //pinMode(buttonA, INPUT_PULLUP);  
  //pinMode(buttonB, INPUT_PULLUP); 
  myservo.attach(10);
  myservo.write(90);// move servos to center position -> 90°
  irrecv.enableIRIn();
  Serial.println("-----------------------------------------------------------------------------");
}

void loop()
{

  // if (digitalRead(buttonA) == LOW)
  // {
  //   // Motor Test Code (Forward)
  //   digitalWrite(ENABLE,255); //enable on
  //   digitalWrite(DIRA,HIGH); //one way
  //   digitalWrite(DIRB,LOW);
  // }
  // else if (digitalRead(buttonB) == LOW)
  // {
  //   // Motor Test Code (Reverse)
  //   // digitalWrite(ENABLE,255); //enable on
  //   // digitalWrite(DIRA,HIGH); //one way
  //   // digitalWrite(DIRB,LOW);

  //   // Servo Test Code
  //   myservo.write(0);
  //   delay(1000);
  //   myservo.write(180);
  //   delay(1000);
  //   myservo.write(90);
  // }
  // else
  // {
  //   // Stop Motor
  //   digitalWrite(ENABLE,LOW);
  //   digitalWrite(DIRA,LOW); //one way
  //   digitalWrite(DIRB,LOW);
  // }

  if(irrecv.decode(&results))
  {
    Serial.println("IR Signal Received...");
    if(results.value == 0xFFA857)
    {
      Serial.println("Motor turned on");
      digitalWrite(ENABLE,255); //enable on
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
      delay(500);
      digitalWrite(ENABLE,LOW);
    }
    else if(results.value == 0xFF629D)
    {
      Serial.println("Motor turned on");
      digitalWrite(ENABLE,255); //enable on
      digitalWrite(DIRA,LOW); //one way
      digitalWrite(DIRB,HIGH);
      delay(500);
      digitalWrite(ENABLE,LOW);
    }
    else if(results.value == 0xFFC23D)
    {
      Serial.println("Servo turned right");
      myservo.write(130);
    }
    else if(results.value == 0xFF22DD)
    {
      Serial.println("Servo turned left");
      myservo.write(60);
    }
    else if(results.value == 0xFF02FD)
    {
      Serial.println("Servo turned center");
      myservo.write(100);
      digitalWrite(ENABLE,LOW);
      //digitalWrite(DIRA,LOW); //one way
      //digitalWrite(DIRB,LOW);
    }
    Serial.print("\tOperation Code:");
    Serial.print(results.value);
    Serial.println(". IR Resume.");
    Serial.println();
    iteration++;
    irrecv.resume();
  }

}
