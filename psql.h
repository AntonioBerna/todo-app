#pragma once

#include "libpq-fe.h"

#define BASE 10
#define BUFFER_SIZE 1024

PGconn *connect_to_database(void);
void add_task(const char *description);
void delete_task(int id);
void print_tasks(void);
