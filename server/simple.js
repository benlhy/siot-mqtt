var mqtt = require("mqtt");
//var client     = mqtt.connect('mqtt://test.mosquitto.org')
var client = mqtt.connect("mqtt://broker.hivemq.com"); // alternative broker

score_tracker = {
  0: {
    target_val: 0,
  },
};

client.on("connect", function () {
  client.subscribe("siot_mqtt/hello", function (err) {
    if (!err) {
      client.publish("siot_mqtt/hello", "Hello from SIOT over MQTT!", {
        retain: true,
      });
    }
  });
  client.subscribe("siot_mqtt/1/#", mqtt_subscribe);
  client.subscribe("siot_mqtt/2/#", mqtt_subscribe);
  client.subscribe("siot_mqtt/3/#", mqtt_subscribe);
  client.subscribe("siot_mqtt/4/#", mqtt_subscribe);
  //client.subscribe("siot_mqtt/scores/#", mqtt_subscribe);
  //client.subscribe("siot_mqtt/target/#", mqtt_subscribe);
});

function target_tick(team) {
  const target_val = getRndInteger(250, 900);
  score_tracker[team]["target_val"] = target_val;
  console.log(`Target value set to: ${target_val}`);
  client.publish(`siot_mqtt/0/target`, target_val.toString(), {
    retain: false,
  });
}

setInterval(target_tick, 10000, 0); // tick the target value, update every 30 seconds, update team 0 - global
