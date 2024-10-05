// p152.c by Daniela Perez. Submitted on September 24, 2024.

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// PASTE YOUR CODE FROM PART 1 HERE

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

void p152(void *in, void *out) {
    // copy 64 bytes from in into an auto-allocated array of 16 uint32_t
    uint32_t arr[16];   // makes array. 64/4 = 16 since uint32_t 
    memcpy(arr, in, 64); // copies 64 bytes form in to arr

    //10 times do:
        //call mix four times, once per column
        //call mix four times, once per diagonal

    for(int i = 0; i < 10; i++){
        mix(&arr[0],& arr[4], &arr[8], &arr[12]);
        mix(&arr[1], &arr[5], &arr[9], &arr[13]);
        mix(&arr[2], &arr[6], &arr[10], &arr[14]);
        mix(&arr[3], &arr[7], &arr[11], &arr[15]);
        
        mix(&arr[0], &arr[5], &arr[10], &arr[15]);
        mix(&arr[1], &arr[6], &arr[11], &arr[12]);
        mix(&arr[2], &arr[7], &arr[8], &arr[13]);
        mix(&arr[3], &arr[4], &arr[9], &arr[14]);
    }
   // copy 64 bytes from your array to out
   memcpy(out, arr, 64);

}

#if 0  // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    unsigned char buf[64] = {1};  // Puts 1 in first byte, rest get auto zeroed
    p152(buf, buf);
    // As a test, output the first 16 bytes of the output
    printf("Is       : ");
    for (int i=0; i<16; i++)
        printf("%02x", buf[i]);
    printf("\n");
    printf("Should be: 14627e9771052d97a8a025cc5531572f\n");
}

#endif