#include <Servo.h>
#include <AccelStepper.h>

byte byte1;
char receivedNote;

#define led1 44
#define led2 46
#define led3 48
#define led4 50
#define led5 52

#define servo1Pin 2
#define servo2Pin 3

int sFlag1 =0;
int sFlag2 =0;
Servo serv1;
Servo serv2;
int flagServ2 =1;

int s2timer=0;


int step1[4] = {4,5,6,7};
AccelStepper stepper1(AccelStepper::FULL4WIRE, step1[0], step1[2], step1[1], step1[3]);
int sFlag3 =0;
int begPos1 = 150;
int endPos1 = 500;

int step2[4] = {8,9,10,11};
AccelStepper stepper2(AccelStepper::FULL4WIRE, step2[0], step2[2], step2[1], step2[3]);
int sFlag4 =0;
int begPos2 = 150;
int endPos2 = 500;

int step3[4] = {22,24,26,28};
AccelStepper stepper3(AccelStepper::FULL4WIRE, step3[0], step3[2], step3[1], step3[3]);
int sFlag5 =0;
int begPos3 = 150;
int endPos3 = 500;


int led[]= {44,46,48,50,52};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i< sizeof(led);i++) {
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],LOW);
  }
  serv1.attach(servo1Pin);
  serv2.attach(servo2Pin);
  
  //pinMode(servo2Pin,OUTPUT);
  //analogWrite(servo2Pin,0);

  stepper1.setMaxSpeed(2000.0);
  stepper1.setAcceleration(2500.0);
  stepper1.moveTo(begPos1);  

  stepper2.setMaxSpeed(1000.0);
  stepper2.setAcceleration(2000.0);
  stepper2.moveTo(begPos2);  

  stepper3.setMaxSpeed(1000.0);
  stepper3.setAcceleration(1000.0);
  stepper3.moveTo(begPos3);  
}

void loop() {
  readSerial();
  
  if (millis()-s2timer > 180 && flagServ2 == 0) {
    serv2.write(90);
    flagServ2 =1;
    }
  stepper1.run();
  stepper2.run();
  stepper3.run();
  /*if (stepper1.distanceToGo() == 0)
  {stepper1.moveTo(-stepper1.currentPosition());}
    stepper1.run();*/
}


void readSerial() {

  if (Serial.available()) {
    receivedNote = Serial.read();  
  
    switch ( receivedNote ) 
    {
      case 'o':
        allOff();
        break;
      case 'c':
        digitalWrite(led[0],HIGH);
        stepper3.moveTo(endPos3);
         endPos3-=200;
         stepper3.run();
        break;
      case 'd':
        digitalWrite(led[1],HIGH);
         stepper1.moveTo(endPos1);
         endPos1+=250;
         stepper1.run();
        break;
      case 'e':
        digitalWrite(led[2],HIGH);
        stepper2.moveTo(endPos2);
         endPos2+=200;
         stepper2.run();
        break;
      case 'g':
        digitalWrite(led[3],HIGH);
        serv2.write(180);
        // delay(5);
        flagServ2 = 0;
        s2timer = millis();
        break;
      case 'b':
        digitalWrite(led[4],HIGH);
        if(sFlag1==0) {
          serv1.write(50);
          delay(15);
          sFlag1 =1;}
        else {
          serv1.write(120);
          delay(15);
          sFlag1 = 0;
        }
        break;
      default:
        break;
    }
  }
}


void allOff() {
   for (int i = 0; i<sizeof(led); i++) {
      digitalWrite(led[i],LOW);
    }
}

void servo1Move() {
  
  }  
