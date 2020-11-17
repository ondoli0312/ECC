#define _CRT_SECURE_NO_WARNINGS
#include "Type.h"
#include "ADD.h"
#include "MULT.h"
void MakeADD() {

	int i = 0;
	int j = 0;
	unsigned long long cycle, cycle1, cycle2;
	cycle = 0;
	FILE* TV_OP_A = NULL;
	FILE* TV_OP_B = NULL;
	FILE* P_256 = NULL;

	FILE* ret_ADD = NULL;
	FILE* ret_SUB = NULL;
	FILE* ret_MUL_OS_32 = NULL;
	FILE* ret_MUL_OS_64 = NULL;
	FILE* ret_MUL_PS_32 = NULL;
	FILE* ret_MUL_PS_64 = NULL;

	FILE* ret_SQR_32 = NULL;
	FILE* ret_SQR_64 = NULL;

	byte buf[2000];
	byte value[32];

	word P256[8];
	word A[8];
	word B[8];
	word output[16];
	
	TV_OP_A = fopen("TV_opA_ADD.txt", "r");
	assert(TV_OP_A != NULL);

	TV_OP_B = fopen("TV_opB_ADD.txt", "r");
	assert(TV_OP_B != NULL);

	P_256 = fopen("P256.txt", "r");
	assert(P_256 != NULL);

	ret_ADD = fopen("ret_PFADD.txt", "w");
	assert(ret_ADD != NULL);

	ret_SUB = fopen("ret_PFSUB.txt", "w");
	assert(ret_ADD != NULL);

	ret_MUL_OS_32 = fopen("ret_MUL_OS_32.txt", "w");
	assert(ret_ADD != NULL);

	ret_MUL_OS_64 = fopen("ret_MUL_OS_64.txt", "w");
	assert(ret_ADD != NULL);

	ret_MUL_PS_32 = fopen("ret_MUL_PS_32.txt", "w");
	assert(ret_ADD != NULL);

	ret_MUL_PS_64 = fopen("ret_MUL_PS_64.txt", "w");
	assert(ret_ADD != NULL);


	ret_SQR_32 = fopen("ret_SQR_32.txt", "w");
	assert(ret_ADD != NULL);

	ret_SQR_64 = fopen("ret_SQR_64.txt", "w");
	assert(ret_ADD != NULL);

	fgets((char*)buf, sizeof(buf), P_256);
	convertStr2Byte(buf, 64, value);

	for (i = 0; i < 8; i++)
		P256[i] = ENDIAN_CHANGE((*(word*)(value + (4 * i))));
	fclose(P_256);

	//ADD
	for (i = 0; i < 10000; i++) {
		
		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_B);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			B[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
		fgets(buf, sizeof(buf), TV_OP_B);
		
		cycle1 = cpucycles();
		addtion_mod_P256(A, B, P256, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);

		for (j = 0; j < 8; j++)
			fprintf(ret_ADD, "%08X", output[j]);
		fprintf(ret_ADD, "\n\n");

	}
	printf("PFADD cpucycle RDTSC = %10lld\n", cycle / 10000);
	cycle = 0;
	fclose(ret_ADD);

	fseek(TV_OP_A, 0, SEEK_SET);
	fseek(TV_OP_B, 0, SEEK_SET);

	//SUB
	for (i = 0; i < 10000; i++) {
		
		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_B);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			B[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
		fgets(buf, sizeof(buf), TV_OP_B);


		cycle1 = cpucycles();
		subtract_mod_P256(A, B, P256, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);
		

		for (j = 0; j < 8; j++)
			fprintf(ret_SUB, "%08X", output[j]);
		fprintf(ret_SUB, "\n\n");

	}
	printf("PFSUB cpucycle RDTSC = %10lld\n", cycle / 10000);
	cycle = 0;
	fclose(ret_SUB);

	fclose(TV_OP_A);
	fclose(TV_OP_B);

	TV_OP_A = fopen("TV_opA_MUL.txt", "r");
	assert(TV_OP_A != NULL);

	TV_OP_B = fopen("TV_opB_MUL.txt", "r");
	assert(TV_OP_B != NULL);

	//MUL_OS_64
	for (i = 0; i < 10000; i++) {

		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_B);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			B[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
		fgets(buf, sizeof(buf), TV_OP_B);

		cycle1 = cpucycles();
		MULT256_OS_Long_type(A, B, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);

		for (j = 0; j < 16; j++)
			fprintf(ret_MUL_OS_64, "%08X", output[j]);
		fprintf(ret_MUL_OS_64, "\n\n");

	}
	printf("MUL_OS_64 cpucycle RDTSC = %10lld\n", cycle / 10000);
	cycle = 0;
	fclose(ret_MUL_OS_64);
	
	fseek(TV_OP_A, 0, SEEK_SET);
	fseek(TV_OP_B, 0, SEEK_SET);

	//MUL_PS_64
	for (i = 0; i < 10000; i++) {
			
		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_B);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			B[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
		fgets(buf, sizeof(buf), TV_OP_B);
		cycle1 = cpucycles();
		MULT256_PS_Long_type(A, B, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);

		for (j = 0; j < 16; j++)
			fprintf(ret_MUL_PS_64, "%08X", output[j]);
		fprintf(ret_MUL_PS_64, "\n\n");

	}
	cycle2 = cpucycles();
	printf("MUL_PS_64 cpucycle RDTSC = %10lld\n", (cycle) / 10000);
	fclose(ret_MUL_PS_64);
	cycle = 0;

	fseek(TV_OP_A, 0, SEEK_SET);
	fseek(TV_OP_B, 0, SEEK_SET);

	//MUL_OS_32
	for (i = 0; i < 10000; i++) {

		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_B);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 16; j++)
			B[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
		fgets(buf, sizeof(buf), TV_OP_B);

		cycle1 = cpucycles();
		MULT256_OS_32bit_type(A, B, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);

		
		for (j = 0; j < 16; j++)
			fprintf(ret_MUL_OS_32, "%08X", output[j]);
		fprintf(ret_MUL_OS_32, "\n\n");

	}
	printf("MUL_OS_32 cpucycle RDTSC = %10lld\n", (cycle) / 10000);
	fclose(ret_MUL_OS_32);
	cycle = 0;

	fseek(TV_OP_A, 0, SEEK_SET);
	fseek(TV_OP_B, 0, SEEK_SET);

	//MUL_PS_32
	for (i = 0; i < 10000; i++) {
		
		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_B);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			B[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
		fgets(buf, sizeof(buf), TV_OP_B);

		cycle1 = cpucycles();
		MULT256_PS_32bit_type(A, B, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);

		for (j = 0; j < 16; j++)
			fprintf(ret_MUL_PS_32, "%08X", output[j]);
		fprintf(ret_MUL_PS_32, "\n\n");

	}
	printf("MUL_PS_32 cpucycle RDTSC = %10lld\n", (cycle) / 10000);
	fclose(ret_MUL_PS_32);
	fclose(TV_OP_B);
	cycle = 0;
	fseek(TV_OP_A, 0, SEEK_SET);

	//SQR_64
	for (i = 0; i < 10000; i++) {
	
		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
		cycle1 = cpucycles();
		MULT256_SQU_Long_type(A, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);

		for (j = 0; j < 16; j++)
			fprintf(ret_SQR_64, "%08X", output[j]);
		fprintf(ret_SQR_64, "\n\n");

	}
	printf("SQR_64 cpucycle RDTSC = %10lld\n", (cycle) / 10000);
	cycle = 0;
	fclose(ret_SQR_64);
	fseek(TV_OP_A, 0, SEEK_SET);

	//SQR_32
	for (i = 0; i < 10000; i++) {
		
		fgets(buf, sizeof(buf), TV_OP_A);
		convertStr2Byte(buf, 64, value);
		for (j = 0; j < 8; j++)
			A[j] = ENDIAN_CHANGE((*(word*)(value + (4 * j))));

		fgets(buf, sizeof(buf), TV_OP_A);
	
		cycle1 = cpucycles();
		MULT256_SQU_32bit_ver_type(A, output);
		cycle2 = cpucycles();
		cycle += (cycle2 - cycle1);

		for (j = 0; j < 16; j++)
			fprintf(ret_SQR_32, "%08X", output[j]);
		fprintf(ret_SQR_32, "\n\n");

	}
	printf("SQR_32 cpucycle RDTSC = %10lld\n", (cycle) / 10000);
	cycle = 0;
	fclose(ret_SQR_32);
	fclose(TV_OP_A);
}

int main() {
	MakeADD();
}
