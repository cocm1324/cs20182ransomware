#ifndef FILEIO
#define FILEIO

#include <stdio.h>
#include <stdlib.h>

int filesize(char*);                        //해당 파일의 바이트 단위 크기를 얻음 (파일이름)
char* file_byte_read(char*);                //해당 파일의 바이트를 읽어옴 (파일이름)
void file_byte_write(char*, char*, int);    //해당 파일 명으로 바이트를 써서 저장함(파일이름, 바이트 배열, 배열 크기)

#endif