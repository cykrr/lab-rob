#include <Servo.h>

#Resistencia fija de 2000 Ohm

int echo = 11;
int trigger = 12;
int pinServo = 10;

int LMAX = 950; // >= Poca luz
int LMIN = 300; // <= Mucha luz
int angle = 0;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  
  servo.attach(pinServo);
  servo.write(0);
}

void loop() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  long t = pulseIn(echo, HIGH);
  long d = t/59;
  
  int v = analogRead(0);
  
  if (d >= 80 && v <= LMIN && angle != 180) {
  	servo.write(180);
    angle = 180;
  }
  else if (d <= 30 && v >= LMAX && angle != 60) {
    if (d >= 2 && v > 50) {
      servo.write(60);
      angle = 60;
    }
  }
  
  delay(1000);
}