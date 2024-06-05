#pragma once

#include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

typedef struct {
    const char *port;
    const char *name;
    const char *username;
    const char *password;

    int no_tasks;
    const char **tasks;
} database_t;

void create_database(database_t *db, const char *port, const char *name, const char *username, const char *password);
PGconn *connect_to_database(database_t *db);
void add_tasks(database_t *db);
void remove_tasks(database_t *db);
void print_tasks(database_t *db);
