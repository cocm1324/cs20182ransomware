#include "ransomware.h"

int main(){
    int* key = hex_to_bitwise(string_to_hex("AABB09182736CCDD", BLOCK_SIZE / 4), BLOCK_SIZE / 4);
    int* plaintext = hex_to_bitwise(string_to_hex("123456ABCD132536", BLOCK_SIZE / 4), BLOCK_SIZE/4);
    int* ciphertext = array_init(BLOCK_SIZE);

    des_encrypt(key, plaintext);
    array_shallow_copy(ciphertext, plaintext, BLOCK_SIZE);
    print_bit(plaintext, BLOCK_SIZE);
    des_decrypt(key, ciphertext);
    print_bit(ciphertext, BLOCK_SIZE);
    
    return 0;
}