CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
LDFLAGS = -lraylib -lm -ldl -lGL -lpthread -lrt -lX11

OBJS = main.o fonctions.o interface.o

all: projet

projet: $(OBJS)
	$(CC) $(OBJS) -o projet $(LDFLAGS)

main.o: main.c programme.h
	$(CC) $(CFLAGS) -c main.c

fonctions.o: fonctions.c programme.h
	$(CC) $(CFLAGS) -c fonctions.c

interface.o: interface.c programme.h
	$(CC) $(CFLAGS) -c interface.c

clean:
	rm -f *.o projet
