var mqtt = require("mqtt");
//var client     = mqtt.connect('mqtt://test.mosquitto.org')
var client = mqtt.connect("mqtt://broker.hivemq.com"); // alternative broker

client.on("connect", function () {
  client.subscribe("siot_mqtt/hello", function (err) {
    if (!err) {
      client.publish(
        "siot_mqtt/hello",
        "Hello to the SIOT MQTT game! Make sure that your team and name are set correctly!",
        {
          retain: true,
        }
      );
    }
  });
  client.subscribe("siot_mqtt/1/#", mqtt_subscribe);
  client.subscribe("siot_mqtt/2/#", mqtt_subscribe);
  client.subscribe("siot_mqtt/3/#", mqtt_subscribe);
  client.subscribe("siot_mqtt/4/#", mqtt_subscribe);
});

client.on("message", function (topic, message) {
  // message is Buffer
  console.log(topic);
  topic_list = topic.split("/");
  console.log(topic_list);
  // base - team - member
  console.log(message.toString());
  //client.end()
});

function team_score_publish(team) {
  // sum up all saved values
}

function mqtt_subscribe(err, granted) {
  console.log(`Subscribed: ${granted} `);
  if (err) {
    console.log(err);
  }
}
