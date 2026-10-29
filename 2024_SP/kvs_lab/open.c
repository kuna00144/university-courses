#include "kvs.h"

kvs_t* open() {
    kvs_t *db_instance = (kvs_t*)malloc(sizeof(kvs_t));
    if (!db_instance) return NULL;

    db_instance->height = 1;
    db_instance->itemCount = 0;

    db_instance->header = (Node*)malloc(sizeof(Node));
    db_instance->header->next = (Node**)malloc(sizeof(Node*) * MAX_HEIGHT);
    for (int i = 0; i < MAX_HEIGHT; i++) {
        db_instance->header->next[i] = NULL;
    }

    return db_instance;
}
