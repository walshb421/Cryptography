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
   KEY=$(READ_MEM 0001AC08 4)
	 # KEY=$(printf "%08X" "$((16#$SEED ^ 16#6E013A98))" | sed 's/../& /g')
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
         echo $size
         ;;
   esac
}


MEMDUMP() {
  START_ADDR=0001A000
  SIZE_SIZE=4
  PAGE_SIZE=3000
  NPAGES=1

  for addr in $(seq $((16#$START_ADDR)) $PAGE_SIZE $((16#$START_ADDR + ($NPAGES*$PAGE_SIZE))))
  do
    READ_MEM $(printf "%08X" "$addr") $PAGE_SIZE
  done

  #READ_MEM $(printf "%08X" "$((16#0001A000 + 6000 ))") 2191
  
  #READ_MEM $(printf "%08X" "$((16#0001A000 + 8191 ))") 1

}

EXT_SESSION
TESTER_PRESENT

sleep 0.5

SEED=$(REQ_SEED)
KEY=$(printf "%04X" $((0x$SEED ^ 0xFFFF))  | sed 's/../& /g')
REQ_KEY $KEY


PROG_SESSION
sleep 1

SEC_ACCESS_1
sleep 1

ES=$(READ_MEM 0001AC00 4)
sleep 1
EK=$(READ_MEM 0001AC08 4)
sleep 1


ES=$(echo $ES | cut -d ' ' -f-4 -O '')
EK=$(echo $EK | cut -d ' ' -f-4 -O '')

printf "%08X\n" "$(( 16#7D0E1A5C ^ (16#$ES ^ 16#$EK) ))"

DEFAULT_SESSION

