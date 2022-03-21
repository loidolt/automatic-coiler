//Automatic Coiler V3
//Chris Loidolt
//03/15/2022

#include <LiquidCrystal.h>

//LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
unsigned long previousMillis = 0; // will store last time LCD was updated
const long updateInterval = 200; // interval at which to update LCD while running job (milliseconds)

//Define Various Menu Variables used throughout
int timer = 0;
byte totalRows = 2;              // total rows of LCD
byte totalCols = 16;             // total columns of LCD
int returndata = 0;              // Used for return of button presses
unsigned long timeoutTime = 0;   // this is set and compared to millis to see when the user last did something.
const int menuTimeout = 20000;   // time to timeout in a menu when user doesn't do anything.
unsigned long lastButtonPressed; // this is when the last button was pressed. It's used to debounce.
const int debounceTime = 150;    // this is the debounce and hold delay. Otherwise, you will FLY through the menu by touching the button.

const int buttonUp = A5;     // Set pin for UP Button
const int buttonSelect = A4; // Set pin for SLELECT Button
const int buttonDown = A3;   // Set pin for DOWN Button

int buttonStateUp = 0; // Initalise ButtonStates
int buttonStateDown = 0;
int buttonState;

// constants for indicating whether cursor should be redrawn
#define MOVECURSOR 1
// constants for indicating whether cursor should be redrawn
#define MOVELIST 2

//Encoder
const int encoder_a = 2; // Green (Red - 5v, Black - GND)
const int encoder_b = 3; // White
long encoder = 0;
const float wheelPerimeter = 200; //mm
const int pulsesPerRev = 200;
float distancePerPulse;

//L298N Motor Driver
#define enA 6
#define in1 5
#define in2 4
int speedPWM = 0;
int minPWM = 120;

bool CWRotation = true;
int acceleration = 2;

//Job Variables
float feedLength = 0;
float distance = 0;
float overshootLength = 260; //Deceleration overshoot length offset

//Menu Variables
int menuItem = 0;

//Function Prototypes
void encoderPinChangeA(void);
void encoderPinChangeB(void);
int read_buttons();
void RunJob(void);
void calcDistance();
void EnterQty(void);

//Preset Lengths (inches)
const int guylineCordLength = 1200;
const int ridgelineLength = 300;

void setup()
{

  // set up the LCD's number of columns and rows:
  lcd.begin(totalCols, totalRows);

  // initialize the serial communications port:
  Serial.begin(9600);

  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonSelect, INPUT);

  // Encoder Setup
  pinMode(encoder_a, INPUT_PULLUP);
  pinMode(encoder_b, INPUT_PULLUP);
  
  attachInterrupt(0, encoderPinChangeA, RISING);
  
  //Calculate encoder distance per pulse
  distancePerPulse = wheelPerimeter / pulsesPerRev;

  //Motor Setup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  speedPWM = minPWM;

  // Boot Up Message
  Serial.println("Automatic Coiler");
  lcd.print("Automatic Coiler");
  lcd.setCursor(0, 1);
  lcd.print("Starting Up");
  Serial.print("Starting Up");
  delay(300);
  for (int i = 0; i < 6; i++)
  {
    Serial.print(".");
    lcd.print(".");
    delay(100);
  }

  Serial.begin(9600);

  lcd.clear();

  displayMenu();
}

void calcDistance()
{
  //Convert mm to inches
  distance = (encoder * distancePerPulse) / 25.4;
  Serial.println(distance);
}

