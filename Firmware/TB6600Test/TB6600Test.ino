// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

//Stepper Motor
const int StepperStepPin = 6;
const int StepperDirectionPin = 5;
const int StepperEnablePin = 4;
const int stepsPerRevolution = 400;
const int StepperAcceleration = 200;
const int StepperMaxSpeed = 900;
AccelStepper stepper(AccelStepper::DRIVER, StepperStepPin, StepperDirectionPin);

void setup()
{  

  pinMode(StepperStepPin, OUTPUT);
  pinMode(StepperDirectionPin, OUTPUT);
  pinMode(StepperEnablePin, OUTPUT);

  digitalWrite(StepperEnablePin, LOW);

  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(StepperMaxSpeed);
  stepper.setAcceleration(StepperAcceleration);
  stepper.moveTo(20000);
}

void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());

    stepper.run();
}
