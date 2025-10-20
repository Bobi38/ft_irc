#!/bin/bash


(
echo "PASS pp"
sleep 0.5
echo "NICK pp"
sleep 0.5
echo "NAME uu"
sleep 1
echo "JOIN #uu"
) | telnet localhost 6666