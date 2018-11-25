#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define CHAR_SIZE 256
#define ENCAP_HEADER_SIZE 4

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
char* int_to_byte(int*, int);
int* byte_to_int(char*, int);

char* char_array_init(int);
void char_array_shallow_copy(char*, char*, int, int, int);
char* encapsulate_des_compatable_size(char*, int);
int encap_size(char*, int);
char* decapsulate_des_compatable_size(char*);
int decap_size(char*);

char* base64_encode(int*, int);
int* base64_decode(char*, int);
int base64_lookup(char);

#endif
