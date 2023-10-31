#include <stdio.h>
#include <string.h>

#include "psql.h"

int main(int argc, const char **argv) {
    database_t db;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [add|delete|list] [description|id]\n", *argv);
        exit(EXIT_FAILURE);
    }

    create_database(&db, PORT, DATABASE, USERNAME, PASSWORD);
    if (!strcmp(argv[1], "add")) {
        add_tasks(&db, argc, argv);
    } else if (!strcmp(argv[1], "delete")) {
        delete_tasks(&db, argc, argv);
    } else if (!strcmp(argv[1], "list") && argc == 2) {
        print_tasks(&db);
    } else {
        fprintf(stderr, "Invalid command, try again.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
