/*
* File Name: ransomware.h
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

#ifndef DES_H
#define DES_H

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 64
#define PART_SIZE 32
#define EXPANSION_SIZE 48
#define KEY_SIZE 56
#define ROUND 16

void des_encrypt(int*, int*);               //des로 암호화. (키, 평문)
void des_decrypt(int*, int*);               //des로 복호화. (키, 암호문)

void pbox(int*, int*, int);
void e_pbox(int*, int*, int*);
void whitner(int*, int*);
void round_sbox(int*, int*, int[8][16][4]);
void s_pbox(int*, int*);
int** key_gen(int*, int*, int*, int);

void print_hex(int*, int); 
void print_bit(int*, int);                  //int 배열을 출력함. (배열 포인터, 배열 길이) 
int* hex_to_bitwise(int*, int);
int* bitwise_to_hex(int*, int);
int* array_init(int);
void bitwise_shift_left(int*, int, int);
void bitwise_xor(int*, int*, int);
void array_shallow_copy(int*, int*, int);   //int 배열을 복사함. (붙여넣을 배열, 복사할 배열, 배열 길이)
void sys_log(char*);                        //시스템 로그를 남김. (시스템 메세지)
int* string_to_hex(char*, int);

#endif