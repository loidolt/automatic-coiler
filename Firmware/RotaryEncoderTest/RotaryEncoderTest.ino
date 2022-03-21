// Red - 5V
// Black - GND
const int encoder_a = 2; // Green - pin 2 - Digital
const int encoder_b = 3; // White - pin 3 - Digital
long encoder = 0;

const float wheelPerimeter = 200; //mm
const int pulsesPerRev = 200;
float distancePerPulse;

int distance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(encoder_a, INPUT_PULLUP);
  pinMode(encoder_b, INPUT_PULLUP);
  
  attachInterrupt(0, encoderPinChangeA, RISING);
  
  //Calculate encoder distance per pulse
  distancePerPulse = wheelPerimeter / pulsesPerRev;
}

void loop() {
  calcDistance();
}

void calcDistance()
{
  distance = encoder * distancePerPulse;
  Serial.println(distance);
}

void encoderPinChangeA() {
  if(digitalRead(encoder_b) == LOW) {
    encoder++;
  } else{
    encoder--;
  }
}
