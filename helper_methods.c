//
// Created by Eliso Morazara on 11/8/23.
//

#include "helper_methods.h"

/*** useful methods to make coding main methods easier ***/
short bitAt(unsigned short s, unsigned short pos){
    if(pos > 15) return 0; // we are only interested in 16 bits numbers max
    unsigned short a = 1 << pos;
    if((s & a) == a) return 1;
    return 0;
}

unsigned short changeBitAt(unsigned short s, unsigned short pos){
    if(pos > 15) return 0; // we are only interested in 16 bits numbers max
    unsigned short a = 1 << pos;
    return s ^ a;
}

unsigned short add_uns(unsigned short a, unsigned short b){
    unsigned short res = 0; // result
    unsigned short c = 0; // carry, Ci = Ai & Bi | (Ai ^ Bi) & Ci-1, say C-1 = 0;

    c = bitAt(a, 0) & bitAt(b, 0); // taking care of carry at pos 0
    res = bitAt(a, 0) ^ bitAt(b, 0); // calculate bit at pos 0 of res
    // now for pos 1 to 15
    for (int i = 1; i < 16; i++){
        // Ci = Ai & Bi | (Ai ^ Bi) & Ci-1
        if(bitAt(a, i) & bitAt(b, i) | (bitAt(a, i) ^ bitAt(b, i)) & bitAt(c,i-1)) {
            c = changeBitAt(c, i);
        }
        // RESi = Ci-1 ^ Ai ^ Bi
        if (bitAt(c, i-1) ^ bitAt(a, i) ^ bitAt(b, i)) res = changeBitAt(res, i);
    }
    return res;
}

unsigned short negation(unsigned short val){
    return (~val) + 1;
}

/* index of register is as follows:
      0 for R0
      1 for R1
      2 for R2
      3 for R3
      4 for AC
      5 for SP
      6 for BP
      7 for PC or ProC
*/
int regStrToInt(char *reg_str){
    if(strcmp(reg_str, "R0") == 0) return 0;
    if(strcmp(reg_str, "R1") == 0) return 1;
    if(strcmp(reg_str, "R2") == 0) return 2;
    if(strcmp(reg_str, "R3") == 0) return 3;
    if(strcmp(reg_str, "AC") == 0) return 4;
    if(strcmp(reg_str, "SP") == 0) return 5;
    if(strcmp(reg_str, "BP") == 0) return 6;
    if(strcmp(reg_str, "PC") == 0) return 7;

    return -1; // invalid register
}

int valid_dec_val(char *val){
    int len = 0;
    // count number of characters in val
    while(val[len]){ len++; }
    if(len == 0) return 0;

    int i = (val[0] == '-') ? 1 : 0; // i depends on if val is negative or positive
    if((i == 1) && (len < 2)) return 0; // if "-", invalid

    for(; i < len; i++){
        if((val[i] < '0') || (val[i] > '9')) return 0; // if it has character other that [0,9], invalid
    }

    return len;
}

int valid_hex_val(char *val){
    int len = 0;
    // count number of characters in val
    while(val[len]){ len++; }
    if(len < 3) return 0; // need at very least 3 char "0x_"

    int i = (val[0] == '-') ? 1 : 0; // i depends on if val is negative or positive
    if((i == 1) && (len < 4)) return 0; // if negative now we need at least 4 char
    if((val[i] != '0') || ((val[i+1] != 'x') && (val[i+1] != 'X'))) return 0; // check for "0x" or "0X"
    i += 2; // update i before loop

    for(; i < len; i++){
        if(((val[i] < '0') || (val[i] > '9'))
           && ((val[i] < 'A') || (val[i] > 'F'))
           && ((val[i] < 'a') || (val[i] > 'f'))) return 0; // if it has character other that [0,9], invalid
    }

    return len;
}

