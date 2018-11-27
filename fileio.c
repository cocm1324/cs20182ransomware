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

char* file_byte_read(char* filename){
    FILE* fp;
    size_t size;
    long length;
    char* buffer;
    char* encap;
 
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        sys_log("file open error");
        return 0;
    }

    /* Obtain file size */
    if (fseek(fp, 0, SEEK_END) != 0) {
        sys_log("repositioning error");
        return 0;
    }
    length = ftell(fp);
    if (fseek(fp, 0L, SEEK_SET) != 0) {
        sys_log("repositioning error");
        return 0;
    }
 
    /* Allocate memory to contain whole file */
    buffer = (char*)malloc(length);
    if (buffer == NULL) {
        /* Handle memory allocation error */
        sys_log("memory alloc error");
    }
     
    /* size assigned here in some other code */
    if (fread(buffer, 1, length, fp) < length) {
        sys_log("file open error");
        return 0;
    }
    fclose(fp);
    
    return buffer;
}


void file_byte_write(char* filename, char* buffer, int size){
    FILE* fileptr = NULL;

    fileptr = fopen(filename, "wb");
    if (fileptr == NULL) {
        sys_log("file open error");
        return;
    }

    fwrite(buffer, 1, (long)size, fileptr);

    fclose(fileptr); // Close the file
    fileptr = NULL;
}