DECODE_DTC() {


	SYS_CODE_RAW=$(((16#$(echo $* | cut -d ' ' -f 4-4) >> 6) + 1))
	SYS_CODE=$(echo "P C B U" | cut -d ' ' -f $SYS_CODE_RAW-$SYS_CODE_RAW)$((16#$(echo $* | cut -d ' ' -f 4-4) >> 4))
	DTC=$SYS_CODE$( printf "%X" $((16#$(echo $* | cut -d ' ' -f 4-4) & 0x0F)))$(echo $* | cut -d ' ' -f 5-6 -O '-')
	echo $DTC
}


echo $(set +m;\
	DECODE_DTC $(isotprecv -s 7E0 -d 7E8 vcan0) &\
	echo "19 02 FF" | isotpsend -s 7E0 -d 7E8 vcan0)