void RunJob(int feedLength)
{
  //Set Motor Direction Forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(20);
        
  int accelerationDistance = 0;

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(7, 1);
  lcd.print("/");
  lcd.print(feedLength);
  lcd.print("in");

  //Smooth Start
  while (speedPWM < 255) {

    calcDistance();
    
    Serial.print(distance);
    Serial.print("/");
    Serial.println(feedLength);

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= updateInterval) {
      // save the last time we updated LCD
      previousMillis = currentMillis;
  
      lcd.setCursor(0, 1);
      lcd.print("       ");
      lcd.setCursor(0, 1);
      lcd.print((int)distance);
    }
    
    analogWrite(enA, speedPWM); // Send PWM signal to L298N Enable pin
    speedPWM = speedPWM + acceleration;
    delay(100);
    accelerationDistance = distance;
  }

  //Run Full Speed
  while (distance < feedLength - accelerationDistance - overshootLength) {

    calcDistance();
    
    Serial.print(distance);
    Serial.print("/");
    Serial.println(feedLength);
    
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= updateInterval) {
      // save the last time we updated LCD
      previousMillis = currentMillis;
  
      lcd.setCursor(0, 1);
      lcd.print("       ");
      lcd.setCursor(0, 1);
      lcd.print((int)distance);
    }

    analogWrite(enA, 255); // Send PWM signal to L298N Enable pin

    
  }

  //Decelerate
  while (speedPWM > minPWM) {

    calcDistance();
    
    Serial.print(distance);
    Serial.print("/");
    Serial.println(feedLength);
    
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= updateInterval) {
      // save the last time we updated LCD
      previousMillis = currentMillis;
  
      lcd.setCursor(0, 1);
      lcd.print("       ");
      lcd.setCursor(0, 1);
      lcd.print((int)distance);
    }
    
    analogWrite(enA, speedPWM); // Send PWM signal to L298N Enable pin
    speedPWM = speedPWM - acceleration;
    delay(100);
  }

  //Fine Tune Length
  while (distance < feedLength) {

    calcDistance();
    
    Serial.print(distance);
    Serial.print("/");
    Serial.println(feedLength);
    
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= updateInterval) {
      // save the last time we updated LCD
      previousMillis = currentMillis;
  
      lcd.setCursor(0, 1);
      lcd.print("       ");
      lcd.setCursor(0, 1);
      lcd.print((int)distance);
    }

    analogWrite(enA, minPWM); // Send PWM signal to L298N Enable pin

    
  }
  
  analogWrite(enA, 0); // Send PWM signal to L298N Enable pin

  speedPWM = minPWM;
  encoder = 0; //empty for next round
  distance = 0; //empty for next round

  Serial.println("Done!");

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Done!");

  delay(1000);

  displayMenu();
}

void displayMenu(){
  switch (menuItem) {
    case 0:
      Serial.println("Guyline Cord");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Guyline Cord");
      lcd.setCursor(0, 1);
      lcd.print("1200in, 1.5mm YL");
      break;

    case 1:
      Serial.println("Ridgeline Cord");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ridgeline Cord");
      lcd.setCursor(0, 1);
      lcd.print("300in, 1.5mm GR");
      break;

    case 2:
      Serial.println("Reset Distance");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reset Distance");
      break;

    case 3:
      Serial.println("Reverse Motor");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reverse Motor");
      lcd.setCursor(0, 1);
      lcd.print("2 seconds");
      break;
  }
}

void loop()
{

  switch (read_buttons()){
    case 1: //Left Button Pushed
      if (menuItem > 0) {
        menuItem = menuItem - 1;
        displayMenu();
      }
      break;

    case 2: //Right Button Pushed
      if (menuItem < 4) {
        menuItem = menuItem + 1;
        displayMenu();
      }
      break;

    case 3: //Enter Button Pushed
    
      switch (menuItem){
        case 0: // menu item 1 selected
          Serial.println("Guyline Cord");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Guyline Cord");
          RunJob(guylineCordLength);
          break;

        case 1: // menu item 2 selected
          Serial.println("Ridgeline");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Ridgeline");
          RunJob(ridgelineLength);
          break;
  
        case 2: // menu item 3 selected
          Serial.println("Counter Reset");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Counter Reset!");
          encoder = 0;
          delay(2000);
          displayMenu();
          break;
        
        case 3: // menu item 4 selected
          Serial.println("Reverse");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Reversing");
          encoder = 0;
          digitalWrite(in1, LOW);
          digitalWrite(in2, HIGH);
          delay(20);
          analogWrite(enA, 180); // Send PWM signal to L298N Enable pin
          delay(2000);
          analogWrite(enA, 0); // Send PWM signal to L298N Enable pin
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
          delay(20);
          displayMenu();
          break;
      }
      
      break;
  }
}

int read_buttons()
{ // you may need to swap "void" with "int" or "byte"

  int returndata = 0;

  if ((lastButtonPressed + debounceTime) < millis())
  { // see if it's time to check the buttons again

    // read Up button
    buttonState = digitalRead(buttonUp);

    if (buttonState == LOW)
    {
      returndata = 1;
      lastButtonPressed = millis();
      Serial.println("UP");
    }

    // read Down button
    buttonState = digitalRead(buttonDown);

    if (buttonState == LOW)
    {
      returndata = 2;
      lastButtonPressed = millis();
      Serial.println("DOWN");
    }

    //read Select button
    buttonState = digitalRead(buttonSelect);

    if (buttonState == LOW)
    {
      returndata = 3;
      lastButtonPressed = millis();
      Serial.println("SELECT");
    }
  }

  return returndata; // this spits back to the function that calls it the variable returndata.
}

void encoderPinChangeA() {
  if(digitalRead(encoder_b) == LOW) {
    encoder++;
  } else{
    encoder--;
  }
}
