#ifndef RANSOMWARE_H
#define RANSOMWARE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 20000
#define WINDOW 64

void encrypt_single_file(char*);
void decrypt_single_file(char*);

#endif