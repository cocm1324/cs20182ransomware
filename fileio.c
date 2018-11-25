#include "fileio.h"
#include "util.h"

int filesize(char* filename){
    FILE* fileptr = NULL;
    int filelen;

    fileptr = fopen(filename, "rb");                   // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);                       // Jump to the end of the file
    filelen = ftell(fileptr);                          // Get the current byte offset in the file
    rewind(fileptr);

    fclose(fileptr); // Close the file
    fileptr = NULL;

    return filelen + 1;
}

char* encrypt_file_byte_read(char* filename){
    FILE* fileptr = NULL;
    char* buffer = NULL;
    char* encap = NULL;
    long filelen;
    int encap_size_val = 0;

    fileptr = fopen(filename, "rb");                   // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);                       // Jump to the end of the file
    filelen = ftell(fileptr);                          // Get the current byte offset in the file
    rewind(fileptr);                                   // Jump back to the beginning of the file

    buffer = (char *)malloc((filelen+1) * sizeof(char));
    fread(buffer, filelen, 1, fileptr);

    encap = encapsulate_des_compatable_size(buffer, filelen + 1);
    encap_size_val = encap_size(buffer, filelen + 1);

    fclose(fileptr); // Close the file
    fileptr = NULL;
    free(buffer);
    buffer = NULL;

    return encap;
}

void encrypt_file_byte_write(char* filename, char* buffer, int size){
    FILE* fileptr = NULL;
    int filelen = size;
    int decap_size_val = 0;
    char* decap = NULL;

    decap = char_array_init(filelen + 1);
    char_array_shallow_copy(decap, buffer, 0, ENCAP_HEADER_SIZE, filelen);
    decap[filelen] = '\0';

    fileptr = fopen(filename, "wb");                                                                           
    fwrite(decap, 1, filelen + 1, fileptr);

    fclose(fileptr); // Close the file
    fileptr = NULL;
    free(decap);
    decap = NULL;
}

char* decrypt_file_byte_read(char* filename){
    FILE* fileptr = NULL;
    char* buffer = NULL;
    char* encap = NULL;
    long filelen;
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
    fileptr = NULL;
    free(buffer);
    buffer = NULL;

    return encap;
}

void decrypt_file_byte_write(char* filename, char* buffer){
    FILE* fileptr = NULL;
    char* decap = NULL;
    long filelen;
    int decap_size_val = 0;

    filelen = decap_size(buffer);
    decap = (char*)malloc(sizeof(char) * filelen);
    char_array_shallow_copy(decap, buffer, 0, ENCAP_HEADER_SIZE, filelen);

    fileptr = fopen(filename, "wb");                                          
    rewind(fileptr);                                   
    fwrite(decap, filelen, 1, fileptr);

    fclose(fileptr); // Close the file
    fileptr = NULL;
    free(decap);
    decap = NULL;
}