#include "library.h"
#include <stdio.h>
#include <string.h>
int bit(char c) {
    if (c <= '9' && c >= '0') {
        return c - '0';
    } else {
        return c - 'a' + 10;
    }
}
void change(uint8_t *s, const char *c, int sz) {
    for (int i = 0; i < sz; i += 2) {
        s[i / 2] = bit(c[i]) * 16 + bit(c[i + 1]);
    }
}
char outbit(uint8_t c) {
    if (c >= 10) {
        return c - (uint8_t) (10) + 'a';
    } else {
        return c + '0';
    }
}
void output(const uint8_t *s, int sz) {
    for (int i = 0; i < sz; ++i) {
        printf("%c%c", outbit(s[i] / 16), outbit(s[i] % 16));
    }
}
int main() {
    char c_state[16 * 2] = "0429974cda6665fb9bb4b67d50859258";
    //    for (int i = 0; i < 16; ++i) {
    //        char mid = c_state[i];
    //        c_state[i] = c_state[31-i];
    //        c_state[31-i] = mid;
    //    }
    char c_key[32 * 2] = "101112131415161718191a1b1c1d1e1f20000000000000000000000000000000";
    //    for (int i = 0; i < 32; ++i) {
    //        char mid = c_key[i];
    //        c_key[i] = c_key[63-i];
    //        c_key[31-i] = mid;
    //    }
    uint8_t state[16], key[32];
    change(state, c_state, 16 * 2);
    change(key, c_key, 32 * 2);
    for (int i = 0; i < 16; ++i) {
        printf("%d ", state[i]);
    }
    printf("\n");
    for (int i = 0; i < 32; ++i) {
        printf("%d ", key[i]);
    }
    printf("\n");
    DeoxysEncryption(state, key);
    for (int i = 0; i < 16; ++i) {
        printf("%d ", state[i]);
    }
    output(state, 16);
}
