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
#include "ecb.h"

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
    
    char* encap = NULL;
    char* decap = NULL;

    int encap_size_val, decap_size_val;

    int* int_buffer;
    long filelen;
    char temp = 0;
    
    fileptr = fopen("jackson.jpg", "rb");                   // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);                            // Jump to the end of the file
    filelen = ftell(fileptr);                               // Get the current byte offset in the file
    rewind(fileptr);                                        // Jump back to the beginning of the file

    buffer = (char *)malloc((filelen+1) * sizeof(char));    // Enough memory for file + \0
    int_buffer = (int*)malloc((filelen+1) * 8 * sizeof(int));

    fread(buffer, filelen, 1, fileptr); 

    for(int i = 0; i < filelen + 1; i++){
        temp = buffer[i];
        //printf("temp: %d\n", temp);
        for( int j = 7; j >= 0; j--) {
            //printf("%d: %d\n", 8-j, ( temp >> j ) & 1 ? 1 : 0);
            int_buffer[i * 8 + 7 - j] = ( temp >> j ) & 1 ? 1 : 0;
        }
    }

    for(int i = 0; i < 64; i++){
        printf("%3d ",buffer[i]);
        if(i % 8 == 7){
            printf("\n");
        }
    }

    printf("\n");
    
    for(int i = 0; i < 64 * 8; i++){
        printf("%d",int_buffer[i]);
        if(i % 64 == 63){
            printf("\n");
        }
        else if(i % 8 == 7){
            printf(" ");
        }
    }


    fclose(fileptr); // Close the file
    
    /*
    fp = fopen("sample.docx.locked", "wb");
    fwrite(buffer, filelen, 1, fp);

    fclose(fp);

    */
    

    encap = encapsulate_des_compatable_size(buffer, filelen + 1);
    encap_size_val = encap_size(buffer, filelen + 1);

    for(int i = 0; i < encap_size_val; i++){
        printf("%5d ", encap[i]);
        if(i % 10 == 9){
            printf("\n");
        }
    }

    decap = decapsulate_des_compatable_size(encap);
    decap_size_val = decap_size(encap);

    printf("\n");

    for(int i = 0; i < decap_size_val; i++){
        //printf("%5d ", decap[i]);
        if(i % 10 == 9){
        //    printf("\n");
        }
    }


    free(buffer);
    buffer = NULL;
    free(int_buffer);
    int_buffer = NULL;

    printf("\nfile length: %ld\n", filelen);

    return 0;
}