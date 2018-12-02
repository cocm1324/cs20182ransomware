
/*
* File Name: main.c
* Description:
* Made by: Gongtuigigi (Jaeeun Cho)
* Student ID: 21300733
* Email: cocm1324@gmail.com
* Lastly Modified: 18.11.27
*
* OS X 10.13.6
* gcc
*
*/

#include "des.h"
#include "util.h"
#include "ecb.h"
#include "ransomware.h"

int main(){
    //encrypt_single_file("sample.docx");
    decrypt_single_file("sample.docx.locked");


    /*

    이 부분은 어떻게 해야할지 잘 모르겠음;;;

    struct _finddata_t fd;
    long* handle;
    int result = 1;
    char* file;
    handle = _findfirst(".\\*.*", &fd); // Set path
    // handle = _findfirst("C:\\Users\\kwonda\\Desktop\\18_2\\*.*", &fd); // path 예시

    if (handle == -1){
        printf("There were no files.\n");
        return;
    }

    int NumOfFile = 0;

    while (result != -1){
        char* fileName= fd.name;

        if( NumOfFile > 1){
            printf("%s \n", fileName);
        }// finish 'If' of NumOfFile
        result = _findnext(handle, &fd);
        NumOfFile++;


    }//finish 'while'. No more files to read

    _findclose(handle);
    */

    return 0;
}
