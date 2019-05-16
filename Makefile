CC= gcc
CFLAGS= -c -Wvla -Wall -Wextra -std=c99
LDFLAGS = -lm

# Exceutable
ex3: queue.o stack.o basicMath.o main.o
	$(CC) queue.o stack.o basicMath.o main.o $(LDFLAGS) -o ex3

# Object Files
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) queue.c -o queue.o
	
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) stack.c -o stack.o
	
basicMath.o: basicMath.c basicMath.h
	$(CC) $(CFLAGS) basicMath.c -o basicMath.o
	
main.o: main.c queue.h stack.h basicMath.h
	$(CC) $(CFLAGS) main.c -o main.o
	
	