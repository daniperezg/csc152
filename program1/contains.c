// contains.c by Daniela Perez. Submitted for CSC 152 September 8, 2024
// Terry Weatherman helped me understand the assingment 
// used www.geeksforgeeks.org and www.w3schools.org for help in C


#include <stdio.h>
#include <string.h> // for char 
 

int is_equal(unsigned char *a, unsigned char *b, int len) {
    // inner loop 
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return 0;  // if elements don't equal, return 0
        }
    }
    return 1;  // else, return 1
}

// a points to an alen byte buffer, b points to a blen byte buffer,
// returns non-zero iff b's buffer is found contiguously inside a's.
int contains(void *a, int alen, void *b, int blen) {
    // typecasting void pointers to unsigned char 
    unsigned char *arr1 = (unsigned char *)a;
    unsigned char *arr2 = (unsigned char *)b;

    // if b is larger than a, can't be subarray of a
    // elif b = 0, then b is empty, therefore contained in a
    if (blen > alen) {
        return 0;
    }
    else if(blen == 0){
        return 1;
    } 

    // outer loop through array a
    for (int i = 0; i <= alen - blen; i++) {
        if (is_equal(&arr1[i], arr2, blen)) {
            return 1;  
        }
    }

    // if no match found, return 0
    return 0;
}

/*
int main()
{
    int isContained;
    int x[100]; // An array to demonstrate usage
    char *ptrx = (char *)x;

    // Test case 1
    isContained = contains(ptrx, 100, &ptrx[5], 10);
    printf("Test Case 1: %d (Expected: 1)\n", isContained);

    // Test case 2
    isContained = contains(ptrx, 50, &ptrx[20], 30);
    printf("Test Case 2: %d (Expected: 1)\n", isContained);

    // Test case 3
    isContained = contains(ptrx, 0, &ptrx[5], 5);
    printf("Test Case 3: %d (Expected: 0)\n", isContained);

    // Test case 4
    isContained = contains(ptrx, 100, &ptrx[99], 1);
    printf("Test Case 4: %d (Expected: 1)\n", isContained);

    // Test case 5
    isContained = contains(ptrx, 100, ptrx, 0);
    printf("Test Case 5: %d (Expected: 1)\n", isContained);

    // Test case 6
    isContained = contains(ptrx, 100, ptrx + 10, 20);
    printf("Test Case 6: %d (Expected: 1)\n", isContained);

    // Test case 7
    isContained = contains(ptrx, 50, ptrx + 25, 25);
    printf("Test Case 7: %d (Expected: 1)\n", isContained);

    // Test case 8
    isContained = contains(ptrx, 100, ptrx + 5, 95);
    printf("Test Case 8: %d (Expected: 1)\n", isContained);

    // Test case 9
    isContained = contains(ptrx, 100, ptrx + 50, 50);
    printf("Test Case 9: %d (Expected: 1)\n", isContained);

    // Test case 10
    isContained = contains(ptrx, 100, ptrx + 30, 20);
    printf("Test Case 10: %d (Expected: 1)\n", isContained);

    // Edge Test case 1: Both buffers are the same with length 0
    isContained = contains(ptrx, 0, ptrx, 0);
    printf("Edge Test Case 1: %d (Expected: 1)\n", isContained);

    // Edge Test case 2: Sub-buffer starts exactly where main buffer ends
    isContained = contains(ptrx, 100, ptrx + 100, 1);
    printf("Edge Test Case 2: %d (Expected: 0)\n", isContained);

    // Edge Test case 3: Sub-buffer is outside the range of the main buffer
    isContained = contains(ptrx, 50, ptrx + 60, 10);
    printf("Edge Test Case 3: %d (Expected: 0)\n", isContained);
}
*/