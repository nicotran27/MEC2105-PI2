#include <IRremote.h>
#include <AccelStepper.h>
#include <Servo.h>

#define IR_RECEIVE_PIN 8

#define IR_BUTTON_UP 70 
#define IR_BUTTON_DOWN 21
#define IR_BUTTON_LEFT 68
#define IR_BUTTON_RIGHT 67
#define IR_BUTTON_OK 64
#define IR_BUTTON_1 22
#define IR_BUTTON_2 25
#define IR_BUTTON_3 13
#define IR_BUTTON_4 12
#define IR_BUTTON_5 24
#define IR_BUTTON_6 94
#define IR_BUTTON_7 8
#define IR_BUTTON_8 28
#define IR_BUTTON_9 90
#define IR_BUTTON_H 74
#define IR_BUTTON_0 82
#define IR_BUTTON_STAR 66

Servo servo1; 
Servo servo2;

#define STEPS  8   // Number of steps per revolution of Internal shaft
int dir;

AccelStepper RoueAvantDroite(STEPS, 22, 26, 24, 28);// MOTEUR AVANT DROIT
AccelStepper RoueAvantGauche(STEPS, 23, 27, 25, 29);// MOTEUR ARRIERE DROIT
AccelStepper RoueArriereDroite(STEPS,  30, 34, 32, 36);// MOTEUR AVANT GAUCHE
AccelStepper RoueArriereGauche(STEPS, 31, 35, 33, 37); // MOTEUR ARRIERE GAUCHE
int wheelSpeed = 1000;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  RoueAvantDroite.setMaxSpeed(wheelSpeed);
  RoueAvantGauche.setMaxSpeed(wheelSpeed);
  RoueArriereDroite.setMaxSpeed(wheelSpeed);
  RoueArriereGauche.setMaxSpeed(wheelSpeed);
  servo1.attach(52);
  servo2.attach(53);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    
    if (command == IR_BUTTON_UP) //BOUTON AVANCER
    {
    RoueAvantDroite.setSpeed(wheelSpeed);
    RoueArriereDroite.setSpeed(wheelSpeed);
    RoueAvantGauche.setSpeed(-wheelSpeed);
    RoueArriereGauche.setSpeed(-wheelSpeed); 
    }

    else if (command == IR_BUTTON_DOWN) //BOUTON RECULER
    {
    RoueAvantDroite.setSpeed(-wheelSpeed);
    RoueArriereDroite.setSpeed(-wheelSpeed);
    RoueAvantGauche.setSpeed(wheelSpeed);
    RoueArriereGauche.setSpeed(wheelSpeed); 
    }

    else if (command == IR_BUTTON_LEFT) //BOUTON ROTATION ANTIHORAIRE
    {
    RoueAvantDroite.setSpeed(wheelSpeed);
    RoueArriereDroite.setSpeed(-wheelSpeed);
    RoueAvantGauche.setSpeed(wheelSpeed);
    RoueArriereGauche.setSpeed(-wheelSpeed); 
    }

    else if (command == IR_BUTTON_RIGHT) //BOUTON ROTATION HORAIRE
    {
    RoueAvantDroite.setSpeed(-wheelSpeed);
    RoueArriereDroite.setSpeed(wheelSpeed);
    RoueAvantGauche.setSpeed(-wheelSpeed);
    RoueArriereGauche.setSpeed(wheelSpeed); 
    }

    else if (command == IR_BUTTON_OK) //BOUTON STOP
    {
    RoueAvantDroite.setSpeed(0);
    RoueAvantGauche.setSpeed(0);
    RoueArriereDroite.setSpeed(0);
    RoueArriereGauche.setSpeed(0); 
    }
    
    else if (command == IR_BUTTON_1) //BOUTON 100 degrés
    {
    servo2.write(145);
    }

    else if (command == IR_BUTTON_2) //BOUTON Au Centre
    {
    servo2.write(88);
    }

    else if (command == IR_BUTTON_3) //BOUTON Au Sol
    {
    servo2.write(55);
    }

    else if (command == IR_BUTTON_4) //BOUTON Au Sol
    {
    servo1.write(94);
    }

    else if (command == IR_BUTTON_5) //BOUTON X Degrés
    {
    servo1.write(40);
    }
    
    else if (command == IR_BUTTON_7) //BOUTON CRAWL GAUCHE
    {
    RoueAvantDroite.setSpeed(wheelSpeed);
    RoueArriereDroite.setSpeed(-wheelSpeed);
    RoueAvantGauche.setSpeed(-wheelSpeed);
    RoueArriereGauche.setSpeed(wheelSpeed); 
    }

    else if (command == IR_BUTTON_8) //BOUTON CRAWL DROITE
    {
    RoueAvantDroite.setSpeed(-wheelSpeed);
    RoueArriereDroite.setSpeed(wheelSpeed);
    RoueAvantGauche.setSpeed(wheelSpeed);
    RoueArriereGauche.setSpeed(-wheelSpeed); 
    }

  }
  RoueAvantDroite.runSpeed();
  RoueAvantGauche.runSpeed();
  RoueArriereDroite.runSpeed();
  RoueArriereGauche.runSpeed();
}