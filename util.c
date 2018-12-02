#include "util.h"

//other modules
void print_hex(int* hex_value, int hex_size){
    printf("0x");
    for(int i = 0; i < hex_size; i++){
        printf("%X", hex_value[i]);
    }
    printf("\n");

    return;
}
void print_bit(int* bitwise_value, int bit_size){
    int* hex_value = bitwise_to_hex(bitwise_value, bit_size);
    print_hex(hex_value, bit_size / 4);

    free(hex_value);
    hex_value = NULL;

    return;
}
int* hex_to_bitwise(int* hex_input, int hex_size){
    int* ret_val = (int*)malloc(sizeof(int) * (hex_size * 4));
    int* hex_value = array_init(hex_size);
    int temp = 0x0;

    for(int i = 0; i < hex_size; i++){
        hex_value[i] = hex_input[i];
    }

    for(int i = 0; i < hex_size; i++){
        temp = hex_value[i];
        if(hex_value[i] >= 0x8){
            ret_val[i * 4] = 1;
            hex_value[i] -= 0x8;
        }
        else{
            ret_val[i * 4] = 0;
        }
        if(hex_value[i] >= 0x4){
            ret_val[i * 4 + 1] = 1;
            hex_value[i] -= 0x4;
        }
        else{
            ret_val[i * 4 + 1] = 0;
        }
        if(hex_value[i] / 0x2){
            ret_val[i * 4 + 2] = 1;
            hex_value[i] -= 0x2;
        }
        else{
            ret_val[i * 4 + 2] = 0;
        }
        if(hex_value[i] == 0x1){
            ret_val[i * 4 + 3] = 1;
            hex_value[i] = temp;
        }
        else{
            ret_val[i * 4 + 3] = 0;
        }
    }
    return ret_val;
}
int* bitwise_to_hex(int* bitwise_value, int bit_size){
    int* ret_val = (int*)malloc(sizeof(int) * bit_size / 4);
    for(int i = 0; i < bit_size / 4; i++){
        ret_val[i] = bitwise_value[i * 4] * 8 + bitwise_value[i * 4 + 1] * 4 + bitwise_value[i * 4 + 2] * 2 + bitwise_value[i * 4 + 3];
    }

    return ret_val;
}
int* array_init(int size){
    int* array = (int*)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++){
        array[i] = 0;
    }

    return array;
}
void bitwise_shift_left(int* array, int array_size, int repeat){
    int temp = array[0];

    for(int i = 1; i < array_size; i++){
        array[i - 1] = array[i];
    }
    array[array_size - 1] = temp;

    if(repeat <= 1){
        return;
    }
    else{
        bitwise_shift_left(array, array_size, repeat - 1);
    }
}
void bitwise_xor(int* bit_a, int* bit_b, int size){
    for(int i = 0; i < size; i++){
        bit_a[i] = bit_a[i]^bit_b[i];
    }

    return;
}
void array_shallow_copy(int* array1, int* array2, int size){
    for(int i = 0; i < size; i++){
        array1[i] = array2[i];
    }

    return;
}
void sys_log(char* message){
    printf("System log: %s\n", message);

    return;
}
int* string_to_hex(char* input, int size){
    int* ret_val = (int*)malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++){
        if(input[i] >= '0' && input[i] < ':')ret_val[i] = input[i] - '0';
        else if(input[i] >= 'a' && input[i] < 'g')ret_val[i] = input[i] - 'a' + 10;
        else if(input[i] >= 'A' && input[i] < 'G')ret_val[i] = input[i] - 'A' + 10;
        else input[i] = 0;
        printf("%d\n", input[i]);
    }

    return ret_val;
}


