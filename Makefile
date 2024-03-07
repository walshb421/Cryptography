EXE = cryptopals
CC = gcc
.PHONY: all run clean

all: cryptopals

$(EXE): main.o hex2base64.o fixed_xor.o
	$(CC) $(LDFLAGS) $^ -o $@ 

main.o: main.c basics/hex2base64.h basics/fixed_xor.h
	$(CC) -c main.c -o $@

hex2base64.o: basics/hex2base64.c basics/hex2base64.h 
	$(CC) -c basics/hex2base64.c -o $@

fixed_xor.o: basics/fixed_xor.c basics/fixed_xor.h 
	$(CC) -c basics/fixed_xor.c -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -f ./*.o ./cryptopals