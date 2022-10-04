#ifndef DEOXYS_LIBRARY_H
#define DEOXYS_LIBRARY_H

#include <stdint.h>
/**
 * Defines
 */
#define Deoxys_TBC_256 1
// #define Deoxys_TBC_384 1
#define Block_size 128
#if defined(Deoxys_TBC_256)
#define k_plus_t 256
#define rounds 14
#elif defined(Deoxys_TBC_384)
#define k_plus_t 384
#define rounds 16
#endif
void AddRoundTweakey(uint8_t *state, const uint8_t *subtweakey);

void InvAddRoundTweakey(uint8_t *state, const uint8_t *subtweakey);

void MixBytes(uint8_t *state);

void InvMixBytes(uint8_t *state);

void SubBytes(uint8_t *state);

void InvSubBytes(uint8_t *state);

void ShiftRows(uint8_t *state);

void InvShiftRows(uint8_t *state);

void DeoxysEncryption(uint8_t *state, uint8_t *key);

void DeoxysDecryption(uint8_t *state, uint8_t *key);
#endif// DEOXYS_LIBRARY_H
