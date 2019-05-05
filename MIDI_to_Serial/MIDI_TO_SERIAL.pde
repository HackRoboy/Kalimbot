import processing.serial.*;
import themidibus.*;

MidiBus midiDAW;
MidiBus midiKey;
Serial ser;
char tex = 'a';

String str = null;
int nl = 10; // new line in ASCII
float val;
byte byte1 =0;
int c=0;
float t = 1000;

void setup() 
{
  size(800,800);
  
  MidiBus.list();
  midiDAW = new MidiBus(this,1,4);
  //midiKey = new MidiBus(this,1,4);
  
  String port = Serial.list() [0];
  ser = new Serial(this, port, 9600);
  stroke(255);
  strokeWeight(20);
  ser.write('a');
  delay(1000);
}

void draw() {
  
}
  

void draw1 () 
{
  while(ser.available() >0) {
    str = ser.readStringUntil(nl);
    
    if(str != null) {
      background(0);
      val = float(str);
      point(val,val);
      println(val);
    }
  }
}

void noteOn(int channel, int pitch, int velocity) 
{
  pitch = pitch%12 +60; // creates octave
  switch (pitch) {
    case 60:
      ser.write('c');
      break;
    case 62:
      ser.write('d');
      break;
    case 63:
      ser.write('e');
      break;
    case 65:
      ser.write('f');
      break;
    case 67:
      ser.write('g');
      break;
    case 69:
      ser.write('a');
      break;
    case 70:
      ser.write('b');
      break;
    case 71:
      ser.write('h');
      break;
    default:
    break;
  }
}

void noteOff(int channel, int pitch, int velocity) {
    ser.write('o');
}
