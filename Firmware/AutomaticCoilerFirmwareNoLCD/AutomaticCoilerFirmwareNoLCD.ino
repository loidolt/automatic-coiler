/****************************************************************************** 
Automatic Coiler Firmware V1
******************************************************************************/
int motor = 2;

//Encoder Pins
// Red - 5V
// Black - GND
const int encoder_a = 4; // Green - pin 2 - Digital
const int encoder_b = 3; // White - pin 3 - Digital
long encoder = 0;

//Buttons
int btnA = 5;
int btnB = 6;
int btnStateA = 0;
int btnStateB = 0;

//Set Distances
int guyline = 960;
int ridgeline = 300;

//Variables
int distance;
int x;
char c;
int count;

void setup(){
  /*Sets all pin to output; the microcontroller will send them(the pins) bits, it will not expect to receive any bits from thiese pins.*/
  pinMode(motor, OUTPUT);

  pinMode(encoder_a, INPUT_PULLUP);
  pinMode(encoder_b, INPUT_PULLUP);

  attachInterrupt(0, encoderPinChangeA, CHANGE);
  attachInterrupt(1, encoderPinChangeB, CHANGE);

  pinMode(btnA, INPUT);
  pinMode(btnB, INPUT);
}
 
void loop(){
  btnStateA = digitalRead(btnA);
  btnStateB = digitalRead(btnB);
      
  if (btnStateA == HIGH)
  { 
    while(distance < guyline)  //Loop the forward stepping until set cord is coiled
    {
      digitalWrite(motor, HIGH);  
      distance = encoder / 492;
    }
  
      digitalWrite(motor, LOW);

      encoder = 0; //empty for next round
      distance = 0; //empty for next round
    }
    else if (btnStateB == HIGH)
    {
      while(distance < ridgeline)  //Loop the forward stepping until set cord is coiled
    {
      digitalWrite(motor, HIGH);  
      distance = encoder / 492;
    }
  
      digitalWrite(motor, LOW);

      encoder = 0; //empty for next round
      distance = 0; //empty for next round
    }
    else
    {
       delay (100); 
    }
    
}

void encoderPinChangeA() {
encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? -1 : 1;
}

void encoderPinChangeB() {
encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? -1 : 1;
}

