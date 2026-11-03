#ifndef KVS_H
#define KVS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 10

typedef struct Node {
    char key[100];
    char *value;
    struct Node **next;
} Node;

typedef struct {
    Node *header;
    int height;
    int itemCount;
} kvs_t;

kvs_t* open();
int close(kvs_t *db);
int put(kvs_t *db, const char *key, const char *value);
char* get(kvs_t *db, const char *key);

#endif // KVS_H
