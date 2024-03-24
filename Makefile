EXE = cryptopals
CC = gcc
.PHONY: all run clean

all: cryptopals basics/cyphertext1.txt

$(EXE): main.o hex2base64.o fixed_xor.o xor_cypher.o detect_char_xor.o encrypt_repeating_xor.o common.o
	$(CC) $(LDFLAGS) $^ -o $@ 

main.o: main.c basics/basics.h
	$(CC) -c main.c -o $@

common.o: basics/common.c basics/basics.h 
	$(CC) -c basics/common.c -o $@

hex2base64.o: basics/hex2base64.c basics/basics.h 
	$(CC) -c basics/hex2base64.c -o $@

fixed_xor.o: basics/fixed_xor.c basics/basics.h
	$(CC) -c basics/fixed_xor.c -o $@

xor_cypher.o: basics/xor_cypher.c basics/basics.h
	$(CC) -c basics/xor_cypher.c -o $@

detect_char_xor.o: basics/detect_char_xor.c basics/basics.h
	$(CC) -c basics/detect_char_xor.c -o $@

encrypt_repeating_xor.o: basics/encrypt_repeating_xor.c basics/basics.h
	$(CC) -c basics/encrypt_repeating_xor.c -o $@

basics/cyphertext1.txt: 
	curl https://cryptopals.com/static/challenge-data/4.txt > basics/cyphertext1.txt

run: all
	./$(EXE)

clean:
	rm -f ./*.o ./cryptopals