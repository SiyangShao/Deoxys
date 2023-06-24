#ifndef DEOXYS_H
#define DEOXYS_H
#include <emmintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <wmmintrin.h>
#include <x86intrin.h>
typedef __m128i i128;
void deoxysi128BLOCKEncrypt(i128 *state, uint8_t counter_begin);
void preComputeKey(uint8_t *key);
void deoxysBlockEncrypt(uint8_t plainText[16 * 24], uint8_t key,
                        uint8_t ans[16 * 24]);

#endif