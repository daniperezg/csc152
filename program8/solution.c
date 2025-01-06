// professor krovetz solution

#include <stdlib.h>
#include <stdio.h>
#include <openssl/evp.h>

static void pbuf(void *buf, int len)
{
    unsigned char *p = (unsigned char *)buf;
    for (int i = 0; i < len; i++)
        printf("%02x", p[i]);
    printf("\n");
}

static void incbuf(unsigned char *buf) {
    int idx = 0;
    buf[idx] += 1;
    while (buf[idx] > 'z') {
        buf[idx] = 'a';
        idx += 1;
        buf[idx] += 1;
    }
}

static int test(unsigned char *buf, int bits) {
    int idx = 0;
    while (bits >= 8) {
        if (buf[idx] != 0)
            return 0;
        idx += 1;
        bits -= 8;
    }
    if (bits == 4)
        return ((buf[idx] & 0xf0) == 0);
    else
        return bits == 0;
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        int bits = (int)strtol(argv[1], NULL, 10);
        if ((bits > 0) && (bits%4 == 0)) {
            EVP_MD_CTX *mdctx;
            unsigned char digest[32];
            unsigned char buf[] = "abcdefghijklmnopqrstuvwxyz";
            
            mdctx = EVP_MD_CTX_new();
            do {
                incbuf(buf);
                EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
                EVP_DigestUpdate(mdctx, buf, 26);
                EVP_DigestFinal_ex(mdctx, digest, NULL);
            } while ( ! test(digest, bits));
            EVP_MD_CTX_free(mdctx);
            printf("%s\n", buf);
            pbuf(digest, 32);
        }
    }
    return EXIT_SUCCESS;
}