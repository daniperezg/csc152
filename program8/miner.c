// miner.c by Daniela Perez. Submitted for CSC 152 on October 27, 2024
// implements EVP Message Digest (SHA2-256) from: https://wiki.openssl.org/index.php/EVP_Message_Digests

// How to compile: gcc -o miner miner.c -lssl -lcrypto -Wall -Werror -fsanitize=address 
// how to run ./miner <number of leading bits>

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

// prototypes
void pbuf (void * buf, int len);
void digest_message (const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len);
int check_leading_zero_bits (const unsigned char *digest, int n);
void increment_string(char *str);
void mining(int num);


#if 0     // set to 1 while testing and 0 for submission
#include <stdio.h>
int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of leading 0 bits>\n", argv[0]);
        return 1;
    }

    int num_zeros = atoi(argv[1]);

    mining(num_zeros);

    return 0;
    
} 
#endif



void digest_message (const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len) {
    // creates new message digest context structure 
	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        exit(1);  // error checking
    }
    // intializes mdctx to SHA-256
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    // processes the message 
	EVP_DigestUpdate(mdctx, message, message_len);

    // allocates memory for digest 
	*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()));
    if (*digest == NULL) {
        exit(1); // error checking 
    }

    // finalizes digest 
	EVP_DigestFinal_ex(mdctx, *digest, digest_len);

    // frees memory 
	EVP_MD_CTX_free(mdctx);
}

// function to check leading bits are 0 
// assume inputs are multiples of 4, so no need to error check 
int check_leading_zero_bits (const unsigned char *digest, int n) {
    int full_nibbles = n / 4;  // num of nibbles (0000) that must be zero


    for (int i = 0; i < full_nibbles; i++) {
        unsigned char byte = digest[i / 2];  // get hi or low nibble from byte
        unsigned char nibble;

        // if i is even, check hi nibble
        if (i % 2 == 0) {
            nibble = byte >> 4; 
        } 
        // if i is odd, check low nibble 
        else {
            nibble = byte & 0x0F;  
        }

        // if nibble is not zero, return fail
        if (nibble != 0) {  
            return 0;
        }
    }

    return 1;  // if all nibbles are zero, return success
}

// increment an ASCII string (ex: a, ab, ...)
void increment_string(char *str) {
    int len = strlen(str);
    int i = 0;

    while (i < len) {
        if (str[i] == 'z') {
            str[i] = 'A';
        } 
        else if (str[i] == 'Z') {
            str[i] = '0';
        } 
        else if (str[i] == '9') {
            str[i] = 'a';
        } 
        else {
            str[i]++;  // increment the current character
            return;    // exit after a successful increment
        }

        // move to the next character if there's a wrap around
        i++;

        // if we reached the end and need to add a new character
        if (i == len) {
            str[len] = 'a';  // append 'a' at the end if the whole string wraps
            str[len + 1] = '\0';
        }
    }
}

// function for mining 
void mining(int num){
    unsigned char *digest = NULL;
    unsigned int digest_len = 0;
    char test[61] = "a"; // initializing ASCII string (60 + null terminator)

    while (1) {
        // compute SHA-256 hash of the test
        digest_message((unsigned char *)test, strlen(test), &digest, &digest_len);

        // check if the hash has the required leading 0 bits
        if (check_leading_zero_bits(digest, num)) {
            printf("%s\n",test);
            pbuf(digest, digest_len);
            printf("\n");

            OPENSSL_free(digest);
            break;
        }

        // increment the candidate string for the next attempt
        increment_string(test);
        
        // free the digest memory after each iteration
        OPENSSL_free(digest);
    }
}

// helper function provided by Prof Krotvetz to print memory as a sequence of hex 
void pbuf(void *buf, int len){
    unsigned char *p = (unsigned char *)buf;

    for (int i = 0; i < len; i++){
        printf("%02x", p[i]);
    }

    printf("\n");
}