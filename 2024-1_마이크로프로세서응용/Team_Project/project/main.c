#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 8

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	char *filename = argv[1];
	uint8_t buffer[BUFFER_SIZE];
	size_t bytes_read;
	
	FILE *file = fopen(, "rb");
	if (!file) {
		printf("Error opening file.\n");
		return 1;
	}
	
	printf("Binary data for file: %s\n", filename);
	
	while ((bytes_read = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, file)) > 0) {
		for (size_t i = 0; i < bytes_read; i++) {
			printf("%02X ", buffer[i]);
		}
		printf("\n");
	}
	
	fclose(file);
	return 0;

}