#!/bin/bash

echo $(set +m;\
    candump -n 1  any,7DF:7DF | cut -d ' ' -f 10- | xxd -r  &\
    echo "11 01" | isotpsend -S -s 7E0 vcan0)