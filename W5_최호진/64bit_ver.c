#include "MULT.h"

void change_value(word* A, int size) {

	word value[16];
	int i = 0;
	for (i = 0; i < size; i++)
		value[i] = A[i];

	for (i = 0; i < size; i++)
		A[i] = value[size - i - 1];

}

void MULT256_OS_Long_type(word* A, word* B, word* output) {

	int i = 0;
	int j = 0;
	Long UV = 0;
	word U = 0;
	word V = 0;

	//Initialize output
	for (i = 0; i < 16; i++) {
		output[i] = 0;
	}

	change_value(A, 8);
	change_value(B, 8);

	//Main Part
	for (i = 0; i < 8; i++) {
		U = 0;
		for (j = 0; j < 8; j++) {
			UV = A[i];
			UV *= B[j];
			UV += output[i + j];
			UV += U;

			U = UV >> 32;
			V = (UV & 0xffffffff);
			output[i + j] = V;
		}
		output[i + 8] = U;
	}

	change_value(output, 16);

	change_value(A, 8);
	change_value(B, 8);

}

void MULT256_PS_Long_type(word* A, word* B, word* output) {

	word R0 = 0;
	word R1 = 0;
	word R2 = 0;
	word U, V = 0;

	Long UV = 0;

	int k = 0;
	int i = 0;
	int j = 0;
	int carry = 0;


	change_value(A, 8);
	change_value(B, 8);

	//Case1. K < T;
	for (k = 0; k < 8; k++) {

		j = k;
		for (i = 0; i <= k; i++) {

			UV = A[i];
			UV *= B[j];

			U = (UV >> 32);
			V = (UV & 0xffffffff);

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
			j--;
		}
		output[k] = R0;
		R0 = R1;
		R1 = R2;
		R2 = 0;
	}

	//Case2. K>= T
	for (k = 8; k < 15; k++) {

		for (i = 7, j = k - 7; j < 8; i--, j++) {

			UV = A[i];
			UV *= B[j];

			U = (UV >> 32);
			V = (UV & 0xffffffff);

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
	output[15] = R0;
	change_value(A, 8);
	change_value(B, 8);
	change_value(output, 16);
}

void MULT256_SQU_Long_type(word* A, word* output) {

	word R0 = 0;
	word R1 = 0;
	word R2 = 0;
	word U = 0;
	word V = 0;
	Long value = 0;
	Long UV = 0;

	int i = 0;
	int j = 0;
	int k = 0;
	int carry = 0;

	change_value(A, 8);
	for (i = 0; i < 16; i++)
		output[i] = 0;

	for (k = 0; k < 8; k++) {

		j = k;
		for (i = 0; i <= j; i++) {

			UV = A[i];
			UV *= A[j];

			if (i != j) {
				value = (UV);
				UV = (UV << 1);
				if (value > UV)
					carry = 1;
				else
					carry = 0;
				R2 = R2 + carry;
			}

			V = UV & 0xffffffff;
			U = UV >> 32;

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

			j--;
		}
		output[k] = R0;
		R0 = R1;
		R1 = R2;
		R2 = 0;

	}

	for (k = 8; k < 15; k++) {

		for (i = k - 7, j = 7; i < 8 && j >= i; i++, j--) {

			UV = A[i];
			UV *= A[j];

			if (i != j) {
				value = (UV);
				UV = (value << 1);
				if (value > UV)
					carry = 1;
				else
					carry = 0;

				R2 = R2 + carry;
			}

			V = UV & 0xffffffff;
			U = UV >> 32;

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
	output[15] = R0;
	change_value(A, 8);
	change_value(output, 16);
}