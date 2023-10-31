char inChar;
char Char;
#include <SoftwareSerial.h>

SoftwareSerial SerialBT(2,3); // TX, RX
const int trigPin = 7;
const int echoPin = 6;

void setup() {
  Serial.begin(19200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  SerialBT.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() 
{ 
  long duration, distance; // define variables
  // generate the 10us pulse as the trigger signal according to the data sheet
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // duration is the time in us from sending the signal to receiving the echo
  duration = pulseIn(echoPin, HIGH);
  
  // distance is the distance in cm from the object to the sensor
  // use the equation from the data sheet: distance(cm) = duration(us)/58
  distance = duration/58;
  
  
  if (SerialBT.available()) 
  {
    inChar = SerialBT.read();
    Serial.write(inChar);
  }
  if(inChar == 'Y')
  {
    digitalWrite(13,HIGH);
  }
 if (distance < 10) 
  {
    digitalWrite(13,LOW); 
    }  
  else if (inChar == 'N')
  {
    digitalWrite(13,LOW);
  } 
    Serial.print(distance); // print to IDE serial monitor
    Serial.println(" cm");
}
