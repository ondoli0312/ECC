#pragma once
#include "Type.h"

int addtion256(word* A, word* B, word* output);
int subtract256(word* A, word* B, word* output);
void addtion_mod_P256(word* A, word* B, word* P, word* output);
void subtract_mod_P256(word* A, word* B, word* P, word* output);