/* Adapted from the MQTT_ESP8266 example sketch*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define UPPER_LIMIT 100
//#include "secret.h"

// 3.1 TODO Change the define to match the pin you are using
#define LED D6

// 3.1 TODO: Add your WIFI password here!
const char* password = "";
const char* ssid = "";

// The broker we are using
const char* mqtt_server = "broker.hivemq.com";


// Global values
int target = 0;
int global_score = 0;
int counter = 0;
String incomingByte = ""; // for incoming serial data
int command = 0;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {


  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(A0,INPUT);
  pinMode(LED,OUTPUT);
}

/*
 * This function receives all the messages of the topics that we subscribe to
 */

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  target = atoi((char*)payload); // convert our payload to a numerical value

  // Add match statement here
}

/*
 * This function reconnects to the MQTT broker if the connection is dropped
 */
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // 3.1 TODO: add new subscription to your partner's topic

      // 3.1 TODO: uncommment this line to subscribe to siot_mqtt/hello
      // client.subscribe("siot_mqtt/hello");


      // 3.2 TODO: subscribe to the siot_mqtt/target/0/current_target topic





      
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/*
 * This function computes a score based on the target
 */

int score_add(int target, int current) {
  int result = target - current;
  result = abs(result); 
  if(result>=UPPER_LIMIT) {
    result = UPPER_LIMIT;
  }
  result = map(result,0,UPPER_LIMIT,10,-1); // remap range to 0-20
  return result;
}
void setup() {
  Serial.begin(115200);
  setup_wifi(); // start WIFI
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();

  // If there is something coming in through the serial port

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.readStringUntil('\n'); //convert it to number 
    command = (int)(incomingByte[0]-'0'); // 0: number 1: \n

    if (command==0) {
      // reset the counter and the global score
      counter = 0;
      global_score = 0;
    }
    if (command==1) {
      //Serial.println("Start");
    }
    while (Serial.read() >= 0); //flush the buffer to ignore queued commands
  }
  
  if (now - lastMsg > 500) {
    lastMsg = now;
    
    int light_level = analogRead(A0);
    Serial.print("Current:");
    Serial.print(light_level);
    Serial.print("\t");

    // publish LDR value
    snprintf (msg, MSG_BUFFER_SIZE, "%ld", light_level);
    Serial.print("Publishing LDR value: ");
    Serial.println(msg);

    // 3.1 TODO: uncomment and modify to publish your LDR readings
    //client.publish("siot_mqtt/0/ben", msg);


    // 3.1 TODO: uncomment to change your LED's output value
    //Serial.print("Setting LED value to: ");
    //Serial.println(target);
    //analogWrite(LED,target);


    // 3.2 TODO: uncomment the code below to start your scoring!

    /*
    Serial.print("Target:");
    Serial.print(target);
    Serial.print("\t");
    
    if ((command==1) && (counter<60)) {
      global_score = global_score + score_add(target,light_level);
      
      counter++;
      Serial.print("Score:");
    }
    else {
      Serial.print("Last_Score(");
      Serial.print(global_score);
      Serial.print("):");
    }
    
    Serial.println(global_score);
    */

    

  }
}
