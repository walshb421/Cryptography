EXE = cryptopals
CC = gcc
BDIR = ./build
VPATH = ./basics

OBJECTS := $(patsubst %.c,build/%.o,$(wildcard *.c))
OBJECTS := $(OBJECTS) $(patsubst basics/%.c,build/%.o,$(wildcard basics/*.c))

.PHONY: all run clean

all: $(BDIR) $(EXE) basics/cyphertext1.txt

$(BDIR):
	echo $(OBJECTS); mkdir -p $@

$(EXE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(BDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

basics/cyphertext1.txt: 
	curl -s https://cryptopals.com/static/challenge-data/4.txt > $@

run: all
	./$(EXE)

clean:
	rm -rf ./build ./cryptopals ./basics/cyphertext1.txt