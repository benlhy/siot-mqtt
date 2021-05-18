void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start: Analog Read");
  pinMode(A0,INPUT); // set the pin mode to either input or output

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  Serial.print("Analog Value from A0: ");
  Serial.println(val); // challenge: check out serial plotter and plot this with several other values on a graph
  delay(1000);
}
