//RECEIVER

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);}

void loop() {
  int i=0;
  if(Serial.available())
    Serial.println(Serial.read());
}
