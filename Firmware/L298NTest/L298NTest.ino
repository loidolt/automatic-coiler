/*  Arduino DC Motor Control - PWM | H-Bridge | L298N 
 *  TEST
*/
#define enA 6
#define in1 5
#define in2 4
int speedPWM = 0;
int minPWM = 130;

bool CWRotation = true;
int acceleration = 5;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  speedPWM = minPWM;
}
void loop() {

  if (CWRotation == true) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(20);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(20);
  }

  while (speedPWM < 255) {

    analogWrite(enA, speedPWM); // Send PWM signal to L298N Enable pin

    speedPWM = speedPWM + acceleration;

    delay(100);
    
  }

  analogWrite(enA, 255); // Send PWM signal to L298N Enable pin

  delay (2000);

  while (speedPWM > minPWM) {

    analogWrite(enA, speedPWM); // Send PWM signal to L298N Enable pin

    speedPWM = speedPWM - acceleration;
    
    delay(100);
    
  }

  speedPWM = minPWM;

  CWRotation = !CWRotation;

  analogWrite(enA, 0); // Send PWM signal to L298N Enable pin

  delay(500);
  
}
