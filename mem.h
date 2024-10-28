//
// Created by Eliso Morazara on 11/5/23.
//

#ifndef CS203LAB5_MEM_H
#define CS203LAB5_MEM_H

#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ctype.h"

#include "cpu.h"
#include "helper_methods.h"

// define the size of a pointer
#define ADDRESS_SIZE 65536

enum OP {
    data,               // indicates location stores data
    dumpmemory,         // dump the contents of memory to stdout
    dumpCPU,            // dump the contents of the CPU to stdout
    halt,               // halts program
    jmp, jmpz, jmpn,    // jump instructions
    call, ret,          // function call/ret instructions
    mova, movr,         // register move instructions
    lodi, loda, lorr,   // memory load instructions     reg    --> memory
    stoa, stor, stoi,   // memory store instructions    memory --> reg
    add, sub, neg,      // arithmetic instructions
};

// as each line is read from the file, it will be:
//  1. stored into the instruction_string
//  2. cleaned up, as done in lab 4
//  3. broken into substrings stored in the associated char * variables
//  4. converted into functional values stored in the appropriate structure variables

struct location_contents {
    /*** information dot-instructions ***/
    /*** add your variables here ***/

    /*** information storage for data ***/
    unsigned short data;

    /*** information storage for an instruction ***/
    enum OP operation;  // enum indicating operator being performed

    char *instruction_str;  // original string from file

    // The different parts of the string
    // When a value is null, it does not exist in the instruction_string
    char *operand_a_str;
    char *operand_b_str;
};

void initialize_memory();
/*** main methods using address unsigned reference ***/
void set_mem_value_from_us_address(unsigned short address, char * property, char *value); // change the value of a property of that memory
void set_data_from_us_address(unsigned short address, unsigned short value); // change data value given us address
unsigned short get_mem_data_from_us_address(unsigned short address); // get the data of an address
char * get_instruction_str_from_us_address(unsigned short address); // I am tired, it's 5 in the morning, it does exactly what the name says
struct location_contents * get_mem_from_us_address(unsigned short address); // get the address of the memory based on the "dummy" address
void load_code_to_mem(char * path); // load the lines of code to memory

/*** main methods using address string reference ***/
void set_mem_value_from_str_address(char * address, char * property, char *value); // change the value of a property of that memory


/*** useful methods to make coding main methods easier ***/
int propertyToInt(char *property); // string to number property to avoid making duplicate methods for each property
enum OP getOperation(char * opera); // get operation OP given the operation string

#endif //CS203LAB5_MEM_H


