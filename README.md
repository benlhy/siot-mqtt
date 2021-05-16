# Introduction
This repo contains the code required to set up the MQTT game. The purpose is to teach students about how MQTT works in a fun manner.

## The game
The objective of the game is to keep your team's score within the published range at the topic `/team_name/target`. You publish your current output to `/team_name/members/[your name]`. The score is determined by the difference between your team's current result and the target.

## Structure
The code is split up into two portions: the server and the client side. The client side will host the Arduino code that reads the sensors while the server side will host the game server that keeps track of the scores

# Todo
1. Need to restrict topics related to the gamemaster portion