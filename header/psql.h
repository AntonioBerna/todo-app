#pragma once

#ifdef __APPLE__
#include "/usr/local/Cellar/postgresql@16/16.0_1/include/libpq-fe.h"

#define DATABASE "todolist"
#define USERNAME "clevercode"
#define PASSWORD "ant0ni02"
#define PORT "5432" // SELECT setting FROM pg_settings WHERE name = 'port';
#elif __linux__
#include <libpq-fe.h>

#define DATABASE "todolist"
#define USERNAME "postgres"
#define PASSWORD "ant0ni02"
#define PORT "5432" // SELECT setting FROM pg_settings WHERE name = 'port';
#endif

#include <stdlib.h>
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