int* byte_to_int(char *buffer, int size){
  int* intarray = (int*)malloc(sizeof(int) * (size) * 8);
  int element;

  for(int j = 0; j < size; j++){
    element = buffer[j];
    int flag = 0;

    if(element < 0){
      flag = 1;
      element *= -1;
    }

    for(int i = 7; i >= 0 ; i--){
        intarray[8*j + i] = element % 2;
        element >>= 1;
    }

    if(flag == 1){
      for(int i = 7; i > 0 ; i--)
        (intarray[8*j + i] == 0) ? (intarray[8*j + i] = 1) : (intarray[8*j + i] = 0);
      intarray[8*j + 7] += 1;

      for(int i = 7; i > 0 ; i--){
        if(intarray[8*j + i] == 2){
          intarray[8*j + i] = 0;
          intarray[8*j + i - 1] += 1;
        }
        else break;
      }
      intarray[8*j] = 1;
    }
  }

  return intarray;
}


char* int_to_byte(int* record, int size){
    int* buffer = array_init(size);
    array_shallow_copy(buffer, record, size);
    char* bytearray = char_array_init(size / 8);

    int flag = 0;
    int data = 0;


    for(int i = 0; i < size / 8 ; i++){
        flag = 0;
        data = 0;

        if(buffer[8*i] == 1)
        flag = 1;

        if(flag == 0){
            for(int j = 7; j > 0 ; j--){
                data += pow(2.0,(7-j)) * buffer[8*i + j];
            }
        }
        else if (flag == 1){

            for(int j = 7; j > 0 ; j--)
                (buffer[8*i + j] == 0) ? (buffer[8*i + j] = 1) : (buffer[8*i + j] = 0);

            buffer[8*i + 7] += 1;
            for(int j = 7; j > 0 ; j--){
                if(buffer[8*i + j] == 2){
                    buffer[8*i + j] = 0;
                    buffer[8*i + j - 1] += 1;
                }
                else break;
            }

            if(buffer[8*i] == 2) data += pow(2.0,7);

            for(int j = 7; j > 0 ; j--)
                data += pow(2.0,(7-j)) * buffer[8*i + j];

            data *= -1;
        }
        bytearray[i] = data;
    }

    free(buffer);
    buffer = NULL;

    return bytearray;
}

char* char_array_init(int size){
    char* array = (char*)malloc(sizeof(char) * size);
    for(int i = 0; i < size; i++){
        array[i] = 0;
    }

    return array;
}

void char_array_shallow_copy(char* array1, char* array2, int base1, int base2, int size){
    for(int i = 0; i < size; i++){
        array1[i + base1] = array2[i + base2];
    }

    return;
}

char* encapsulate_des_compatable_size(char* buffer, int size){
    int padding_size = 8 - ((size + ENCAP_HEADER_SIZE) % 8);
    int record_size = encap_size(buffer, size);
    char* record = char_array_init(record_size);
    char* record_header = char_array_init(ENCAP_HEADER_SIZE);

    record_header[0] = (((size / CHAR_SIZE) / CHAR_SIZE) / CHAR_SIZE) - 128;
    record_header[1] = ((size / CHAR_SIZE) / CHAR_SIZE) - 128;
    record_header[2] = (size / CHAR_SIZE) - 128;
    record_header[3] = (size % CHAR_SIZE) - 128;

    char_array_shallow_copy(record, record_header, 0, 0, ENCAP_HEADER_SIZE);
    char_array_shallow_copy(record, buffer, ENCAP_HEADER_SIZE, 0, size);
    for(int i = ENCAP_HEADER_SIZE + size; i < ENCAP_HEADER_SIZE + size + padding_size; i++){
        record[i] = 0;
    }

    return record;
}

int encap_size(char* buffer, int size){
    int padding_size = 8 - ((size + ENCAP_HEADER_SIZE) % 8);
    int record_size = size + ENCAP_HEADER_SIZE + padding_size;

    return record_size;
}

char* decapsulate_des_compatable_size(char* buffer){
    int size = decap_size(buffer);
    char* record = char_array_init(size);

    char_array_shallow_copy(record, buffer, 0, ENCAP_HEADER_SIZE, size);

    return record;
}

int decap_size(char* buffer){
    int size = (buffer[0]+128)*CHAR_SIZE*CHAR_SIZE*CHAR_SIZE + (buffer[1]+128)*CHAR_SIZE*CHAR_SIZE + (buffer[2]+128)*CHAR_SIZE + (buffer[3]+128);

    return size;
}