int valid_bin_val(char *val){
    int len = 0;
    // count number of characters in val
    while(val[len]){ len++; }
    if((len < 3)) return 0; // len must be >= 3

    int i = (val[0] == '-') ? 1 : 0; // i depends on if val is negative or positive
    if((i == 1) && (len < 4)) return 0; // if positive len >= 4

    if((val[i] != '0') || ((val[i+1] != 'b') && (val[i+1] != 'B'))) return 0; // check for "0x" or "0X"
    i += 2; // update i before loop

    for(; i < len; i++){
        if((val[i] < '0') || (val[i] > '1')) return 0; // if it has character other that [0,9], invalid
    }

    return len;
}

int dec_str_val_to_us_IV(char *val){

    int len = valid_dec_val(val); // get len if valid, if val not valid, len == 0
    if(len == 0) return 0; // if not valid dec, do nothing, return 0

    int negative = (val[0] == '-') ? 1 : 0; // check if negative

    int i = (val[0] == '-') ? 1 : 0; // the start of the digits

    // get rid of all 0 at the beginning of the dec string
    while(val[i] == '0'){i++;}

    IV = 0; // to store the real unsigned short value of the decimal, remember IV is "global"
    for(int u = len - 1; u >= i; u--){
        int v = (val[u] - '0');
        if(v > 0){
            for(int w = 0; w < (len-1-u); w++) v *= 10;
        }
        unsigned short preIV = IV;
        IV += v; // update PIV
        if((IV - preIV) != v) return 0; // overflow
    }

    if(negative) IV = negation(IV); // if negative store 2's comp

    return 1;
}

int hex_str_val_to_us_IV(char *val){

    int len = valid_hex_val(val); // get len if valid, if val not valid, len == 0
    if(len == 0) return 0; // if not valid hex, do nothing, return 0

    int negative = (val[0] == '-') ? 1 : 0; // check if negative

    int i = (val[0] == '-') ? 3 : 2; // the start of the digits

    // get rid of all 0 at the beginning of the hex string
    while(val[i] == '0'){i++;}

    IV = 0; // to store the real unsigned short value of the hex, reminder that PIV is a global var
    for(int u = len - 1; u >= i; u--){
        int v = 0;
        if ((val[u] >= '0') && (val[u] <= '9')) v = (val[u] - '0');
        if ((val[u] >= 'a') && (val[u] <= 'f')) v = (val[u] - 'a' + 10);
        if ((val[u] >= 'A') && (val[u] <= 'F')) v = (val[u] - 'A' + 10);

        if(v > 0){
            for(int w = 0; w < (len-1-u); w++) v *= 16;
        }
        unsigned short preIV = IV;
        IV += v; // update PIV
        if((IV - preIV) != v) return 0; // overflow
    }

    if(negative) IV = negation(IV); // if negative store 2's comp

    return 1;
}

int bin_str_val_to_us_IV(char *val){

    int len = valid_bin_val(val); // get len if valid, if val not valid, len == 0
    if(len == 0) return 0; // if not valid binary, do nothing, return 0

    int negative = (val[0] == '-') ? 1 : 0; // check if negative

    int i = (val[0] == '-') ? 3 : 2; // the start of the digits

    // get rid of all 0 at the beginning of the hex string
    while(val[i] == '0'){i++;}

    IV = 0; // to store the real int value of the binary, reminder that PIV is a global var
    for(int u = len - 1; u >= i; u--){
        int v = (val[u] == '1') ? (1 << (len - 1 - u)) : 0;

        unsigned short preIV = IV;
        IV += v; // update PIV
        if((IV - preIV) != v) return 0; // overflow
    }

    if(negative) IV = negation(IV); // if negative store 2's comp

    return 1;
}

int str_val_to_us_IV(char *val){
    // when one is true, the or statement stops so this is an easy way to implement it
    return (dec_str_val_to_us_IV(val) || hex_str_val_to_us_IV(val) || bin_str_val_to_us_IV(val));
}


