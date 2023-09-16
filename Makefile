UNAME:=$(shell uname)
ifeq ($(UNAME), Darwin)
	PATH_POSTGRESQL=-L/Library/PostgreSQL/14/lib/ -lpq
else ifeq ($(UNAME), Linux)
	PATH_POSTGRESQL=-I/usr/include/postgresql -L/usr/lib -lpq
else
	$(error Operative system not supported yet.)
endif

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c11
TARGET=todo
SRCS=src/main.c src/psql.c
OBJS=$(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(PATH_POSTGRESQL)

.PHONY: clean

clean:
	$(RM) $(TARGET) $(OBJS)
