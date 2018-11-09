/*
* File Name: main.c
* Description: 
* Made by: Gongtuigigi (Jaeeun Cho)
* Student ID: 21300733
* Email: cocm1324@gmail.com
* Lastly Modified: 18.11.10
*
* OS X 10.13.6
* gcc
*
*/

#include "des.h"
#include "util.h"
#include "cbc.h"

int main(){
    /*
    int* key = hex_to_bitwise(string_to_hex("AABB09182736CCDD", BLOCK_SIZE / 4), BLOCK_SIZE / 4);
    int* plaintext = hex_to_bitwise(string_to_hex("123456ABCD132536", BLOCK_SIZE / 4), BLOCK_SIZE/4);
    int* ciphertext = array_init(BLOCK_SIZE);

    des_encrypt(key, plaintext);
    array_shallow_copy(ciphertext, plaintext, BLOCK_SIZE);
    print_bit(plaintext, BLOCK_SIZE);
    des_decrypt(key, ciphertext);
    print_bit(ciphertext, BLOCK_SIZE);
    */

    FILE* fileptr;
    FILE* fp;
    char* buffer;
    long filelen;
    char temp = 0;

    fileptr = fopen("jackson.jpg", "rb");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
    fread(buffer, filelen, 1, fileptr); // Read in the entire file
    
    printf("  1: ");
    for(int i = 0; i < 1024; i++){
        temp = buffer[i];
        for( int j = 7; j >= 0; j-- ) {
            printf( "%d", ( temp >> j ) & 1 ? 1 : 0 );
            if(j == 4){
                printf(" ");
            }
        }
        printf(" ");

        if(i % 8 == 0){
            printf("\n%3d: ", (i / 10) + 2);
        }
    }
    


    fclose(fileptr); // Close the file

    fp = fopen("jackson_modified.jpg", "wb");
    fwrite(buffer, filelen, 1, fp);

    fclose(fp);

    free(buffer);
    buffer=NULL;

    printf("\nfile length: %ld\n", filelen);

    return 0;
}