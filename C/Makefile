all: spi

Icon: spi.o read_file.o

read_file.o: read_file.cpp
	gcc -c read_file.c

spi.o: spi.c
	gcc -c spi.c





clean:
	rm *.o spi
