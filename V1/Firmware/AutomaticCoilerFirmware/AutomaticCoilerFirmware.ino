/****************************************************************************** 
Automatic Coiler Firmware V1
******************************************************************************/
#include <LiquidCrystal.h>

//Stepper Pins
int motor = 2; //Direction pin

//Encoder Pins
const int encoder_a = A4; // Green - pin 11 - Digital
const int encoder_b = A5; // White - pin 12 - Digital 
volatile int encoder = 0; // Variable for reading the encoder status

//Buttons
int enter = 2;
int back = 4;
int next = 3;

//Set Distances
int guyline = 80;


//Variables
int user_input;
int distance;
int x;
char c;
int count;

LiquidCrystal lcd(5, 6, 10, 9, 8, 7);

void setup(){
  /*Sets all pin to output; the microcontroller will send them(the pins) bits, it will not expect to receive any bits from thiese pins.*/
  pinMode(motor, OUTPUT);

  pinMode(encoder_a, INPUT_PULLUP);
  pinMode(encoder_b, INPUT_PULLUP);

  attachInterrupt(0, encoderPinChangeA, CHANGE);
  attachInterrupt(1, encoderPinChangeB, CHANGE);

  pinMode(enter, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(next, INPUT_PULLUP);

  lcd.begin(16,2);
 
  Serial.begin(9600); 

   //Print function list for user selection
  Serial.println("Enter distance:");
  Serial.println();
  lcd.print("Enter length");
}
 
void loop(){
  Serial.println(encoder);
  
  while(Serial.available()){
      user_input = Serial.parseInt(); //read int or parseFloat for ..float...
      
      Serial.println(user_input);
      Serial.println();
      
      if (user_input >=1)
      { 
        MovementOne();
      }
      else if (user_input = 2)
      {
        GuyLine();
      }
      else
      {
        Serial.println("Invalid Number");
      }
  }
}

void MovementOne()
{ 
  Serial.print("Winding ");
  Serial.print(user_input);
  Serial.println(" in");
  Serial.println();
  lcd.clear();
  lcd.print("Winding ");
  lcd.print(user_input);
  lcd.print(" in");
  
  for(x= 1; x < user_input ; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(motor, HIGH);
  }

  user_input=0; //empty for next input
  Serial.println("Enter new distance");
  Serial.println();
  lcd.clear();
  lcd.print("Enter next");
}

void GuyLine()
{ 
  Serial.print("Coiling guyline cord section");
  Serial.println();
  
  while(distance < guyline)  //Loop the forward stepping until set cord is coiled
  {
    digitalWrite(motor, HIGH);  
    distance = encoder / 600;
  }

  encoder = 0; //empty for next round
  Serial.println("Done");
  Serial.println();
}

void encoderPinChangeA() {
encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? -1 : 1;
}

void encoderPinChangeB() {
encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? -1 : 1;
}

