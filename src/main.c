#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psql.h"

int main(int argc, const char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [add|rm|edit|ls] [description|id]\n", *argv);
        exit(EXIT_FAILURE);
    }

    if (argv[1] == NULL || strnlen(argv[1], 32) >= 32) {
        fprintf(stderr, "Invalid or too long command.\n");
        exit(EXIT_FAILURE);
    }

    db_t todo;
    init_db(&todo, argc, argv);

    cmd_t cmd = parse_command(argv[1]);
    switch (cmd) {
    case CMD_ADD: add_tasks(todo); break;
    case CMD_REMOVE: remove_tasks(todo); break;
    case CMD_EDIT:
        if (argc == 4) {
            long id = strtol(argv[2], NULL, 0);
            if (errno == ERANGE) {
                perror("strtol");
                exit(EXIT_FAILURE);
            }
            edit_tasks(todo, id, argv[3]);
        } else {
            fprintf(stderr, "Edit command requires an ID and a new description.\n");
            exit(EXIT_FAILURE);
        }
        break;
    case CMD_LIST:
        if (argc == 2) {
            print_tasks(todo);
        } else {
            fprintf(stderr, "List command takes no additional arguments.\n");
            exit(EXIT_FAILURE);
        }
        break;
    case CMD_UNKNOWN:
    default: fprintf(stderr, "Invalid command '%s'. Use: add, rm, or ls\n", argv[1]); exit(EXIT_FAILURE);
    }

    return 0;
}
