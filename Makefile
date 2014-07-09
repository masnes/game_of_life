CFLAGS=-Wall -lm -g
CC=clang
LDFLAGS=
SOURCES=
OBJECTS=
EXECUTABLE=

all: game
	
reversepolishcalc:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

$@: 
	$(CC) $(CFLAGS) $@ -o $@

# .c.o:
	# $(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCES:.c=) $(OBJECTS)
