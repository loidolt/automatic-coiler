/****************************************************************************** 
Automatic Coiler Firmware V1
******************************************************************************/
#include <LiquidCrystal.h>

int motor = 2;

//Encoder Pins
// Red - 5V
// Black - GND
const int encoder_a = 4; // Green - pin 2 - Digital
const int encoder_b = 3; // White - pin 3 - Digital
long encoder = 0;

//Buttons
int enter = A1;
int back = A2;
int next = A3;

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
  Serial.println("Choose Option:");
  Serial.println();
  lcd.print("Enter length");
}
 
void loop(){
  
  while(Serial.available()){
      user_input = Serial.parseInt(); //read int or parseFloat for ..float...
      
      Serial.println(user_input);
      Serial.println();
      
      if (user_input = 1)
      { 
        CustomLength();
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

void CustomLength()
{ 
  Serial.println("Enter length:");
  Serial.println();
  lcd.print("Enter length");

  while(Serial.available()){
      user_input = 0; //empty for next input
      
      user_input = Serial.parseInt(); //read int or parseFloat for ..float...
      
      Serial.println(user_input);
      Serial.println();

      if (user_input >= 1)
      {
        user_input = 0; //empty for next input
        
        user_input = Serial.parseInt(); //read int or parseFloat for ..float...
      
        Serial.println(user_input);
        Serial.println();
        
        Serial.print("Winding ");
        Serial.print(user_input);
        Serial.println(" in");
        Serial.println();
        lcd.clear();
        lcd.print("Winding ");
        lcd.print(user_input);
        lcd.print(" in");
  
        while(distance < user_input)
        {
          digitalWrite(motor, HIGH);
          distance = encoder / 600;
        }
  
        digitalWrite(motor, LOW);

        user_input = 0; //empty for next input
        encoder = 0; //empty for next round
        distance = 0; //empty for next round
        Serial.println("Enter new distance");
        Serial.println();
        lcd.clear();
        lcd.print("Enter next");
      }
      else
      {
        Serial.println("Invalid Number");
      }
  }
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
  
  digitalWrite(motor, LOW);

  user_input = 0; //empty for next input
  encoder = 0; //empty for next round
  distance = 0; //empty for next round
  Serial.println("Done");
  Serial.println();
}

void encoderPinChangeA() {
encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? -1 : 1;
}

void encoderPinChangeB() {
encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? -1 : 1;
}