int base64_encode_size(int size){
    int ret = 0;

    if(size % 3 == 0){
        ret = (size / 3) * 4;
    }
    else{
        ret = ((size / 3) * 4) + 4;
    }

    return ret;
}

int base64_decode_size(char* record, int size){
    int ret = 0;

    if(record[size - 1] == '='){
        if(record[size - 2] == '='){
            ret = ((size - 4) / 4) * 3 + 1;
        }
        else{
            ret = ((size - 4) / 4) * 3 + 2;
        }
    }
    else{
        ret = (size / 4) * 3;
    }

    return ret;
}

//base64 int to char
char* base64_encode(char* byte_record, int size){
    char base64[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
    };
    int* record = byte_to_int(byte_record, size);
    int temp = 0;
    char* encoded = char_array_init(base64_encode_size(size));
    int temp_size = (size / 3) * 4;


    for(int j = 0; j < temp_size; j++){
        temp = 0;
        for(int i = 0; i < 6; i++){
            temp += record[j * 6 + i] * pow(2, 5 - i);
        }
        encoded[j] = base64[temp];
    }

    if(size % 3 == 1){
        temp = 0;
        for(int i = 0; i < 6; i++){
            temp += record[temp_size * 6 + i] * pow(2, 5 - i);
        }
        encoded[temp_size] = base64[temp];

        temp = (record[(temp_size + 1) * 6] * 32) + (record[(temp_size + 1) * 6 + 1] * 16);
        encoded[temp_size + 1] = base64[temp];

        encoded[temp_size + 2] = '=';
        encoded[temp_size + 3] = '=';
    }

    if(size % 3 == 2){
        temp = 0;
        for(int i = 0; i < 6; i++){
            temp += record[temp_size * 6 + i] * pow(2, 5 - i);
        }
        encoded[temp_size] = base64[temp];

        temp = 0;
        for(int i = 0; i < 6; i++){
            temp += record[(temp_size + 1) * 6 + i] * pow(2, 5 - i);
        }
        encoded[temp_size+1] = base64[temp];

        temp = (record[(temp_size + 2) * 6] * 32) + (record[(temp_size + 2) * 6 + 1] * 16) + (record[(temp_size + 2) * 6 + 2] * 8) + (record[(temp_size + 2) * 6 + 3] * 4);
        encoded[temp_size + 2] = base64[temp];

        encoded[temp_size + 3] = '=';
    }

    return encoded;
}

