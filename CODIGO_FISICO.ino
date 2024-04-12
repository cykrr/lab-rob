/* Este código fue escrito para controlar un microservo SG-90 que intuimos no 
   funcionaba correctamente. Llegamos a esta conclusión debido a que en el
   datasheet del servo se menciona que el rango máximo de operación es de 
   180 grados, sin embargo, al escribir el ángulo 0 en el servo (para
   posicionarlo en el ángulo inicial) el motor no dejaba de girar, lo cual
   no coincide con la descripción del datasheet.

   Por ende se optó por un código que trabaja con la velocidad  del motor 
   y se le indica que gire a velocidad máxima por un periodo de tiempo,
   Logrando así que:
      * Con d > 80  y luz MAX: Gire 180 grados
      * con d < 30 y luz MIN: Gire 60 grados
      * con d < 2 y luz 0: Nada
  */

#include <Servo.h>
int triggerPin = 11, echoPin = 12, servoPin = 10;
Servo servo;
void setup()
{
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  servo.attach(servoPin);
  //servo.write(0);
 
}
int LMAX = 150, LMIN=90;
int angulo=0;
void loop()
{
  int luz = analogRead(0);
	digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long t,d;
  t=pulseIn(echoPin, HIGH);
  d=t/59;
  if (d > 80 && luz > LMAX && angulo != 180) {
    angulo = 180;
    servo.write(0);
    delay(370);
    servo.write(90);
    Serial.print("!");
    Serial.println(180);
  } else if (d < 30 && luz < LMIN && angulo != 60) {
      if (d < 2 && luz < 10) {   
        Serial.println("None");
      } else {
        angulo = 60;
        Serial.print("!");
        Serial.println(60);
        servo.write(0);
        delay(120);
        servo.write(90);
  }
  Serial.println(d);
  Serial.println(analogRead(0));
  delay(100);
}
