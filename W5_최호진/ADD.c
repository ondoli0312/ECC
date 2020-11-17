#include "ADD.h"

/*
	output = (e, A+B);
*/
int addtion256(word* A, word* B, word* output) {

	int x = 0;
	int i = 0;

	//(e, C[0])
	output[7] = A[7] + B[7];

	if (output[7] < A[7])
		x = 1;
	else
		x = 0;

	for (i = 6; i >= 0; i--) {

		output[i] = A[i] + B[i] + x;

		if ((output[i] - x) < A[i])
			x = 1;
		else
			x = 0;

	}
	return x;
}

/*
	output = (e, A-B);
*/
int subtract256(word* A, word* B, word* output) {

	int x = 0;
	int i = 0;

	//output[0];
	if (A[7] < B[7]) {
		output[7] = (0xffffffff - B[7] + 1) + A[7];
		x = 1;
	}

	else {
		output[7] = A[7] - B[7];
		x = 0;
	}

	for (i = 6; i >= 0; i--) {

		if (A[i] < B[i]) {
			output[i] = ((0xffffffff - B[i]) + 1) + A[i] - x;
			x = 1;
		}
		else if (A[i] == B[i] && x == 1) {
			output[i] = 0xffffffff;
			x = 1;
		}
		else {
			output[i] = A[i] - B[i] - x;
			x = 0;
		}
	}

	return x;
}

/*
	output ->
	1  => A[i] > B[i]
	-1 => A[i] < B[i]
	0  => A[i] = B[i]
*/
int compare256(word* A, word* B) {

	int i = 0;
	int cnt = 0;
	for (i = 0; i < 8; i++) {
		if (A[i] > B[i])
			return 1;
		else if (A[i] < B[i])
			return -1;
	}
	return 0;
}

void addtion_mod_P256(word* A, word* B, word* P, word* output) {

	int a = 0;
	int b = 0;
	int cnt = 0;
	word value[8];
	a = addtion256(A, B, value);
	b = compare256(value, P);

	if (a == 1 || b != -1)
		subtract256(value, P, output);
	else
		for (cnt = 0; cnt < 8; cnt++)
			output[cnt] = value[cnt];
}

void subtract_mod_P256(word* A, word* B, word* P, word* output) {
	word value[8];
	int a = 0;
	int cnt = 0;

	a = subtract256(A, B, value);
	if (a == 1)
		addtion256(value, P, output);

	else
		for (cnt = 0; cnt < 8; cnt++)
			output[cnt] = value[cnt];
}