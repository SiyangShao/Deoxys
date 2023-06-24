#include "Deoxys.h"
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
const static uint8_t RCON[17] = {0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97,
                                 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
                                 0xef, 0xc5, 0x91, 0x39, 0x72};

// RC
static uint8_t RC_tmp[16] = {0x1, 0x2, 0x4, 0x8, 0x0, 0x0, 0x0, 0x0,
                             0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
i128 RC(int i) {
  RC_tmp[4] = RC_tmp[5] = RC_tmp[6] = RC_tmp[7] = RCON[i];
  return _mm_load_si128((i128 *)RC_tmp);
}
static i128 RCvalues[17];
static i128 nxtState[6];
static i128 subTweakey[6];
static i128 counterOffset[17][256];
inline static i128 _getOffset(uint8_t cnt, int round) {
  i128 cur = _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, cnt);
  // return _liftFunction[round](&cur);
  switch (round) {
  case 0:
    return cur;
  case 1:
    return _mm_srli_si128(cur, 9);
  case 2:
    return _mm_srli_si128(cur, 14);
  case 3:
    return _mm_srli_si128(cur, 15);
  case 4:
    return _mm_srli_si128(cur, 8);
  case 5:
    return _mm_srli_si128(cur, 1);
  case 6:
    return _mm_srli_si128(cur, 6);
  case 7:
    return _mm_srli_si128(cur, 7);
  case 8:
    return cur;
  case 9:
    return _mm_srli_si128(cur, 9);
  case 10:
    return _mm_srli_si128(cur, 14);
  case 11:
    return _mm_srli_si128(cur, 15);
  case 12:
    return _mm_srli_si128(cur, 8);
  case 13:
    return _mm_srli_si128(cur, 1);
  case 14:
    return _mm_srli_si128(cur, 6);
  case 15:
    return _mm_srli_si128(cur, 7);
  case 16:
    return cur;
  case 17:
    return _mm_srli_si128(cur, 9);
  default:
    return cur;
  }
}
__attribute__((constructor)) void initialize() {
  // Initialize RC value when start the program
  for (int i = 0; i < 17; ++i) {
    RCvalues[i] = RC(i);
  }
  for (int i = 0; i < 6; ++i) {
    nxtState[i] =
        _mm_setr_epi8(1, 6, 11, 12, 5, 10, 15, 0, 9, 14, 3, 4, 13, 2, 7, 8);
  }
  for (int i = 0; i < 17; ++i) {
    for (int j = 0; j < 256; ++j) {
      counterOffset[i][j] = _getOffset((uint8_t)j, i);
    }
  }
}

static i128 UpdatedKey[17], UpdatedAll[17];

void deoxysi128BLOCKEncrypt(i128 *state, uint8_t counter_begin) {

  subTweakey[0] = _mm_xor_si128(UpdatedAll[0], counterOffset[0][counter_begin]);
  state[0] = _mm_xor_si128(state[0], subTweakey[0]);
  subTweakey[1] =
      _mm_xor_si128(UpdatedAll[0], counterOffset[0][counter_begin + 1]);
  state[1] = _mm_xor_si128(state[1], subTweakey[1]);
  subTweakey[2] =
      _mm_xor_si128(UpdatedAll[0], counterOffset[0][counter_begin + 2]);
  state[2] = _mm_xor_si128(state[2], subTweakey[2]);
  subTweakey[3] =
      _mm_xor_si128(UpdatedAll[0], counterOffset[0][counter_begin + 3]);
  state[3] = _mm_xor_si128(state[3], subTweakey[3]);
  subTweakey[4] =
      _mm_xor_si128(UpdatedAll[0], counterOffset[0][counter_begin + 4]);
  state[4] = _mm_xor_si128(state[4], subTweakey[4]);
  subTweakey[5] =
      _mm_xor_si128(UpdatedAll[0], counterOffset[0][counter_begin + 5]);
  state[5] = _mm_xor_si128(state[5], subTweakey[5]);
  for (int i = 1; i <= 14; ++i) {
    subTweakey[0] =
        _mm_xor_si128(UpdatedAll[i], counterOffset[i][counter_begin]);
    state[0] = _mm_aesenc_si128(state[0], subTweakey[0]);
    subTweakey[1] =
        _mm_xor_si128(UpdatedAll[i], counterOffset[i][counter_begin + 1]);
    state[1] = _mm_aesenc_si128(state[1], subTweakey[1]);
    subTweakey[2] =
        _mm_xor_si128(UpdatedAll[i], counterOffset[i][counter_begin + 2]);
    state[2] = _mm_aesenc_si128(state[2], subTweakey[2]);
    subTweakey[3] =
        _mm_xor_si128(UpdatedAll[i], counterOffset[i][counter_begin + 3]);
    state[3] = _mm_aesenc_si128(state[3], subTweakey[3]);
    subTweakey[4] =
        _mm_xor_si128(UpdatedAll[i], counterOffset[i][counter_begin + 4]);
    state[4] = _mm_aesenc_si128(state[4], subTweakey[4]);
    subTweakey[5] =
        _mm_xor_si128(UpdatedAll[i], counterOffset[i][counter_begin + 5]);
    state[5] = _mm_aesenc_si128(state[5], subTweakey[5]);
  }
}

