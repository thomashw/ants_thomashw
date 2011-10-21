CC=gcc
CFLAGS=-O3 -funroll-loops -c
LDFLAGS=-O2 -lm
SOURCES=MyBot.c YourCode.c ants.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=MyBot

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

	cp $(EXECUTABLE) "$(HOME)/Desktop/tools/$(EXECUTABLE)"

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ${EXECUTABLE} ${OBJECTS} *.d

.PHONY: all clean
