CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99
CTARGET=main
SRCS=main.c psql.c
OBJS=$(SRCS:.c=.o)

PATH_POSTGRESQL=-L/Library/PostgreSQL/14/lib/ -lpq

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(CTARGET) $(PATH_POSTGRESQL)

.PHONY: clean

clean:
	$(RM) $(CTARGET) $(OBJS)
