/*
 * This sketch demonstrates a self-stablizing system (medium challenge)
 */

#define TARGET_VALUE 800

int led_output = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int ldr_val = analogRead(A0);
  if (ldr_val > TARGET_VALUE) {
    led_output = led_output - 5;  // very bright, decrease led
  }
  if (ldr_val < TARGET_VALUE) {
    led_output = led_output + 5;  // dark, increase led contribution
  }

  led_output =
      constrain(led_output, 0, 1023);  // constrain values for the output

  analogWrite(D7, led_output);

  // print out values
  Serial.print("TARGET:");
  Serial.print(TARGET_VALUE);
  Serial.print("\t");
  Serial.print("LED:");
  Serial.print(led_output);
  Serial.print("\t");
  Serial.print("LDR:");
  Serial.println(ldr_val);
  delay(200);
}
