#include "kvs.h"

int get_random_level() {
    int level = 1;
    while (rand() % 2 && level < MAX_HEIGHT) {
        level++;
    }
    return level;
}

Node* create_node(const char *key, const char *value, int level) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->next = (Node**)malloc(sizeof(Node*) * level);
    strcpy(new_node->key, key);
    new_node->value = strdup(value);
    return new_node;
}

int put(kvs_t *db_instance, const char *key, const char *value) {
    Node *update[MAX_HEIGHT];
    Node *current = db_instance->header;

    for (int i = db_instance->height - 1; i >= 0; i--) {
        while (current->next[i] != NULL && strcmp(current->next[i]->key, key) < 0) {
            current = current->next[i];
        }
        update[i] = current;
    }
    current = current->next[0];

    if (current != NULL && strcmp(current->key, key) == 0) {
        free(current->value);
        current->value = strdup(value);
        return 0;
    }

    int new_level = get_random_level();
    if (new_level > db_instance->height) {
        for (int i = db_instance->height; i < new_level; i++) {
            update[i] = db_instance->header;
        }
        db_instance->height = new_level;
    }

    Node *new_node = create_node(key, value, new_level);
    for (int i = 0; i < new_level; i++) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }
    db_instance->itemCount++;
    return 0;
}
