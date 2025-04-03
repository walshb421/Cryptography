NBYTES=255


monitor_isotp() {
   while raw=$(timeout 2 isotprecv -s 7E0 -d 7E8 vcan0); do
      printf "%s " "$(echo $raw  | xxd -r -s 1 -c $NBYTES)"
   done

}

 

monitor_isotp & 

for i in $(seq 0 1 256)
do
   echo "23 14 C3 F8 $(printf "%02X 00 %02X" $i $NBYTES)" | isotpsend -s 7E0 -d 7E8 -g 500000 vcan0

done


