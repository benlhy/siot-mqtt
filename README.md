# Introduction
This repo contains the code required to set up the MQTT game. The purpose is to teach students about how MQTT works in a fun manner.

## The game
The objective of the game is to keep your team's score within the published range at the topic `/team_name/target`. You publish your current output to `/team_name/members/[your name]`. The score is determined by the difference between your team's current result and the target.

## Structure
The code is split up into two portions: the server and the client side. The client side will host the Arduino code that reads the sensors while the server side will host the game server that keeps track of the scores

| Topics | Comment |
| ------ | ------- |
|`siot_mqtt/scores/[team]/current_score`| Current score for the team |
|`siot_mqtt/target/[team]/current_reading` | Current reading for the team |
|`siot_mqtt/target/[team]/current_target` | Current target for the team |
|`siot_mqtt/[team]/[team_member]`| The input of each team member |

# Arduino sub-challenges
1. Getting Analog Reading + plotting
2. Reading topics
3. Posting values + reading other people's topics
4. 


# Todo
1. Need to restrict topics related to the score and target portion
2. Arduino needs to read the incoming topic 