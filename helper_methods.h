//
// Created by Eliso Morazara on 11/8/23.
//

#ifndef CS203LAB5_HELPER_METHODS_H
#define CS203LAB5_HELPER_METHODS_H

#include "string.h"

unsigned short IV;

/*** useful methods to make coding main methods easier ***/
short bitAt(unsigned short s, unsigned short pos); // bitAt return the bit value of s at pos
// changeBitAt changes the bit value of s at pos then returns the new value
unsigned short changeBitAt(unsigned short s, unsigned short pos);
unsigned short add_uns(unsigned short a, unsigned short b); // return sum of two unsigned short
unsigned short negation(unsigned short val); // return negation of an unsigned short

int regStrToInt(char *reg_str); // register string to int

int valid_dec_val(char *val); // valid decimal string value, return length if valid, 0 otherwise
int valid_hex_val(char *val); // valid hex string value, return length if valid, 0 otherwise
int valid_bin_val(char *val); // valid binary string value, return length if valid, 0 otherwise

int dec_str_val_to_us_IV(char *val); // decimal immediate string value to unsigned short, return 1 if successful, 0 otherwise
int hex_str_val_to_us_IV(char *val); // hex immediate string value to unsigned short, return 1 if successful, 0 otherwise
int bin_str_val_to_us_IV(char *val); // binary immediate string value to unsigned short, return 1 if successful, 0 otherwise
int str_val_to_us_IV(char *val); //  immediate string value to unsigned short in IV, return 1 if successful, 0 otherwise


#endif //CS203LAB5_HELPER_METHODS_H
