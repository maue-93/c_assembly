//
// Created by Eliso Morazara on 11/2/23.
//

#ifndef CS203LAB5_CPU_H
#define CS203LAB5_CPU_H

#include "string.h"
#include "ctype.h"

#include "mem.h"
#include "helper_methods.h"

/*** initialize method ***/
void initialize_cpu();

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
/*** main methods using register int reference ***/
void lodi_cpu(int reg, unsigned short im); // load an immediate value to a register

void add_cpu(int reg_a, int reg_b); // AC <= reg_a + reg_b
void sub_cpu(int reg_a, int reg_b); // AC <= reg_a - reg_b
void neg_cpu(int reg);              // reg <= -reg

void movr_cpu(int reg_a, int reg_b); // reg_b <= reg_a
void mova_cpu(int reg); // copies value of AC to a Register, reg is the index of the register

void loda_cpu(int reg, unsigned short address); // load value of the address to the register
void stoa_cpu(int reg, unsigned short address); // M[address].data <= reg

/*** main methods using register string reference ***/
void lodi_cpu_str(char* reg, char* im); // load an immediate value to a register

void add_cpu_str(char* reg_a, char* reg_b); // AC <= reg_a + reg_b
void sub_cpu_str(char* reg_a, char* reg_b); // AC <= reg_a - reg_b
void neg_cpu_str(char* reg);              // reg <= -reg

void movr_cpu_str(char* reg_a, char* reg_b); // reg_b <= reg_a
void mova_cpu_str(char* reg); // copies value of AC to a Register, reg is the index of the register

void loda_cpu_str(char* reg, char * address); // load value of the address to the register
void lorr_cpu_str(char* reg, char *para_address); // reg_a <= M[address].data

void stoa_cpu_str(char * reg, char * address); // M[address].data <= reg
void stor_cpu_str(char * reg, char * para_address); // M[address].data <= reg

// im for immediate value and para_no_para_address mean direct or indirect address
// just realized I could rename any parameters to direct or indirect address but I don't really have the time
void stoi_cpu_str(char * im, char * para_no_para_address);

void call_cpu_str(char * address); // call a function given the address
void ret_cpu_str(); // return

void display_cpu(); // print current state of the cpu
void display_mem(char * start, char * stop); // display memory

void perform_IR(); // perform the instruction in IR

void run_program(); // read and execute code

void read_code_from_file_then_run(char* path);

/*** useful methods to make coding main methods easier ***/

unsigned short get_Reg(int reg); // get value of register

int para_address_to_IV(char * para_address); // (reg) or (reg + ind) or (reg - ind) to unsigned short in IV, return 1 if succesful, 0 otherwise


#endif //CS203LAB5_CPU_H
