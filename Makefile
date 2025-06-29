CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -g
LDFLAGS= 
INCLUDES=-Icore
LIBS=

UNAME_S := $(shell uname)

ifneq (,$(filter $(UNAME_S), Linux Darwin))
    PG_INCLUDE := $(shell pg_config --includedir)
    PG_LIB := $(shell pg_config --libdir)
    LIBS += -L$(PG_LIB) -lpq
    INCLUDES += -I$(PG_INCLUDE)
else
    $(error OS $(UNAME_S) not supported)
endif

SRCS=src/main.c core/psql.c
TARGET=todo

all: $(SRCS)
	@mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) $^$(LIBS) -o build/$(TARGET)

clean:
	$(RM) -r build/
