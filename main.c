
/*
* File Name: main.c
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

#include "des.h"
#include "util.h"
#include "ecb.h"
#include "fileio.h"

#define WINDOW 64

int main(){
    /*
        변수 선언 파트
    */

    //1단계: 파일에서 바이트를 추출해내기
    int raw_filelen = 0;
    char* raw_byte = NULL;

    //2단계: 바이트를 des에 맞는 사이즈로 바꾸기
    int encap_len = 0;    
    char* encap = NULL;
    int* encap_bit = NULL;

    //3단계: des로 암호화 하기

    //4단계: byte에서 bit로 바꾸기
    int* encrypted_bit = NULL;
    char* encrypted_byte = NULL;

    //5단계: base64로 인코딩하기
    int encoded_len = 0;
    char* encoded = NULL;

    //6단계: 파일로 저장하기

    //7단계: 파일에서 바이트 추출하기
    int re_filelen = 0;
    char* re_byte = NULL;

    //8단계: base64로 디코딩하기
    int decoded_len = 0;
    char* decoded = NULL;
    

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





    /*
        로직 파트
    */
    
    //1단계: 파일에서 바이트를 추출해내기
    raw_filelen = filesize("jackson.jpg");             //파일 길이 얻기
    raw_byte = file_byte_read("jackson.jpg");          //파일로부터 바이트 얻기

    //sys_log("raw");
    //char_array_print(raw_byte, 0, WINDOW, 1);
    

    //2단계: 바이트를 des에 맞는 사이즈로 바꾸기
    encap_len = encap_size(raw_byte, raw_filelen);
    encap = encapsulate_des_compatable_size(raw_byte, raw_filelen);
    encap_bit = byte_to_int(encap, encap_len);       //바이트로부터 비트 값 얻기

    //sys_log("encap");
    //char_array_print(encap, 0, WINDOW, 1);

    //sys_log("encap bit");
    //int_array_print(encap_bit, 0, WINDOW * 8);


    //3단계: des로 암호화 하기
        //아직 작성되지 않음


     //4단계: byte에서 bit로 바꾸기
    encrypted_bit = array_init(encap_len * 8);
    array_shallow_copy(encrypted_bit, encap_bit, encap_len * 8);    //아직 des가 없어서 encap을 바로 씀
    encrypted_byte = int_to_byte(encrypted_bit, encap_len * 8);

    sys_log("encrypted");
    char_array_print(encrypted_byte, 10000, encap_len, 1);


    //5단계: base64로 인코딩하기
    encoded_len = base64_encode_size(encap_len);
    encoded = base64_encode(encrypted_byte, encap_len);

    //sys_log("encoded");
    //char_array_print(encoded, 0, encoded_len, 0);


    //6단계: 파일로 저장하기
    file_byte_write("jackson.jpg.locked", encoded, encoded_len);


    //7단계: 파일에서 바이트 추출하기
    re_filelen = filesize("jackson.jpg.locked");
    re_byte = file_byte_read("jackson.jpg.locked");

    //sys_log("re byte");
    //char_array_print(re_byte, 0, re_filelen, 0);


    //8단계: base64로 디코딩하기
    decoded_len = base64_decode_size(re_byte, re_filelen);
    decoded = base64_decode(re_byte, re_filelen);

    sys_log("decoded");
    char_array_print(decoded, 10000, decoded_len, 1);

    //현재 base 64 decoding에 문제 있는듯






    /*
        메모리 관리
    */
    free(raw_byte);
    free(encap);
    free(encap_bit);

    free(encrypted_bit);
    free(encrypted_byte);
    free(encoded);

    free(re_byte);
    free(decoded);

    raw_byte = NULL;
    encap = NULL;
    encap_bit = NULL;

    encrypted_bit = NULL;
    encrypted_byte = NULL;
    encoded = NULL;

    re_byte = NULL;
    decoded = NULL;

    return 0;
}
