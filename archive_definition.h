#ifndef ARCHIVE_DEFINITION_H
#define ARCHIVE_DEFINITION_H

unsigned char **read_data(int amount, char *files[]);
unsigned char **arr_memory_allocation(int amount);
unsigned char *str_memory_allocation(unsigned int size);
unsigned int file_size(FILE *file);
void arch_def(int amount, unsigned char **hex, char *files[]);
void ascii_decoding(char encoded[]);
void free_mem(int amount, unsigned char **hex);

#endif /* ARCHIVE_DEFINITION_H */
