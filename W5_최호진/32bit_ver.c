#include "MULT.h"

void change_value_32bit_ver(sword* A, int size) {

	sword value[32];
	int i = 0;
	for (i = 0; i < size; i++)
		value[i] = A[i];
	for (i = 0; i < size; i++)
		A[i] = value[size - i - 1];
}
void MULT256_OS_32bit_type(word* X, word* Y, word* out) {
	
	int i = 0;
	int j = 0;

	sword A[16];
	sword B[16];
	sword output[32];

	for (i = 0; i < 8; i ++) {
		A[2 * i] = X[i] >> 16;
		A[2 * i + 1] = X[i] & 0xffff;
		B[2 * i] = Y[i] >> 16;
		B[2 * i + 1] = Y[i] & 0xffff;
	}
	sword U = 0;
	sword V = 0;
	word UV = 0;

	change_value_32bit_ver(A, 16);
	change_value_32bit_ver(B, 16);

	for (i = 0; i < 32; i++)
		output[i] = 0;

	for (i = 0; i < 16; i++) {
		U = 0;
		for (j = 0; j < 16; j++) {
			UV = A[i];
			UV *= B[j];
			UV += output[i + j];
			UV += U;

			U = UV >> 16;
			V = UV & 0xffff;

			output[i + j] = V;
		}
		output[i + 16] = U;
	}
	change_value_32bit_ver(output, 32);
	for (i = 0; i < 16; i++) {
		out[i] = (output[2 * i] << 16) | (output[2 * i + 1]);
	}

}
void MULT256_PS_32bit_type(word* X, word* Y, word* out) {

	
	sword R0 = 0;
	sword R1 = 0;
	sword R2 = 0;
	sword U, V = 0;

	word UV = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int carry = 0;

	sword A[16];
	sword B[16];
	sword output[32];

	for (i = 0; i < 8; i++) {
		A[2 * i] = X[i] >> 16;
		A[2 * i + 1] = X[i] & 0xffff;
		B[2 * i] = Y[i] >> 16;
		B[2 * i + 1] = Y[i] & 0xffff;
	}

	change_value_32bit_ver(A, 16);
	change_value_32bit_ver(B, 16);

	for (k = 0; k < 16; k++) {
		j = k;
		for (i = 0; i <= k; i++, j--) {

			UV = A[i];
			UV *= B[j];
			
			U = UV >> 16;
			V = UV & 0xffff;

			R0 = R0 + V;
			if (R0 < V)
				carry = 1;
			else
				carry = 0;

			R1 = R1 + U + carry;
			if (R1 < (U + carry))
				carry = 1;
			else
				carry = 0;

			R2 = R2 + carry;
		}
		output[k] = R0;
		R0 = R1;
		R1 = R2;
		R2 = 0;
	}
	for (k = 16; k < 31; k++) {
		for (i = 15, j = k - 15; j < 16; i--, j++) {
			UV = A[i];
			UV *= B[j];

			U = UV >> 16;
			V = UV & 0xffff;

			R0 = R0 + V;
			if (R0 < V)
				carry = 1;
			else
				carry = 0;

			R1 = R1 + U + carry;
			if (R1 < (U + carry))
				carry = 1;
			else
				carry = 0;

			R2 = R2 + carry;
		}
		output[k] = R0;
		R0 = R1;
		R1 = R2;
		R2 = 0;
	}
	output[31] = R0;
	change_value_32bit_ver(output, 32);
	for (i = 0; i < 16; i++) {
		out[i] = (output[2 * i] << 16) | (output[2 * i + 1]);
	}
}
void MULT256_SQU_32bit_ver_type(word* X, word* out){
	
	sword R0 = 0;
	sword R1 = 0;
	sword R2 = 0;
	sword U, V = 0;
	word value = 0;

	word UV = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int carry = 0;


	sword A[16];
	sword output[32];

	for (i = 0; i < 8; i++) {
		A[2 * i] = X[i] >> 16;
		A[2 * i + 1] = X[i] & 0xffff;
	}

	change_value_32bit_ver(A, 16);

	for (i = 0; i < 32; i++) {
		output[i] = 0;
	}
	
	for (k = 0; k < 16; k++) {
		j = k;
		for (i = 0; i <= j; i++, j--) {

			UV = A[i];
			UV *= A[j];

			if (i != j) {
				value = UV;
				UV = UV << 1;
				if (value > UV) 
					carry = 1;
				else 
					carry = 0;
				R2 = R2 + carry;
			}

			U = UV >> 16;
			V = UV & 0xffff;

			R0 = R0 + V;
			if (R0 < V)	
				carry = 1;
			else carry = 0;

			R1 = R1 + U + carry;
			if (R1 < (U + carry)) 
				carry = 1;
			else 
				carry = 0;

			R2 = R2 + carry;
		}
		output[k] = R0;
		R0 = R1;
		R1 = R2;
		R2 = 0;
	}

	for (k = 16; k < 31; k++) {
		for (i = k - 15, j = 15; i<16 && j>= i; i++, j--) {

			UV = A[i];
			UV *= A[j];

			if (i < j) {
				value = UV;
				UV = UV << 1;
				if (value > UV) 
					carry = 1;
				else 
					carry = 0;
				R2 = R2 + carry;
			}

			U = UV >> 16;
			V = UV & 0xffff;

			R0 = R0 + V;
			if (R0 < V)	
				carry = 1;
			else 
				carry = 0;

			R1 = R1 + U + carry;
			if (R1 < (U + carry)) 
				carry = 1;
			else 
				carry = 0;

			R2 = R2 + carry;
		}
		output[k] = R0;
		R0 = R1;
		R1 = R2;
		R2 = 0;
	}
	output[31] = R0;
	change_value_32bit_ver(output, 32);
	for (i = 0; i < 16; i++) {
		out[i] = (output[2 * i] << 16) | (output[2 * i + 1]);
	}

}