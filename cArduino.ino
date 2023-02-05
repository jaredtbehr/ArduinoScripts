#include <TFMPlus.h>
#include <SR04.h>
#include <Servo.h>
#include "IRremote.h"
#include <LiquidCrystal.h>

#define ENABLE 11
#define DIRA 9
#define DIRB 10

Servo myServo;
SR04 ultraSonic = SR04(7,8);

float a;
int receiver = 13;
int iteration = 0;
bool distSensor = false;

LiquidCrystal lcd(41, 39, 37, 35, 33, 31);
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup() 
{
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("cArduino");
  lcd.setCursor(0,2);
  lcd.print("Dist:");
  
  Serial.begin(9600);
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  //pinMode(buttonA, INPUT_PULLUP);  
  //pinMode(buttonB, INPUT_PULLUP); 
  myServo.attach(12);
  myServo.write(90);// move servos to center position -> 90° ## 100° for shitty print
  delay(220);
  myServo.write(155);
  delay(220);
  myServo.write(90);
  delay(220);
  myServo.write(25);
  delay(220);
  myServo.write(90);
  delay(220);
  myServo.write(155);
  delay(220);
  myServo.write(25);
  delay(220);
  myServo.write(90);
  irrecv.enableIRIn();
  Serial.println("\n-----------------------------------------------------------------------------");
  
}

void loop()
{
  
  if( millis() % 500 == 0 )
  {
    if( distSensor == true)
    {
      a = ultraSonic.Distance();
      a /= 2.54;
      lcd.setCursor(6,2);
      lcd.print(a);
      lcd.print(" in ");
    }
  }

  if( millis() % 5000 == 0 )
  {
    lcd.setCursor(0,0);
    lcd.print("cArduino");
    lcd.setCursor(0,2);
    lcd.print("Dist:");
  }
  
  // If IR Signal has been received
  if(irrecv.decode(&results))
  {
    // If Vol- is pressed, turn motor on backward for half second and document
    if(results.value == 0xFFA857)
    {
      Serial.println("Motor turned on - backward");
      digitalWrite(ENABLE,HIGH); //enable on
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
      delay(500);
      digitalWrite(ENABLE,LOW);

      
      Serial.print("\tOperation Code:");
      Serial.print(results.value);
      Serial.print(". #");
      Serial.println(iteration);
      Serial.println();

      iteration++;
      irrecv.resume();
    }
    // If Vol+ is pressed, turn motor on forwards for half second and document
    else if( (results.value == 0xFF629D)  )
    {
      Serial.println("Motor turned on - forward");
      digitalWrite(ENABLE,HIGH); //enable on
      digitalWrite(DIRA,LOW); //one way
      digitalWrite(DIRB,HIGH);
      delay(500);
      digitalWrite(ENABLE,LOW);


      Serial.print("\tOperation Code:");
      Serial.print(results.value);
      Serial.print(". #");
      Serial.println(iteration);
      Serial.println();
      
      iteration++;
      irrecv.resume();
    }
    // If Fast-Back is pressed, Steer wheels to the left and document
    else if(results.value == 0xFF22DD)
    {
      Serial.println("Servo turned Left");
      myServo.write(155);

      Serial.print("\tOperation Code:");
      Serial.print(results.value);
      Serial.print(". #");
      Serial.println(iteration);
      Serial.println();

      iteration++;
      irrecv.resume();
    }
    // If Fast-Forward is pressed, Steer wheels to the right and document
    else if(results.value == 0xFFC23D)
    {
      Serial.println("Servo turned Right");
      myServo.write(25);

      Serial.print("\tOperation Code:");
      Serial.print(results.value);
      Serial.print(". #");
      Serial.println(iteration);
      Serial.println();

      iteration++;
      irrecv.resume();
    }
    // If Play/Pause is pressed, Steer wheels center and document
    else if(results.value == 0xFF02FD)
    {
      Serial.println("Servo turned center");
      myServo.write(90);
      digitalWrite(ENABLE,LOW);

      Serial.print("\tOperation Code:");
      Serial.print(results.value);
      Serial.print(". #");
      Serial.println(iteration);
      Serial.println();

      iteration++;
      irrecv.resume();
    }
    // If Func/Stop is pressed, Record distance from car and document on LCD
    else if(results.value == 0xFFE21D)
    {
      Serial.println("Distance sensor triggered");

      Serial.print("\tOperation Code:");
      Serial.print(results.value);
      Serial.print(". #");
      Serial.println(iteration);
      Serial.println();

      if( distSensor )
      {
        distSensor = false;
      }
      else
      {
        distSensor = true;
      }

      iteration++;
      irrecv.resume();      
    }
    // If other button pressed, resume IR receive protocol
    else
    {
      irrecv.resume();
      Serial.print("Unused IR Signal: ");
      Serial.println(results.value);     
    }
  }
  
}
