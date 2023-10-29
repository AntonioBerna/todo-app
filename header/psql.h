#pragma once

#ifdef __APPLE__
#include "/usr/local/Cellular/postgresql@16/16.0_1/include/libpq-fe.h"

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
} database_t;

void create_database(database_t *db, const char *port, const char *name, const char *username, const char *password);
PGconn *connect_to_database(database_t *db);
void add_tasks(database_t *db, int argc, const char **argv);
void delete_tasks(database_t *db, int argc, const char **argv);
void print_tasks(database_t *db);
