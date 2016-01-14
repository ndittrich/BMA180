TARGET = BMA180Test
LIBS = -lmraa
CC=gcc
CFLAGS = -g -Wall
HEADERS = BMA180.h
OBJ= BMA180_test.o BMA180.o


$(TARGET): $(OBJ) $(HEADERS) 
	$(CC) $(OBJ) -Wall $(LIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	-rm -f *.o
	-rm -f $(TARGET) 
