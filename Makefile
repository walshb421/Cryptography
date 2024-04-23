OBJECTS := $(patsubst set*/%.cpp,%.o,$(wildcard set*/challenge*.cpp))
#OBJECTS := $(patsubst %.c,build/%.o,$(wildcard *.c))
#OBJECTS := $(OBJECTS) $(patsubst basics/%.c,build/%.o,$(wildcard basics/*.c))


#.PHONY: all run clean

all: 
	echo "$(OBJECTS)"
#$(BDIR) $(DDIR) $(EXE) basics/cyphertext1.txt basics/cyphertext2.txt

$(BDIR):
	$(OBJECTS)	
#mkdir -p $@

$(DDIR):
	mkdir -p $@

$(EXE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(BDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

basics/cyphertext1.txt: 
	curl -s https://cryptopals.com/static/challenge-data/4.txt > $@

$(DDIR)/raw6: 
	curl -s https://cryptopals.com/static/challenge-data/6.txt | tr -d \\n | base64 -d > $@
	

test: 
	./$(EXE)

clean:
	rm -rf ./build ./cryptopals ./basics/cyphertext1.txt