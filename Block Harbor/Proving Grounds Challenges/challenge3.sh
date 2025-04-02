#!/bin/bash

echo $(set +m; isotprecv -s 7E0 -d 7E8 vcan0 | cut -d ' ' -f 4-6  & echo "19 02 FF" | isotpsend -s 7E0 -d 7E8 vcan0)