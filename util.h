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

char* char_array_init(int);                                 //캐릭터 배열를 생성해서 반환, (배열 길이)
void char_array_shallow_copy(char*, char*, int, int, int);  //캐릭터 배열 얕은 복사 (붙여넣을 배열, 복사할 배열, 붙여넣을 배열 offset, 복사할 배열 offset, 배열 길이)
char* encapsulate_des_compatable_size(char*, int);          //바이트 배열을 des가 가능한 8바이트 단위로 만듦 (목표 바이트 배열, 배열 길이)
int encap_size(char*, int);                                 //encapsulate_des_compatable_size()함수의 리턴값의 배열 길이를 반환함 (목표 바이트 배열, 배열 길이)
char* decapsulate_des_compatable_size(char*);               //des가능하게 만들었던 배열을 다시 원래 배열로 되돌림 (목표 바이트 배열)
int decap_size(char*);                                      //마찬가지로 위 함수의 리턴값의 배열 길이를 반환

int base64_encode_size(int);            //특정길이의 바이트 배열을 base64로 인코딩 했을 때 나오는 배열의 길이 (원래 배열의 길이)
int base64_decode_size(char*, int);     //base64로 인코딩 된 배열을 다시 디코딩 했을 때 나오는 배열의 길이 (인코딩 된 배열, 그 배열의 길이)
char* base64_encode(char*, int);        //배열을 base64로 인코딩함 (바이트 배열, 배열 길이)
char* base64_decode(char*, int);        //배열을 base64로 디코딩함 (바이트 배열, 배열 길이)
int base64_lookup(char);          

void char_array_print(char*, int, int, int);    //바이트 배열을 오프셋 부터 엔드까지 콘솔에 출력함 (배열, 오프셋, 엔드, 1이면 숫자로 출력하고 1 이외에는 캐릭터로 출력)
void int_array_print(int*, int, int);           //비트 배열을 오프셋 부터 엔드까지 콘솔에 출력함 (배열, 오프셋, 엔드)

#endif
