#define LIGHT_PIN 999  // TODO 1: replace 999 with the LED pin
#define LDR_PIN A0

int ldrReading;  // this variable is used to store the current ldrReading

// the setup function runs once when you press reset or power the board

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  ldrReading = analogRead(LDR_PIN);  // this reads the value from the LDR (light-dependent resistor)
  Serial.println(ldrReading);  // this prints out the reading

  if (ldrReading < 9999) {  // TODO 2: replace 9999 with a reasonable threshold
    // TODO 3: turn on LED
  } else {
    // TODO 4: turn off LED
  }

  delay(1000);  // wait for a second
}
