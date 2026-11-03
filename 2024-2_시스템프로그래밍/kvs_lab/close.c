#include "kvs.h"

int close(kvs_t *db_instance) {
    Node *current_node = db_instance->header;
    while (current_node != NULL) {
        Node *next_node = current_node->next[0];
        free(current_node->value);
        free(current_node->next);
        free(current_node);
        current_node = next_node;
    }
    free(db_instance);
    return 0;
}
