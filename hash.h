#ifndef HASH_H
#define HASH_H

typedef unsigned long long uint64;

typedef unsigned char BitSequence;
typedef unsigned long long DataLength;
typedef enum {SUCCESS = 0, FAIL = 1, BAD_HASHLEN = 2} HashReturn;

/*define data alignment for different C compilers*/
#if defined(__GNUC__)
      #define DATA_ALIGN16(x) x __attribute__ ((aligned(16)))
#else
      #define DATA_ALIGN16(x) __declspec(align(16)) x
#endif


typedef struct {
	int hashbitlen;	   	              /*the message digest size*/
	unsigned long long databitlen;    /*the message size in bits*/
	unsigned long long datasize_in_buffer;      /*the size of the message remained in buffer; assumed to be multiple of 8bits except for the last partial block at the end of the message*/
	DATA_ALIGN16(uint64 x[8][2]);     /*the 1024-bit state, ( x[i][0] || x[i][1] ) is the ith row of the state in the pseudocode*/
	unsigned char buffer[64];         /*the 512-bit message block to be hashed;*/
} hashState;

HashReturn	Init(hashState *state, int hashbitlen);
HashReturn	Update(hashState *state, const BitSequence *data, DataLength databitlen);
HashReturn	Final(hashState *state, BitSequence *hashval);
HashReturn	Hash(int hashbitlen, const BitSequence *data, DataLength databitlen, BitSequence *hashval);

#endif

