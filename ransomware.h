#ifndef RANSOMWARE_H
#define RANSOMWARE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 15000
#define WINDOW 64

void encrypt_single_file(char*, char*, char*);            //파일 명을 넣으면 해당 파일을 암호화 함 (파일이름)
void decrypt_single_file(char*, char*, char*);     //파일 명과 키를 넣으면 해당 파일을 복호화 함 (파일이름, 복호화 키)

#endif