static i128 i128text[24], i128firstKey, i128firstCounter;
void preComputeKey(uint8_t *key) {
  i128firstKey = _mm_loadu_si128((i128 *)key);
  i128firstCounter = _mm_setr_epi8(
      key[16], key[17], key[18], key[19], key[20], key[21], key[22], key[23],
      key[24], key[25], key[26], key[27], key[28], key[29], key[30], 0);
  UpdatedKey[0] = i128firstKey ^ RCvalues[0];
  UpdatedAll[0] = UpdatedKey[0] ^ i128firstCounter;
  for (int i = 0; i < 14; ++i) {
    i128firstKey = _mm_xor_si128(
        _mm_and_si128(_mm_xor_si128(_mm_srli_epi16(i128firstKey, 7),
                                    _mm_srli_epi16(i128firstKey, 5)),
                      _mm_set1_epi8(1)),
        _mm_and_si128(_mm_slli_epi16(i128firstKey, 1), _mm_set1_epi8(0xFE)));
    i128firstKey = _mm_shuffle_epi8(i128firstKey, nxtState[0]);
    i128firstCounter = _mm_shuffle_epi8(i128firstCounter, nxtState[1]);
    UpdatedKey[i + 1] = _mm_xor_si128(i128firstKey, RCvalues[i + 1]);
    UpdatedAll[i + 1] = _mm_xor_si128(UpdatedKey[i + 1], i128firstCounter);
  }
}
void deoxysBlockEncrypt(uint8_t plainText[16 * 24], uint8_t key,
                   uint8_t ans[16 * 24]) {

  for (int i = 0; i < 24; i += 6) {
    i128text[i + 0] = _mm_loadu_si128((i128 *)(plainText + i * 16 + 16 * 0));
    i128text[i + 1] = _mm_loadu_si128((i128 *)(plainText + i * 16 + 16 * 1));
    i128text[i + 2] = _mm_loadu_si128((i128 *)(plainText + i * 16 + 16 * 2));
    i128text[i + 3] = _mm_loadu_si128((i128 *)(plainText + i * 16 + 16 * 3));
    i128text[i + 4] = _mm_loadu_si128((i128 *)(plainText + i * 16 + 16 * 4));
    i128text[i + 5] = _mm_loadu_si128((i128 *)(plainText + i * 16 + 16 * 5));
  }
  deoxysi128BLOCKEncrypt(i128text + 0, key + 0);
  deoxysi128BLOCKEncrypt(i128text + 6, key + 6);
  deoxysi128BLOCKEncrypt(i128text + 12, key + 12);
  deoxysi128BLOCKEncrypt(i128text + 18, key + 18);

  for (int i = 0; i < 24; i += 2) {
    _mm_storeu_si128((i128 *)(ans + i * 16), i128text[i]);
    _mm_storeu_si128((i128 *)(ans + i * 16 + 16), i128text[i + 1]);
  }
}