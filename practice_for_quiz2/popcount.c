#include <stdio.h> // used for printf 
#include <stdint.h> // used for uint32_t

// input: uint32_t
// output: int of how many 1's in binary

int popcount(uint32_t num){
    int counter = 0; 

    for(int i = 0; i < num; i++){
        // check the right most bit (least significant) 
        if(((num >> i) & 1) == 1){
            counter++; 
        }
    }

    return counter;
}

int main(){
    uint32_t num =  25;
    uint32_t num2 =  15;

    printf("%d\n", popcount(num));
    printf("%d", popcount(num2));

    return 0; 
}