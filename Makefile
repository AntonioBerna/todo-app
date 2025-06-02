CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wpedantic
LDFLAGS= 
INCLUDES=-Iinclude
LIBS=

ifeq ($(shell uname), Linux)
    PG_INCLUDE=$(shell pg_config --includedir)
    PG_LIB=$(shell pg_config --libdir)
    LIBS+=-L$(PG_LIB) -lpq
    INCLUDES+=-I$(PG_INCLUDE)
else
    $(error Operating system not supported yet.)
endif

SRCS=src/main.c src/psql.c
TARGET=todo

all: $(SRCS)
	@mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBS) -o build/$(TARGET)

.PHONY: clean

clean:
	$(RM) -r build/
