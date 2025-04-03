cleanup() {
    kill $isotprecv_pid
    exit 0
}


monitor_isotp() {
   isotprecv -s 7E0 -d 7E8 -l vcan0 | cut -d ' ' -f 2-
   # isotprecv -s 7E0 -d 7E8 -l vcan0 | while read a; do echo $a | cut -d ' ' -f 2-; done
}

trap cleanup SIGINT SIGTERM

monitor_isotp &
isotprecv_pid=$!


for i in $(seq 0 8 255)
do

echo "23 14 C3 F8 00 $(printf "%02X" $i) 04" | isotpsend -s 7E0 -d 7E8 -g 1000000 vcan0

done


