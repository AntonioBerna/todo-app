#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psql.h"

int main(int argc, const char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [add|rm|ls] [description|id]\n", *argv);
        exit(EXIT_FAILURE);
    }

    const char *database = getenv("DATABASE");
    const char *username = getenv("USERNAME");
    const char *password = getenv("PASSWORD");
    const char *port = getenv("PORT");

    if (!database || !username || !password || !port) {
        fprintf(stderr, "Environment variables not set.\n");
        exit(EXIT_FAILURE);
    }

    database_t db;
    create_database(&db, port, database, username, password);
    db.no_tasks = argc;
    db.tasks = argv;

    if (!strcmp(argv[1], "add")) {
        add_tasks(&db);
    } else if (!strcmp(argv[1], "rm")) {
        remove_tasks(&db);
    } else if (!strcmp(argv[1], "ls") && argc == 2) {
        print_tasks(&db);
    } else {
        fprintf(stderr, "Invalid command, try again.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
