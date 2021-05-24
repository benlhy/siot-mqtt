/*
 * This program will blink an LED on D5
 * 
 * author: Ben
 */

void setup() {
  pinMode(D5,OUTPUT) // set the pin marked D5 as output
}

void loop() {
  digitalWrite(D5,HIGH); // set the pin to HIGH - 3.3V
  delay(1000); // wait for 1000ms
  digitalWrite(D5,LOW); // set the pin to LOW - 0V
  delay(1000); // wait for 1000ms

}
