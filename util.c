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


char* int_to_byte(int* buffer, int size){
  char* bytearray = (char*)malloc(sizeof(char) * (size) / 8);
  // char* bytearray = char_array_init(size / 8);

  for(int i = 0; i < size / 8 ; i++){
    int flag = 0;
    int data = 0;

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
        else break;}

      for(int j = 7; j > 0 ; j--)
        data += pow(2.0,(7-j)) * buffer[8*i + j];

      data *= -1;
    }
    bytearray[i] = data;
  }

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