char* base64_decode(char* record, int size){
    int temp_size = base64_decode_size(record, size);
    int* temp_record = array_init(temp_size * 8);
    char* decoded = NULL;
    int temp = 0;


    for(int i = 0; i < size - 4; i++){
        temp = base64_lookup(record[i]);

        if(temp >= 32){
            temp_record[i * 6] = 1;
            temp -= 32;
        }
        else{
            temp_record[i * 6] = 0;
        }

        if(temp >= 16){
            temp_record[i * 6 + 1] = 1;
            temp -= 16;
        }
        else{
            temp_record[i * 6 + 1] = 0;
        }

        if(temp >= 8){
            temp_record[i * 6 + 2] = 1;
            temp -= 8;
        }
        else{
            temp_record[i * 6 + 2] = 0;
        }

        if(temp >= 4){
            temp_record[i * 6 + 3] = 1;
            temp -= 4;
        }
        else{
            temp_record[i * 6 + 3] = 0;
        }

        if(temp >= 2){
            temp_record[i * 6 + 4] = 1;
            temp -= 2;
        }
        else{
            temp_record[i * 6 + 4] = 0;
        }

        temp_record[i * 6 + 5] = temp;
    }

    if(record[size - 1] == '='){
        if(record[size - 2] == '='){
            temp = base64_lookup(record[size - 4]);

            if(temp >= 32){
                temp_record[size - 4 * 6] = 1;
                temp -= 32;
            }

            else{
                temp_record[size - 4 * 6] = 0;
            }

            if(temp >= 16){
                temp_record[size - 4 * 6 + 1] = 1;
                temp -= 16;
            }
            else{
                temp_record[size - 4 * 6 + 1] = 0;
            }

            if(temp >= 8){
                temp_record[size - 4 * 6 + 2] = 1;
                temp -= 8;
            }
            else{
                temp_record[size - 4 * 6 + 2] = 0;
            }

            if(temp >= 4){
                temp_record[size - 4 * 6 + 3] = 1;
                temp -= 4;
            }
            else{
                temp_record[size - 4 * 6 + 3] = 0;
            }

            if(temp >= 2){
                temp_record[size - 4 * 6 + 4] = 1;
                temp -= 2;
            }
            else{
                temp_record[size - 4 * 6 + 4] = 0;
            }

            temp_record[size - 4 * 6 + 5] = temp;

            temp = base64_lookup(record[size - 3]);

            if(temp >= 32){
                temp_record[size - 3 * 6] = 1;
                temp -= 32;
            }

            else{
                temp_record[size - 3 * 6] = 0;
            }

            if(temp >= 16){
                temp_record[size - 3 * 6 + 1] = 1;
                temp -= 16;
            }
            else{
                temp_record[size - 3 * 6 + 1] = 0;
            }

        }
        else{
            temp = base64_lookup(record[size - 4]);

            if(temp >= 32){
                temp_record[size - 4 * 6] = 1;
                temp -= 32;
            }

            else{
                temp_record[size - 4 * 6] = 0;
            }

            if(temp >= 16){
                temp_record[size - 4 * 6 + 1] = 1;
                temp -= 16;
            }
            else{
                temp_record[size - 4 * 6 + 1] = 0;
            }

            if(temp >= 8){
                temp_record[size - 4 * 6 + 2] = 1;
                temp -= 8;
            }
            else{
                temp_record[size - 4 * 6 + 2] = 0;
            }

            if(temp >= 4){
                temp_record[size - 4 * 6 + 3] = 1;
                temp -= 4;
            }
            else{
                temp_record[size - 4 * 6 + 3] = 0;
            }

            if(temp >= 2){
                temp_record[size - 4 * 6 + 4] = 1;
                temp -= 2;
            }
            else{
                temp_record[size - 4 * 6 + 4] = 0;
            }

            temp_record[size - 4 * 6 + 5] = temp;

            temp = base64_lookup(record[size - 3]);

            if(temp >= 32){
                temp_record[size - 3 * 6] = 1;
                temp -= 32;
            }

            else{
                temp_record[size - 3 * 6] = 0;
            }

            if(temp >= 16){
                temp_record[size - 3 * 6 + 1] = 1;
                temp -= 16;
            }
            else{
                temp_record[size - 3 * 6 + 1] = 0;
            }

            if(temp >= 8){
                temp_record[size - 3 * 6 + 2] = 1;
                temp -= 8;
            }
            else{
                temp_record[size - 3 * 6 + 2] = 0;
            }

            if(temp >= 4){
                temp_record[size - 3 * 6 + 3] = 1;
                temp -= 4;
            }
            else{
                temp_record[size - 3 * 6 + 3] = 0;
            }

            if(temp >= 2){
                temp_record[size - 3 * 6 + 4] = 1;
                temp -= 2;
            }
            else{
                temp_record[size - 3 * 6 + 4] = 0;
            }

            temp_record[size - 3 * 6 + 5] = temp;

            temp = base64_lookup(record[size - 2]);

            if(temp >= 32){
                temp_record[size - 2 * 6] = 1;
                temp -= 32;
            }

            else{
                temp_record[size - 2 * 6] = 0;
            }

            if(temp >= 16){
                temp_record[size - 2 * 6 + 1] = 1;
                temp -= 16;
            }
            else{
                temp_record[size - 2 * 6 + 1] = 0;
            }

            if(temp >= 8){
                temp_record[size - 2 * 6 + 2] = 1;
                temp -= 8;
            }
            else{
                temp_record[size - 2 * 6 + 2] = 0;
            }

            if(temp >= 4){
                temp_record[size - 2 * 6 + 3] = 1;
                temp -= 4;
            }
            else{
                temp_record[size - 2 * 6 + 3] = 0;
            }
        }
    }
    else{
        for(int i = size - 4; i < size; i++){
            temp = base64_lookup(record[i]);

            if(temp >= 32){
                temp_record[i * 6] = 1;
                temp -= 32;
            }
            else{
                temp_record[i * 6] = 0;
            }

            if(temp >= 16){
                temp_record[i * 6 + 1] = 1;
                temp -= 16;
            }
            else{
                temp_record[i * 6 + 1] = 0;
            }

            if(temp >= 8){
                temp_record[i * 6 + 2] = 1;
                temp -= 8;
            }
            else{
                temp_record[i * 6 + 2] = 0;
            }

            if(temp >= 4){
                temp_record[i * 6 + 3] = 1;
                temp -= 4;
            }
            else{
                temp_record[i * 6 + 3] = 0;
            }

            if(temp >= 2){
                temp_record[i * 6 + 4] = 1;
                temp -= 2;
            }
            else{
                temp_record[i * 6 + 4] = 0;
            }

            temp_record[i * 6 + 5] = temp;
        }
    }

    decoded = int_to_byte(temp_record, temp_size * 8);
    free(temp_record);
    temp_record = NULL;

    return decoded;
}

