#pragma once

#include "/Library/PostgreSQL/14/include/libpq-fe.h"

#define DATABASE "todolist"
#define USERNAME "postgres"
#define PASSWORD "ant0ni02"
#define PORT "5433"

#define SELECT_TASKS_QUERY "SELECT * FROM tasks;"
