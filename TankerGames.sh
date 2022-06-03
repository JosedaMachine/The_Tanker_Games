#!/bin/bash

# make binaries
make clean
make game

# open server
./Server_TankerGames.out 0.0.0.0 2200 &
sleep 1.5

# open clients
./Client_TankerGames.out 127.0.0.1 2200 &
./Client_TankerGames.out 127.0.0.1 2200 &