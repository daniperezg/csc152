#include <stdio.h>

// prototyes 
int cmp_bits(int a, int b);
int bitset(int num, int pos);
int bitclear(int num, int pos);
int bittoggle(int num, int pos);
unsigned char reverse_bits(unsigned char num);
int bits_to_flip(int a, int b);

int main (){
    //printf("%d", bitset(22,5));
    //printf("%d", bitset(15,31));
    //printf("%d", bitset(12,0));

    //printf("%d", bitclear(54,5));
    //printf("%d", bitclear(15,31));
    //printf("%d", bitclear(-12,31));
}

int cmp_bits(int a, int b){
    int count_a = 0;
    int count_b = 0;
    
    // assuming 32 bit int 
    // move from left to right 
    for(int i = 32; i>0; i--){
        if(((a >> i) &1) == 1){
            count_a ++;
        }
        if(((b >> i) &1) == 1){
            count_b ++;
        }
    }
    
    if(count_a > count_b){
        return 1;
    }
    else if(count_a == count_b){
        return 0;
    }
    else{
        return -1;
    }
}

int bitset(int num, int pos){
    return num | (1 << pos);
}
int bitclear(int num, int pos){
    return num & (~(1 << pos));
}
int bittoggle(int num, int pos){
    return num ^ (1 << pos);
}

unsigned char reverse_bits(unsigned char num){
    unsigned char answer = 0; 
    unsigned char bit = 0;
    
    // for loop to iterate through char 
    for(int i = 0; i < 8; i++){
        // get lowest bit and put it in answer
        bit = (num >> i) & 1;
        
        answer |= (bit << (7 - i));
    }
    
    return answer;
}

int bits_to_flip(int a, int b){
    // compare each bit in a & b 
    // if they differ count ++;
    
    int count = 0;
    
    for(int i = 32; i > 0; i--){
        if(((a >> i) & 1) != ((b >> i) & 1)){
            count ++;
        }
    }
    return count;
}