#!/bin/bash

./Server_TankerGames.out 0.0.0.0 2200 &

sleep 1.5

./Client_TankerGames.out 127.0.0.1 2200 &

./Client_TankerGames.out 127.0.0.1 2200 &