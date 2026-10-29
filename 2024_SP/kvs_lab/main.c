#include "kvs.h"

int main() {
    kvs_t* db_instance = open();
    if (!db_instance) {
        printf("Failed to open kvs\n");
        return -1;
    }

    FILE *input_file = fopen("query.dat", "r");
    if (!input_file) {
        printf("Failed to open query.dat\n");
        close(db_instance);
        return -1;
    }

    FILE *output_file = fopen("answer.dat", "w");
    if (!output_file) {
        printf("Failed to open answer.dat\n");
        fclose(input_file);
        close(db_instance);
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), input_file)) {
        char action[10], key[100], value[100] = "";
        int tokens = sscanf(line, "%9[^,],%99[^,],%99[^\n]", action, key, value);

        if (tokens >= 2 && strcmp(action, "set") == 0) {
            put(db_instance, key, value);
        } else if (tokens >= 2 && strcmp(action, "get") == 0) {
            char *retrieved_value = get(db_instance, key);
            fprintf(output_file, "%s\n", retrieved_value ? retrieved_value : "-1");
        }
    }

    fclose(input_file);
    fclose(output_file);
    close(db_instance);

    return 0;
}
