#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psql.h"

int main(int argc, const char **argv) {
    char *endptr;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [add|delete|list] [description]\n", argv[0]);
        return 1;
    }
    
    if (!strcmp(argv[1], "add") && argc == 3) {
        add_task(argv[2]);
    } else if (!strcmp(argv[1], "delete") && argc == 3) {
        delete_task((int)strtol(argv[2], &endptr, BASE));
    } else if (!strcmp(argv[1], "list") && argc == 2) {
        print_tasks();
    } else {
        fprintf(stderr, "Invalid command\n");
        return 1;
    }
    return 0;
}
