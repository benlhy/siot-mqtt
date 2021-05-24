/*
 * This program will read an analog signal on A0
 * 
 * author: Ben
 */

void setup() {
  Serial.begin(115200);
  Serial.println("Start: Analog Read");
  pinMode(A0,INPUT); // set the pin mode to either input or output

}

void loop() {
  int val = analogRead(A0);
  //Serial.print("Analog Value from A0: ");
  Serial.print(val+32); // Simulating another value
  Serial.print("\t"); // add tabs for another line to be plotted
  Serial.println(val); 
  
  delay(100);
}
