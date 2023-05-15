#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archive_definition.h"

unsigned char **read_data(int amount, char *files[]) {
    unsigned char **hex = arr_memory_allocation(amount);
    for (int i = 0; i < amount; i++)
    {
        FILE *file = fopen(files[i + 1], "rb");
        if (!file) {
            printf("Failed to open file\n");
            exit(1);
        }

        unsigned int size = file_size(file);
        unsigned char buffer[size];
        unsigned int nbytes = fread(buffer, 1, sizeof(buffer), file);
        if (nbytes != size) {
            printf("Failed to read data from file\n");
            exit(1);
        }
        fclose(file);

        hex[i] = str_memory_allocation(size);
        for (unsigned int j = 0; j < size; j++) {
            sprintf((char*)hex[i] + j * 2, "%02X", buffer[j]);
        }
    }
    return hex;
}

unsigned char **arr_memory_allocation(int amount) {
    unsigned char **hex = (unsigned char**)malloc((amount) * sizeof(unsigned char*));
    if (hex == NULL) {
        printf("Memory allocation error");
        exit(1);
    }
    return hex;
}

unsigned char *str_memory_allocation(unsigned int size) {
    unsigned char *str = (unsigned char*)malloc((size * 2 + 1) * sizeof(unsigned char));
    if (str == NULL) {
        printf("Memory allocation error");
        exit(1);
    }
    return str;
}

unsigned int file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    unsigned int size = ftell(file);
    rewind(file);
    return size;
}

void arch_def(int amount, unsigned char **hex, char *files[]){
    for (int i = 0; i < amount; i++) {
        char zip_signature[] = "504B0304";
        char *res = strstr((char *)hex[i], zip_signature);
        if (res == NULL) {
            printf("The file \"%s\" doesn`t contain an archive\n", files[i + 1]);
        }
        else {
            const int header_until_name_len = 52;
            const int header_until_name = 60;
            printf("The file \"%s\" contains an archive\n", files[i + 1]);
            while (res != NULL) {
                char hex_length_name[5];
                strncpy(hex_length_name, res + header_until_name_len + 2, 2);
                strncpy(hex_length_name + 2, res + header_until_name_len, 2);
                hex_length_name[4] = '\0';

                unsigned int dec_length_name = strtol(hex_length_name, NULL, 16);
                char encoded_archive_file_name[dec_length_name * 2 + 1];
                strncpy(encoded_archive_file_name, res + header_until_name, dec_length_name * 2);
                encoded_archive_file_name[dec_length_name * 2] = '\0';

                ascii_decoding(encoded_archive_file_name);
                strcpy((char *)hex[i], res + 8);
                res = strstr((char *)hex[i], zip_signature);
            }
        }
    }
}

void ascii_decoding(char encoded[]) {
    int length = strlen(encoded);
    char hex_pair[3] = {'\0'};
    for (int i = 0; i < length; i += 2) {
        strncpy(hex_pair, &encoded[i], 2);
        unsigned int ascii_code;
        sscanf(hex_pair, "%x", &ascii_code);  // Расшифровка шестнадцатеричного значения
        printf("%c", (char)ascii_code);
    }
    printf("\n");
}

void free_mem(int amount, unsigned char **hex) {
    for (int i = 0; i < amount; i++) {
        free(hex[i]);
    }
    free(hex);
}

