#ifndef DEOXYS_LIBRARY_H
#define DEOXYS_LIBRARY_H

#include <stdint.h>
/**
 * Defines
 */
#define Deoxys_I_128
// #define Deoxys_I_256
// #define Deoxys_AE1
// #define Deoxys_II_128
// #define Deoxys_II_256
// #define Deoxys_AE2
#if defined(Deoxys_I_128) || defined(Deoxys_II_128)
#define Deoxys_TBC_256
#endif
#if defined(Deoxys_I_256) || defined(Deoxys_AE1) || defined(Deoxys_II_256) || defined(Deoxys_AE2)
#define Deoxys_TBC_384 1
#endif
#define Block_size 128
#if defined(Deoxys_TBC_256)
#define k_plus_t 256
#define rounds 14
#elif defined(Deoxys_TBC_384)
#define k_plus_t 384
#define rounds 16
#endif

#define key_size 128
// #define key_size 256

#define tag_size 128

void AddRoundTweakey(uint8_t *state, const uint8_t *subtweakey);

void InvAddRoundTweakey(uint8_t *state, const uint8_t *subtweakey);

void MixBytes(uint8_t *state);

void InvMixBytes(uint8_t *state);

void SubBytes(uint8_t *state);

void InvSubBytes(uint8_t *state);

void ShiftRows(uint8_t *state);

void InvShiftRows(uint8_t *state);

void RoundFunction(uint8_t *state, uint8_t *key);

void Byte_Permutation_h(uint8_t *key);

void XOR(uint8_t *subtweakey, const uint8_t *TK1, const uint8_t *TK2);

void STK(uint8_t *key, int round);

void LFSR2(uint8_t *key);

void LFSR3(uint8_t *key);

void DeoxysEncryption(uint8_t *state, const uint8_t *key);

void DeoxysDecryption(uint8_t *state, uint8_t *key);
#endif// DEOXYS_LIBRARY_H
