CC=gcc
CFLAGS=-c -Wall -Wextra --std=c99 -pedantic


all: test

test: rgbw-i2c-driver.o i2chw-test.o test.o
	$(CC) test.o rgbw-i2c-driver.o i2chw-test.o -o test

rgbw-i2c-driver.o: rgbw-i2c-driver.c
	$(CC) $(CFLAGS) rgbw-i2c-driver.c

i2chw-test.o: i2chw-test.c
	$(CC) $(CFLAGS) i2chw-test.c

test.o: test.c
	$(CC) $(CFLAGS) test.c

run: test
	./test > result.log

clean:
	rm -rf *.o test
