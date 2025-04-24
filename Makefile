CC=gcc
CFLAGS=-c -Wall -Wextra --std=c99 -pedantic -I./driver -I./i2chw

all: test

test: rgbw-i2c-driver.o i2chw-test.o test.o
	$(CC) test.o rgbw-i2c-driver.o i2chw-test.o -o test

rgbw-i2c-driver.o: driver/rgbw-i2c-driver.c
	$(CC) $(CFLAGS) driver/rgbw-i2c-driver.c

i2chw-test.o: i2chw/i2chw-test.c
	$(CC) $(CFLAGS) i2chw/i2chw-test.c

test.o: tests/test.c
	$(CC) $(CFLAGS) tests/test.c

run: test
	./test > run.out
	diff run.out tests/expected.out || echo "OUTPUT IS NOT EQUAL TO EXPECTED"

clean:
	rm -rf *.o test run.out
