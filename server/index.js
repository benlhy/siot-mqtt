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

client.on("message", function (topic, message) {
  // message is Buffer
  //console.log(topic);
  topic_list = topic.split("/");
  console.log(topic_list);
  // base - team - member

  // update score tracker
  if (topic_list.length === 3) {
    let team = topic_list[1];
    let member_name = topic_list[2];
    if (!(team in score_tracker)) {
      score_tracker[team] = {
        current_score: 0,
        current_reading: 0,
        target_val: 0,
        members: {},
      }; // create
    }
    score_tracker[team]["members"][member_name] = parseInt(message);
    console.log(score_tracker);

    // publishing team score
    team_score_publish(team);
  }

  // if it is not a scoring message

  console.log(message.toString());
  //client.end()
});

function clear_siot_mqtt() {
  const result = 0;
  const team = 1;
  client.publish(`siot_mqtt/${team}/current_reading`, result.toString(), {
    retain: false,
  });
}

/*
 * This function gets all the current team values
 * and publishes them to the current_reading topic
 */

function team_score_publish(team) {
  // sum the values and update the global tracker
  const result = sumValues(score_tracker[team]["members"]);
  score_tracker[team]["current_reading"] = result;

  client.publish(
    `siot_mqtt/target/${team}/current_reading`,
    result.toString(),
    {
      retain: false,
    }
  );
}

/*
 * Whenever this function ticks the difference in the target and readings are taken
 * and posted to the scores
 */

function score_tick(team) {
  const currReading = sumValues(score_tracker[team]["current_reading"]);
  const currScore = score_tracker[team]["current_score"];
  const newScore =
    Math.abs(score_tracker[team]["target_val"] - currReading) + currScore;

  // update with new score
  score_tracker[team]["current_score"] = newScore;

  // publish result
  client.publish(`siot_mqtt/scores/${team}/current_score`, score.toString(), {
    retain: false,
  });
}

/*
 * This function sets and changes the target score for the team
 */
function target_tick(team) {
  const target_val = getRndInteger(250, 900);
  score_tracker[team]["target_val"] = target_val;
  console.log(`Target value set to: ${target_val}`);
  client.publish(`siot_mqtt/${team}/target`, target_val.toString(), {
    retain: false,
  });
}

function getRndInteger(min, max) {
  return Math.floor(Math.random() * (max - min)) + min;
}

function mqtt_subscribe(err, granted) {
  console.log(`Subscribed: ${granted} `);
  if (err) {
    console.log(err);
  }
}

const sumValues = (obj) => Object.values(obj).reduce((a, b) => a + b);

//setInterval(score_tick, 1000, 1); // tick every second to capture the score.
setInterval(target_tick, 10000, 0); // tick the target value, update every 30 seconds, update team 0 - global
