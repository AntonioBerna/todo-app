#pragma once

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <libpq-fe.h>

typedef enum { CMD_UNKNOWN = 0, CMD_ADD, CMD_REMOVE, CMD_EDIT, CMD_LIST } cmd_t;

cmd_t parse_command(const char *cmd_str);

typedef struct {
    const char *db_name;
    const char *username;
    const char *password;
    const char *port;
    size_t no_tasks;
    const char **tasks;
} db_t;

void init_db(db_t *todo, const size_t no_tasks, const char **tasks);
PGconn *connect_to_db(db_t todo);
void add_tasks(db_t todo);
void remove_tasks(db_t todo);
void edit_tasks(db_t todo, const long id, const char *new_description);
void print_tasks(db_t todo);
