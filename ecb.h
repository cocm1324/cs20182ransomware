#ifndef ECB_H
#define ECB_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <time.h>

void send_keyinfo();
char* rand_key_generator();
int* ecb_des_encrypt(int*, int);
int* ecb_des_decrypt(int*, char*, int);


#endif
