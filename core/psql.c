#include "psql.h"

cmd_t parse_command(const char *cmd_str) {
    if (cmd_str == NULL) return CMD_UNKNOWN;

    if (strncmp(cmd_str, "add", 4) == 0) {
        return CMD_ADD;
    } else if (strncmp(cmd_str, "rm", 3) == 0) {
        return CMD_REMOVE;
    } else if (strncmp(cmd_str, "edit", 5) == 0) {
        return CMD_EDIT;
    } else if (strncmp(cmd_str, "ls", 3) == 0) {
        return CMD_LIST;
    }

    return CMD_UNKNOWN;
}

void init_db(db_t *todo, const size_t no_tasks, const char **tasks) {
    assert(todo != NULL);

    const char *db_name = getenv("DB_NAME");
    const char *username = getenv("USERNAME");
    const char *password = getenv("PASSWORD");
    const char *port = getenv("PORT");

    if (!db_name || !username || !password || !port) {
        fprintf(stderr, "Environment variables not set.\n");
        exit(EXIT_FAILURE);
    }

    if (strnlen(db_name, 256) >= 256 || strnlen(username, 256) >= 256 || strnlen(password, 256) >= 256 || strnlen(port, 16) >= 16) {
        fprintf(stderr, "Environment variables too long.\n");
        exit(EXIT_FAILURE);
    }

    todo->db_name = db_name;
    todo->username = username;
    todo->password = password;
    todo->port = port;
    todo->no_tasks = no_tasks;
    todo->tasks = tasks;
}

PGconn *connect_to_db(db_t todo) {
    PGconn *conn = PQsetdbLogin(NULL, todo.port, NULL, NULL, todo.db_name, todo.username, todo.password);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        return NULL;
    }
    return conn;
}

void add_tasks(db_t todo) {
    char query[BUFSIZ];

    PGconn *conn = connect_to_db(todo);
    if (conn == NULL) {
        perror("conn");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 2; i < todo.no_tasks; ++i) {
        PGresult *res = PQexec(conn, "SELECT MAX(id) FROM tasks;");
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Error fetching max ID: %s\n", PQerrorMessage(conn));
            PQclear(res);
            PQfinish(conn);
            exit(EXIT_FAILURE);
        }

        long max_id = strtol(PQgetvalue(res, 0, 0), NULL, 0);
        if (errno == ERANGE) {
            perror("strtol");
            exit(EXIT_FAILURE);
        }
        PQclear(res);

        long new_id = max_id + 1;
        snprintf(query, sizeof(query), "INSERT INTO tasks (id, description) VALUES (%ld, '%s');", new_id, todo.tasks[i]);
        res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            fprintf(stderr, "Insertion of task failed: %s\n", PQerrorMessage(conn));
            PQclear(res);
            PQfinish(conn);
            exit(EXIT_FAILURE);
        }

        printf("Adding of item \"%s\" successful\n", todo.tasks[i]);
        PQclear(res);
    }

    PQfinish(conn);
}

void remove_tasks(db_t todo) {
    char query[BUFSIZ];
    PGresult *res;

    PGconn *conn = connect_to_db(todo);
    if (conn == NULL) {
        perror("conn");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 2; i < todo.no_tasks; ++i) {
        long id = strtol(todo.tasks[i], NULL, 0);
        if (errno == ERANGE) {
            perror("strtol");
            exit(EXIT_FAILURE);
        }

        // Check if the exact ID exists
        snprintf(query, sizeof(query), "SELECT id FROM tasks WHERE id = %ld;", id);

        res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Selection of task ID failed: %s\n", PQerrorMessage(conn));
            PQclear(res);
            continue;
        }

        // Check if the query returned any rows (task exists)
        if (PQntuples(res) == 0) {
            printf("Task with ID %ld not found\n", id);
            PQclear(res);
            continue;
        }

        PQclear(res);

        // Delete the task with the exact ID
        snprintf(query, sizeof(query), "DELETE FROM tasks WHERE id = %ld;", id);
        res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            fprintf(stderr, "Deletion of task failed: %s\n", PQerrorMessage(conn));
            PQclear(res);
            continue;
        }

        printf("Deletion of item %ld successful\n", id);
        PQclear(res);
    }

    PQfinish(conn);
}

void edit_tasks(db_t todo, const long id, const char *new_description) {
    char query[BUFSIZ];
    PGresult *res;

    PGconn *conn = connect_to_db(todo);
    if (conn == NULL) {
        perror("conn");
        exit(EXIT_FAILURE);
    }

    // Check if the task with the given ID exists
    snprintf(query, sizeof(query), "SELECT id FROM tasks WHERE id = %ld;", id);
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Selection of task ID failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(EXIT_FAILURE);
    }

    // Check if the query returned any rows (task exists)
    if (PQntuples(res) == 0) {
        printf("Task with ID %ld not found\n", id);
        PQclear(res);
        PQfinish(conn);
        return;
    }

    PQclear(res);

    // Update the task with the new description
    snprintf(query, sizeof(query), "UPDATE tasks SET description = '%s' WHERE id = %ld;", new_description, id);
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Update of task failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(EXIT_FAILURE);
    }

    printf("Update of item %ld successful\n", id);
    PQclear(res);

    PQfinish(conn);
}

void print_tasks(db_t todo) {
    PGconn *conn = connect_to_db(todo);
    if (conn == NULL) {
        perror("conn");
        exit(EXIT_FAILURE);
    }

    PGresult *res = PQexec(conn, "SELECT * FROM tasks ORDER BY id;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Selection of tasks failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(EXIT_FAILURE);
    }

    int rows = PQntuples(res);
    if (rows == 0) {
        printf("Empty list!\n");
    } else {
        printf("Todo list:\n");
        for (int i = 0; i < rows; ++i) {
            char *description = PQgetvalue(res, i, 1);
            char *id = PQgetvalue(res, i, 0);
            printf("(%s) %s\n", id, description);
        }
    }
    PQclear(res);

    PQfinish(conn);
}
