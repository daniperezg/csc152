// chat_security.c by Daniela Perez. Submitted for CSC 152 on October 5, 2024.
// implements AES256-CTR encryption & decryption 
// used EVP Symmetric Encryption and Decryption example from 
// https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Write 12+ptlen bytes to ct (ciphertext preceded by 12 byte random nonce)
void chat_encrypt(void *k, void *pt, int ptlen, void *ct){
    unsigned char iv[16];
    int len;
    int ct_bytes_written = 0;

    // write 12 random byte + 4 bytes nonce of 0
    RAND_bytes(iv, 12);
    for (int i = 12; i < 16; i++) {
        iv[i] = 0;
    }

    // copy nonce to beginning of ct 
    memcpy(ct, iv, 12);

    // set up context with alg, key and iv
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, k, iv);

    // provide message to be encrypted
    EVP_EncryptUpdate(ctx, ct + 12, &len, pt, ptlen);

    // keep count of bytes written 
    ct_bytes_written += len;

    // finalize encryption
    EVP_EncryptFinal_ex(ctx, ct + 12 + ct_bytes_written, &len);

    // update counting 
    ct_bytes_written += len;

    // free memory and make it 0
    EVP_CIPHER_CTX_free(ctx);
}

// Write ctlen-12 bytes to pt (using the first 12 bytes of ct as the nonce)
void chat_decrypt(void *k, void *ct, int ctlen, void *pt){
    unsigned char iv[16];
    int len;
    int pt_bytes_written = 0;

    // retrieve nonce from ct 
    unsigned char *nonce = (unsigned char *)ct;
    memcpy(iv, nonce, 12);

    // 4 bytes of zero added to iv 
    for (int i = 12; i < 16; i++) {
        iv[i] = 0;
    }
    
    // initialize decrypt process 
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, k, iv);

    EVP_DecryptUpdate(ctx, pt, &len, ct + 12, ctlen - 12);

    pt_bytes_written += len; 

    EVP_DecryptFinal_ex(ctx, pt + pt_bytes_written, &len);

    pt_bytes_written += len; 

    // free memory and make it 0
    EVP_CIPHER_CTX_free(ctx);

}


#if 0     // Set to 1 while testing and 0 for submission
#include <stdio.h>
int main() {
    unsigned char k[32] = {1,2,3,4};  // First 4 bytes are 1,2,3,4; rest are 0;
    unsigned char pt[81];
    unsigned char ct[93] = {0x45,0x29,0x18,0x7D,0x4D,0x1C,0xF3,0x1D,0x51,0xBF,
                            0x1A,0xB9,0x25,0x57,0xCD,0xE3,0x87,0x07,0xED,0x72,
                            0xA2,0x9E,0xD2,0xA8,0xEA,0x3F,0xA9,0x2E,0xE5,0x08,
                            0x88,0xB8,0xE5,0xC3,0xA4,0xEC,0xE1,0x2F,0xD3,0x6E,
                            0x5E,0x92,0xAA,0x21,0x2A,0x9C,0x7C,0xFC,0x62,0x43,
                            0xA9,0x95,0x4B,0x0C,0x7F,0xB8,0x6C,0x59,0x5D,0x5C,
                            0x56,0x8C,0x08,0x52,0x31,0xD9,0x03,0x32,0x8D,0xA4,
                            0x09,0x86,0x0B,0xBE,0x5A,0xE1,0x28,0x4C,0x57,0xCE,
                            0xE3,0xAA,0x4F,0x7A,0x0E,0x11,0x97,0xAF,0x89,0x6D,
                            0x34,0xD8,0x1B};

    chat_decrypt(k, ct, 93, pt);
    printf("%s", pt);
    
    // output: Shall I compare thee to a summer's day? Thou art more lovely and more temperate.

    /*

    unsigned char pt[44] = "The quick brown fox jumps over the lazy dog";
    unsigned char ct[56];
    unsigned char pt2[44];

    chat_encrypt(k, pt, 44, ct);
    chat_decrypt(k, ct, 56, pt2);

    printf("%s", pt2);
    */

    return 0;
}
#endif