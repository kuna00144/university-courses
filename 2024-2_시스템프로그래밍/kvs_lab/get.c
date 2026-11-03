#include "kvs.h"

char* get(kvs_t *db_instance, const char *key) {
    Node *current = db_instance->header;
    for (int i = db_instance->height - 1; i >= 0; i--) {
        while (current->next[i] != NULL && strcmp(current->next[i]->key, key) < 0) {
            current = current->next[i];
        }
    }
    current = current->next[0];

    if (current != NULL && strcmp(current->key, key) == 0) {
        return current->value;
    }
    return NULL;
}
