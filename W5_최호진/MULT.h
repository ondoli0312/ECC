#pragma once
#include "Type.h"

void change_value(word* A, int size);
void MULT256_OS_Long_type(word* A, word* B, word* output);
void MULT256_PS_Long_type(word* A, word* B, word* output);
void MULT256_SQU_Long_type(word* A, word* output);

void MULT256_OS_32bit_type(word* X, word* Y, word* out);
void MULT256_PS_32bit_type(word* X, word* Y, word* out);
void MULT256_SQU_32bit_ver_type(word* X, word* out);