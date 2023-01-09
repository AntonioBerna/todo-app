#include <stdlib.h>

#include "psql.h"

PGconn *connect_to_database(void) {
    PGconn *conn = PQsetdbLogin(NULL, PORT, NULL, NULL, DATABASE, USERNAME, PASSWORD);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        return NULL;
    }
    return conn;
}

void add_task(const char *description) {
    int min_id = 1;
    char *endptr;
    char query[BUFFER_SIZE];

    PGconn *conn = connect_to_database();
    if (conn == NULL) {
        return;
    }

    PGresult *res = PQexec(conn, SELECT_TASKS_QUERY);
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            int id = (int)strtol(PQgetvalue(res, i, 0), &endptr, BASE);
            if (id == min_id) {
                min_id++;
            } else {
                break;
            }
        }
    }
    PQclear(res);

    sprintf(query, "INSERT INTO tasks (id, description) VALUES (%d, '%s');", min_id, description);
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Insertion of task failed: %s\n", PQerrorMessage(conn));
    }

    PQclear(res);
    PQfinish(conn);
}

void delete_task(int id) {
    char *endptr;
    char query[BUFFER_SIZE];

    PGconn *conn = connect_to_database();
    if (conn == NULL) {
        return;
    }

    sprintf(query, "SELECT MIN(id) FROM tasks WHERE id >= %d;", id);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Selection of task ID failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return;
    }

    int rows = PQntuples(res);
    if (rows == 0) {
        printf("Task not found\n");
        PQclear(res);
        PQfinish(conn);
        return;
    }

    int task_id = (int)strtol(PQgetvalue(res, 0, 0), &endptr, BASE);
    PQclear(res);

    sprintf(query, "DELETE FROM tasks WHERE id = %d;", task_id);
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Deletion of task failed: %s\n", PQerrorMessage(conn));
    }

    PQclear(res);
    PQfinish(conn);
}

void print_tasks(void) {
    char *description;

    PGconn *conn = connect_to_database();
    if (conn == NULL) {
        return;
    }
    
    PGresult *res = PQexec(conn, SELECT_TASKS_QUERY);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Selection of tasks failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return;
    }
    
    int rows = PQntuples(res);
    if (rows == 0) {
        printf("Lista vuota!\n");
    } else {
        for (int i = 0; i < rows; i++) {
            description = PQgetvalue(res, i, 1);
            printf("%d - %s\n", i + 1, description);
        }
    }
    
    PQclear(res);
    PQfinish(conn);
}