int base64_lookup(char input){
    int temp = 0;

    char base64[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
    };

    for(int i = 0; i < 64; i++){
        if(base64[i] == input){
            temp = i;
            break;
        }
    }

    return temp;
}

void char_array_print(char* record, int offset, int end, int flag){
    if(offset > end){
        sys_log("캐릭터 배열 출력 실패: offset이 end보다 큼");
        return;
    }

    if(flag == 1){
        for(int i = offset; i < end; i++){
            printf("%4d ",record[i]);
            if(i % 16 == 15){
                printf("\n");
            }
        }
        printf("\n");
    }
    else{
        for(int i = offset; i < end; i++){
            printf("%c ",record[i]);
            if(i % 16 == 15){
                printf("\n");
            }
        }
        printf("\n");
    }

    return;
}

void int_array_print(int* record, int offset, int end){
    if(offset > end){
        sys_log("인테저 배열 출력 실패: offset이 end보다 큼");
        return;
    }

    for(int i = offset; i < end; i++){
        printf("%d", record[i]);
        if(i % 8 == 7){
            printf(" ");
        }
        if(i % 64 == 63){
            printf("\n");
        }
    }
    printf("\n");

    return;
}


int filesize(char* filename){
    FILE* fileptr = NULL;
    int filelen;

    fileptr = fopen(filename, "rb");                   // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);                       // Jump to the end of the file
    filelen = ftell(fileptr);                          // Get the current byte offset in the file
    rewind(fileptr);

    fclose(fileptr); // Close the file
    fileptr = NULL;

    return filelen;
}

char* file_byte_read(char* filename){
    FILE* fp;
    size_t size;
    long length;
    char* buffer;
    char* encap;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        sys_log("file open error");
        return 0;
    }

    /* Obtain file size */
    if (fseek(fp, 0, SEEK_END) != 0) {
        sys_log("repositioning error");
        return 0;
    }
    length = ftell(fp);
    if (fseek(fp, 0L, SEEK_SET) != 0) {
        sys_log("repositioning error");
        return 0;
    }

    /* Allocate memory to contain whole file */
    buffer = (char*)malloc(length);
    if (buffer == NULL) {
        /* Handle memory allocation error */
        sys_log("memory alloc error");
    }

    /* size assigned here in some other code */
    if (fread(buffer, 1, length, fp) < length) {
        sys_log("file open error");
        return 0;
    }
    fclose(fp);

    return buffer;
}


void file_byte_write(char* filename, char* buffer, int size){
    FILE* fileptr = NULL;

    fileptr = fopen(filename, "wb");
    if (fileptr == NULL) {
        sys_log("file open error");
        return;
    }

    fwrite(buffer, 1, (long)size, fileptr);

    fclose(fileptr); // Close the file
    fileptr = NULL;
}
