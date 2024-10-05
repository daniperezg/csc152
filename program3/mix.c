// mix.c by Daniela Perez. Submitted on September 24, 2024.

#include <stdint.h>

// Static means that it is not exported for linking and so
// can only be called from this file.
static uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32-n));
}

// ap - dp are references to four variables to be mixed.
// A good compiler will keep everything in registers, so even
// though it looks like we're reading memory, we probably aren't.
void mix(uint32_t *ap, uint32_t *bp, uint32_t *cp, uint32_t *dp) {
    // Receive the four words to be mixed
    uint32_t a = *ap;
    uint32_t b = *bp;
    uint32_t c = *cp;
    uint32_t d = *dp;
    // Mix the four words

    // YOUR CODE HERE

    // 1: add a and b 
    a = a + b;

    // 2: xor a and d 
    d = a ^ d;

    // 3: d left shift 16 bits 
    d = rotl32(d, 16);

    // 4: add c and d 
    c = c + d; 

    // 5: xor c and b 
    b = b ^ c;

    // 6: b left shift 12 bits 
    b = rotl32(b, 12);

    // 7: add b and a 
    a = a + b;

    // 8: xor a and d 
    d = a ^ d;

    // 9: d left shift 8 bits
    d = rotl32(d, 8); 

    // 10: add d and c 
    c = d + c; 

    // 11: xor c and b
    b = c ^ b;

    // 12: b left shift 7 bits 
    b = rotl32(b , 7);

    // Update the caller's values
    *ap = a;
    *bp = b;
    *cp = c;
    *dp = d;   
}

#if 0  // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    uint32_t a = 0x00010203;
    uint32_t b = 0x04050607;
    uint32_t c = 0x08090A0B;
    uint32_t d = 0x0C0D0E0F;
    mix(&a, &b, &c, &d);
    printf("Is       : %x %x %x %x\n", a, b, c, d);
    printf("Should be: b54718aa afd1b4f0 501eb3c9 4210a1b3\n");
}

#endif