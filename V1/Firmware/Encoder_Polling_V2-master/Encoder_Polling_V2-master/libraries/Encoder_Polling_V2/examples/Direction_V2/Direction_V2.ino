
#include "Encoder_Polling_V2.h"

const int pin_A = 5;  // Encoder input pins
const int pin_B = 6;

void setup()
{
  Serial.begin(9600);
  encoder_begin();  // Start the library
  attach_encoder(0, pin_A, pin_B);  // Attach an encoder to pins A and B
  Serial.println("active");
}

void loop()
{
  int dir_0 = encoder_data(0);  // First encoder
  
  if(millis() > 10000)
  {
    dettach_encoder(1);  // After 10 seconds, dettach encoder 1 
  }
  
  if(dir_0 != 0)  // Check for rotation
  {
    Serial.print("Encoder 0: ");
    Serial.println(dir_0);
  }
}
