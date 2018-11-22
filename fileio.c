#include "fileio.h"
#include "util.h"

char* encrypt_file_byte_read(char* filename){
    FILE* fileptr;
    char* buffer;
    long filelen;
    char* encap = NULL;
    int encap_size_val = 0;

    fileptr = fopen(filename, "rb");                   // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);                            // Jump to the end of the file
    filelen = ftell(fileptr);                               // Get the current byte offset in the file
    rewind(fileptr);                                        // Jump back to the beginning of the file

    buffer = (char *)malloc((filelen+1) * sizeof(char));
    fread(buffer, filelen, 1, fileptr);

    encap = encapsulate_des_compatable_size(buffer, filelen + 1);
    encap_size_val = encap_size(buffer, filelen + 1);

    fclose(fileptr); // Close the file
    free(buffer);
    buffer = NULL;

    return encap;
}

void encrypt_file_byte_write(char* filename, char* buffer){
    FILE* fileptr;
    char* buffer;
    long filelen;
    char* decap = NULL;
    int decap_size_val = 0;

    char* locked_name = char_array_init(sizeof(filename) / sizeof(char));

    fileptr = fopen(filename, "wb");                   // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);                            // Jump to the end of the file
    filelen = ftell(fileptr);                               // Get the current byte offset in the file
    rewind(fileptr);                                        // Jump back to the beginning of the file

    buffer = (char *)malloc((filelen+1) * sizeof(char));
    fread(buffer, filelen, 1, fileptr);

    encap = encapsulate_des_compatable_size(buffer, filelen + 1);
    encap_size_val = encap_size(buffer, filelen + 1);

    fclose(fileptr); // Close the file
    free(buffer);
    buffer = NULL;

    return encap;
}