#ifndef FILEIO
#define FILEIO

#include <stdio.h>
#include <stdlib.h>

int filesize(char*);
char* encrypt_file_byte_read(char*);
void encrypt_file_byte_write(char*, char*, int);
char* decrypt_file_byte_read(char*);
void decrypt_file_byte_write(char*, char*);

#endif