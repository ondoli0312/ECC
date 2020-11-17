#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef unsigned long long Long;
typedef unsigned int word;
typedef unsigned short int sword;
typedef unsigned char byte;

#define ROTL(x, n)			(((x) << (n)) | ((x) >> (32 - (n))))
#define ENDIAN_CHANGE(X)	((ROTL((X),  8) & 0x00ff00ff) | (ROTL((X), 24) & 0xff00ff00))

__int64 cpucycles();
unsigned char getHex(unsigned char ch);
void convertStr2Byte(unsigned char* from, int size, unsigned char* to);