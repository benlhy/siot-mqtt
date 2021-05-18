var mqtt = require("mqtt");
//var client     = mqtt.connect('mqtt://test.mosquitto.org')
var client = mqtt.connect("mqtt://broker.hivemq.com"); // alternative broker

score_tracker = {};

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

  // update score tracker
  if (topic_list.length === 3) {
    let team = topic_list[1];
    let member_name = topic_list[2];
    if (!(team in score_tracker)) {
      score_tracker[team] = {}; // create
    }
    score_tracker[team][member_name] = parseInt(message);
    console.log(score_tracker);

    // publishing team score
    team_score_publish(team);
  }

  // if it is not a scoring message

  console.log(message.toString());
  //client.end()
});

function team_score_publish(team) {
  const result = sumValues(score_tracker[team]);
  client.publish(
    `siot_mqtt/scores/${team}/current_team_value`,
    result.toString(),
    {
      retain: true,
    }
  );

  // sum up all saved values
}

function mqtt_subscribe(err, granted) {
  console.log(`Subscribed: ${granted} `);
  if (err) {
    console.log(err);
  }
}

const sumValues = (obj) => Object.values(obj).reduce((a, b) => a + b);
