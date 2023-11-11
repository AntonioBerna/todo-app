#include <stdio.h>
#include <string.h>

#include "psql.h"

int main(int argc, const char **argv) {
    database_t db;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [add|rm|ls] [description|id]\n", *argv);
        exit(EXIT_FAILURE);
    }

    create_database(&db, PORT, DATABASE, USERNAME, PASSWORD);
    db.no_tasks = argc;
    db.tasks = argv;

    if (!strcmp(argv[1], "add")) {
        add_tasks(&db);
    } else if (!strcmp(argv[1], "rm")) {
        delete_tasks(&db);
    } else if (!strcmp(argv[1], "ls") && argc == 2) {
        print_tasks(&db);
    } else {
        fprintf(stderr, "Invalid command, try again.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
