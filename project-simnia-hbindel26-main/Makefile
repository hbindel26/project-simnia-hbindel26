# Project 2: Simnia RePL

CC = gcc
CFLAGS = -Wall -Wextra -g

# Build the main shell program
simnia: simnia.c shell.c builtins.c strvec.c
	$(CC) $(CFLAGS) $^ -o $@

# Build and run strvec tests
test: strvec.c test_strvec.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f simnia test *.o

