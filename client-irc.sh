#!/bin/bash


(
echo "PASS pp"
sleep 0.5
echo "NICK pp"
sleep 0.5
echo "USER pp 0 * :pp_"
sleep 1
cat
) | telnet localhost 6666