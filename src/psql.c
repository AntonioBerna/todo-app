#include "psql.h"

void create_database(database_t *db, const char *port, const char *name, const char *username, const char *password) {
    assert(db != NULL);
    db->port = port;
    db->name = name;
    db->username = username;
    db->password = password;
}

PGconn *connect_to_database(database_t *db) {
    PGconn *conn = PQsetdbLogin(NULL, db->port, NULL, NULL, db->name, db->username, db->password);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        return NULL;
    }
    return conn;
}

void add_tasks(database_t *db) {
    char query[BUFSIZ];

    PGconn *conn = connect_to_database(db);
    if (conn == NULL) {
        perror("conn");
        exit(EXIT_FAILURE);
    }

    for (int k = 2; k < db->no_tasks; k++) {
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
        snprintf(query, sizeof(query), "INSERT INTO tasks (id, description) VALUES (%ld, '%s');", new_id, db->tasks[k]);
        res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            fprintf(stderr, "Insertion of task failed: %s\n", PQerrorMessage(conn));
            PQclear(res);
            PQfinish(conn);
            exit(EXIT_FAILURE);
        }
        printf("Adding of item '%s' successful\n", db->tasks[k]);
        PQclear(res);
    }

    PQfinish(conn);
}

void delete_tasks(database_t *db) {
    char query[BUFSIZ];
    long id_to_delete;
    PGresult *res;

    PGconn *conn = connect_to_database(db);
    if (conn == NULL) {
        perror("conn");
        exit(EXIT_FAILURE);
    }

    for (int i = 2; i < db->no_tasks; i++) {
        long id = strtol(db->tasks[i], NULL, 0);
        if (errno == ERANGE) {
            perror("strtol");
            exit(EXIT_FAILURE);
        }
        snprintf(query, sizeof(query), "SELECT MIN(id) FROM tasks WHERE id >= %ld;", id);

        res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            fprintf(stderr, "Selection of task ID failed: %s\n", PQerrorMessage(conn));
            PQclear(res);
            continue;
        }

        if (PQgetisnull(res, 0, 0)) {
            printf("Task with ID %ld not found\n", id);
            PQclear(res);
            continue;
        }

        id_to_delete = strtol(PQgetvalue(res, 0, 0), NULL, 0);
        if (errno == ERANGE) {
            perror("strtol");
            exit(EXIT_FAILURE);
        }
        PQclear(res);

        snprintf(query, sizeof(query), "DELETE FROM tasks WHERE id = %ld;", id_to_delete);
        res = PQexec(conn, query);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            fprintf(stderr, "Deletion of task failed: %s\n", PQerrorMessage(conn));
            PQclear(res);
            continue;
        }
        printf("Deletion of item %s successful\n", db->tasks[i]);
        PQclear(res);
    }

    snprintf(query, sizeof(query), "UPDATE tasks SET id = id - 1 WHERE id > %ld;", id_to_delete);
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Update of task IDs failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(EXIT_FAILURE);
    }
    PQclear(res);

    PQfinish(conn);
}

void print_tasks(database_t *db) {
    PGconn *conn = connect_to_database(db);
    if (conn == NULL) {
        perror("conn");
        exit(EXIT_FAILURE);
    }

    PGresult *res = PQexec(conn, "SELECT * FROM tasks;");
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
        for (int i = 0; i < rows; i++) {
            char *description = PQgetvalue(res, i, 1);
            printf("(%d) %s\n", i + 1, description);
        }
    }
    PQclear(res);

    PQfinish(conn);
}
