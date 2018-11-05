all: main.o functions.o
	gcc -o spi main.o functions.o -l bcm2835
read_file.o: main.c
	gcc -c read_file.c
functions.o: functions.c functions.h
	gcc -c functions.c
clean :
	rm *.o
	rm spi
