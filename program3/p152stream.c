// p152stream.c by Daniela Perez. Submitted on September 24, 2024.

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// PASTE YOUR CODE FROM PARTS 1 AND 2 HERE

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

// Increment buf as if it's a 64 byte big-endian integer
static void increment_block(void *buf) {
    unsigned char *blk = buf;
    int i = 63;
    blk[i] += 1;
    while (blk[i] == 0) {
        i -= 1;
        blk[i] += 1;
    }
} 

// k is 32 bytes, n is 16 bytes, 0* is 16 bytes
// Use blk = k || n || 0* to produce output as blk xor p152(blk), then increment blk
// This output is xor'd with the next 64 bytes of buf to encrypt/decrypt
void p152stream(void *k, void *n, void *inbuf, void *outbuf, int nbytes) {
    unsigned char *pinbuf = inbuf;
    unsigned char *poutbuf = outbuf;
    unsigned char in[64];
    unsigned char out[64];
    int pointer = 0;

    // Init in as k || n || 0*
    memcpy(in, k, 32);
    memcpy(in+32, n, 16);
    memset(in+48, 0, 16);

    while(nbytes >= 64){
        p152(in, out); // call p152

        // out = out ^ in 
        for(int i = 0; i < 64; i++){
            out[i] ^= in[i];
        }

        // out = out ^ inbuf and add that to tail of outbuf
        for(int j = 0; j < 64; j++){
            poutbuf[pointer] = out[j] ^  pinbuf[pointer];
            pointer++;
        }

        // increment last 
        increment_block(in);
        // decrement nbytes by 64 it goes to next block 
        nbytes -= 64;
    }

    if(nbytes > 0){
        p152(in, out); // call p152

        // out ^ in 
        for (int k = 0; k < nbytes; k++) {
            out[k] ^= in[k];
        }

        // out[remainder bytes] ^ inbuf[remainder bytes] and add to tail of outbuf
        for(int l = 0; l < nbytes; l++){
            poutbuf[pointer]= out[l] ^ pinbuf[pointer];
            pointer++;
        }

    }

}

#if 0  // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    unsigned char inbuf[200] = {1};
    unsigned char outbuf[200];
    unsigned char k[32] = {1,2,3,4};
    unsigned char n[16] = {1,2,3,4};
    p152stream(k, n, inbuf, outbuf, 200);
    printf("Is       : ");
    for (int i=0; i<200; i++)
        printf("%02x", outbuf[i]);
    printf("\n");
    printf("Should be: d6c0e5ef8745f9fc4657510ce896e96b9f27c18ba5a8cadc7e2a"
           "6872c51c704983726c6633a9e924a5e9a75b8b9980cfad91501f74315fea6da"
           "0936286e5866ac66e8c3d766b6248f88ee99b468dd9fdcf2c4e65e6df35637b"
           "b245246e0cb97ce689c0b91dbd7212257f98744fae42484ea3afbd419db90ca"
           "38a96d4c6e68cd6c003af8b842733ad4162099b2b2d10bfd48a3fb6e8c5e5ea"
           "59dde8bae3206ce3e80f0acad1540e83e2858f39bccec0a4ece5172194f6d15"
           "e7fd5a26a05cb3b8b8fea979965daf5c1\n");
}

#endif