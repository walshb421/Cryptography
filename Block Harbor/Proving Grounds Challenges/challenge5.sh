#!/usr/bin/env sh



cleanup() {
   for pid in $kids
   do
      if kill -0 $pid 2>/dev/null; then
         kill $pid
      fi
   done
   exit 0 
}

trap 'cleanup' EXIT INT TERM KILL HUP 



UDS() {
   echo "$*" | isotpsend -s 7E0 -d 7E8 vcan0
}


DEFAULT_SESSION() {
   if kill -0 $session 2>/dev/null; then
      kill $session
   fi
   UDS 10 01
}

EXT_SESSION() {
   UDS 10 03
   while true; do UDS 3E 00; sleep 5; done & kids="$kids $!" session=$!
}


REQ_SEED() {

   sleep 0.5; UDS 27 03 &
   SEED=$(isotprecv -s 7E0 -d 7E8 vcan0)
   if [ "$(echo $SEED | cut -d ' ' -f-2)" = "67 03" ]; then

      echo $SEED | cut -d ' ' -f 3-5 -O ''
   else
      exit 1
   fi
}

REQ_KEY() {
   UDS 27 04 $1 $2
}

EXT_SESSION

SEED=$(REQ_SEED)
KEY=$(printf "%04X" $((0x$SEED ^ 0xFFFF))  | sed 's/../& /g')
REQ_KEY $KEY

sleep 1
DEFAULT_SESSION

printf "%04x\n" $((0x1337 ^ 0xFFFF))
