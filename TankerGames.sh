#!/bin/bash


./Server_TankerGames.out 0.0.0.0 1200 &

sleep 1.5

./Client_TankerGames.out 0.0.0.0 1200 &

./Client_TankerGames.out 0.0.0.0 1200 &