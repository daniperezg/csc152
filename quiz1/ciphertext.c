#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024

// Function to decrypt text using a given shift
void decrypt(char *ciphertext, int shift) {
    int i;
    char decrypted[MAX_TEXT_LENGTH];
    
    for (i = 0; i < strlen(ciphertext); i++) {
        char ch = ciphertext[i];
        
        if (ch >= 'a' && ch <= 'z') {
            decrypted[i] = (ch - 'a' - shift + 26) % 26 + 'a';
        } else {
            decrypted[i] = ch; // Copy non-alphabetic characters as-is
        }
    }
    decrypted[i] = '\0'; // Null-terminate the decrypted string
    
    printf("Shift %2d: %s\n", shift, decrypted);
}

int main() {
    // Predefined ciphertext
    char ciphertext[MAX_TEXT_LENGTH] = "xultpaajcxitltlxaarpjhtiwtgxktghidhipxciwtvgtpilpitghlxiwiwtxgqadds";
    int shift;
    
    // Try all possible shifts
    for (shift = 0; shift < 26; shift++) {
        decrypt(ciphertext, shift);
    }
    
    return 0;
}

// ANSWER: shift 15 - ifweallunitewewillcausetheriverstostainthegreatwaterswiththeirblood
// if we all unite we will cause the rivers to stain the great waters with their blood