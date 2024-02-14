CC = gcc
SOURCE = visualize.c
OUT = final
OBJECTS = visualize.o sort.o
INCLUDES = -lSDL2 -lm -I/usr/include/SDL2/

build: $(OBJECTS)
	$(CC) -g $(OBJECTS) -o $(OUT) $(INCLUDES)

sorting.o:
	$(CC) -c $(SOURCE) -o visualize.o

sort.o:
	$(CC) -c sort.c -o sort.o

clean:
	rm -rf *.o $(OUT)
