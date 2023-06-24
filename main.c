#include "Deoxys.h"
uint8_t text[16 * 24], ans[16 * 24];
uint8_t tweakey[32 * 24];
int main() {
  // 24 blocks plain text
  for (int i = 0; i < 16 * 24; ++i) {
    scanf("%hhx", &text[i]);
  }
  // 24 blocks tweakey
  // only first 32 bytes are used
  for (int i = 0; i < 32 * 24; ++i) {
    scanf("%hhx", &tweakey[i]);
  }
  preComputeKey(tweakey);
  deoxysBlockEncrypt(text, tweakey[31], ans);
  // Cpiher text
  for (int i = 0; i < 16 * 24; ++i) {
    printf("%02x", ans[i]);
    if (i % 16 == 15)
      printf("\n");
  }
}