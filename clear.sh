#!/bin/bash


./v4 stop
pkill v4
sleep 3



gpio write 4 0
gpio write 3 0
gpio write 0 0

gpio write 1 0
gpio write 2 0
gpio write 5 0

gpio write 7 0
gpio write 8 0
gpio write 11 0

gpio write 12 0
gpio write 14 0
gpio write 17 0

gpio write 18 0
gpio write 19 0
gpio write 16 0
