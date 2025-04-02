#!/bin/bash

echo $(set +m;\
 isotprecv -s 7E0 -d 7E8 vcan0 | xxd -r -s -3 -c 20  & \
 echo "22 F1 90" | isotpsend -s 7E0 -d 7E8 vcan0)