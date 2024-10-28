//
// Created by Eliso Morazara on 11/2/23.
//
#include "stdlib.h"

#include "cpu.h"

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

unsigned short R[4];    // general purpose registers
unsigned short AC;      //accumulator, stores result of last operation (add or sub)

unsigned short SP;      // stack pointer, referencing next instruction
unsigned short BP;      // base pointer, referencing the local context
unsigned short ProC;    // program counter, referencing the next instruction

struct location_contents *IR; //instruction register referencing current instruction

/*** initialize method ***/
void initialize_cpu() {
    // initialize general purpose registers to zero
    R[0] = 0;
    R[1] = 0;
    R[2] = 0;
    R[3] = 0;

    // initialize special purpose accumulator to zero
    AC = 0;

    // initialize stack pointer to rhe start of the stack
    SP = 0x100;

    // initialize base pointer to the start of the stack
    BP = 0x100;

    // initialize the program counter to the start of code memory
    ProC = 0x10;

    // initialize the instruction register to empty
    IR = NULL;
}

/*** main methods using register int reference ***/
void lodi_cpu(int reg, unsigned short im){
    // a function to decode a string parameter to a reg int parameter will be made in upper level
    if (reg < 0) return; // must be 0 or greater
    if (reg < 4) R[reg] = im;
    if (reg == 5) SP = im;
    if (reg == 6) BP = im;
    if (reg == 7) ProC = im;
    // if reg is 4 (AC) or other than the valid reg above, do nothing
}

void add_cpu(int reg_a, int reg_b){
    if((reg_a < 0) || (reg_a > 3) || (reg_b < 0) || (reg_b > 3)) return;
    AC = add_uns(R[reg_a], R[reg_b]); // load sum to AC
}

void sub_cpu(int reg_a, int reg_b){
    if((reg_a < 0) || (reg_a > 3) || (reg_b < 0) || (reg_b > 3)) return;
    AC = add_uns(R[reg_a], negation(R[reg_b])); // load difference to AC
}

void neg_cpu(int reg){
    if((reg < 0) || (reg > 3)) return;
    R[reg] = negation(R[reg]); // reg <= -reg
}

void movr_cpu(int reg_a, int reg_b){
    if((reg_a < 0) || (reg_a > 7)) return; // reg_a in [0, 7], this step necessary because get_reg assumes reg_a is valid
    lodi_cpu(reg_b, get_Reg(reg_a));
}

void mova_cpu(int reg){
    movr_cpu(4, reg);
}

void loda_cpu(int reg, unsigned short address){
    // lodi will take care of the reg if it is valid or not so no need to check here
    lodi_cpu(reg, get_mem_data_from_us_address(address));
}

void stoa_cpu(int reg, unsigned short address){
    if(reg < 0 || reg > 7) return; // reg must be valid
    set_data_from_us_address(address, get_Reg(reg));
}

/*** main methods using register string reference ***/
void lodi_cpu_str(char* reg, char* im){
    int valid_im = str_val_to_us_IV(im); // check if im is valid and change IV if valid
    if(valid_im) lodi_cpu(regStrToInt(reg), IV); // run lodi if im is valid
}

void add_cpu_str(char* reg_a, char* reg_b){
    add_cpu(regStrToInt(reg_a), regStrToInt(reg_b));
}

void sub_cpu_str(char* reg_a, char* reg_b){
    sub_cpu(regStrToInt(reg_a), regStrToInt(reg_b));
}

void neg_cpu_str(char* reg){
    neg_cpu(regStrToInt(reg));
}

void movr_cpu_str(char* reg_a, char* reg_b){
    movr_cpu(regStrToInt(reg_a), regStrToInt(reg_b));
}

void mova_cpu_str(char* reg){
    mova_cpu(regStrToInt(reg));
}

void loda_cpu_str(char* reg, char * address){
    int valid_address = str_val_to_us_IV(address); // check if address is valid and change IV if valid
    if(valid_address) loda_cpu(regStrToInt(reg), IV); // perform the loda
}

void lorr_cpu_str(char* reg, char *para_address){
    int reg_num = regStrToInt(reg);
    if((reg_num < 0) || (reg_num > 7)) return; // reg_b in [0, 7], this step necessary because get_reg assumes reg_b is valid
    // if reg and address valid, perform loda, it will check if reg is ac so no need to check that here
    if(para_address_to_IV(para_address)) loda_cpu(regStrToInt(reg), IV);
}

void stoa_cpu_str(char * reg, char * address){
    int reg_num = regStrToInt(reg);
    // if valid address perform the stoa
    if(str_val_to_us_IV(address)) stoa_cpu(reg_num, IV);
}

void stor_cpu_str(char * reg, char * para_address){
    int reg_num = regStrToInt(reg);
    if((reg_num < 0) || (reg_num > 7)) return; // reg_b in [0, 7], this step necessary because get_reg assumes reg_b is valid
    // if reg and address valid, perform stoa
    if(para_address_to_IV(para_address)) stoa_cpu(reg_num, IV);
}

void stoi_cpu_str(char * im, char * para_no_para_address){
    if(!str_val_to_us_IV(im)) return; // if im invalid, return
    unsigned short immediate = IV; // copy value of IV to immediate

    // the address could be a direct address or indirect address (with parentheses)
    unsigned short address = 0;
    if(str_val_to_us_IV(para_no_para_address)) {
        // direct address
        address = IV;
    }
    else if(para_address_to_IV(para_no_para_address)){
        // indirect address
        address = IV;
    }
    else {
        // invalid address
        return;
    }

    set_data_from_us_address(address, immediate); // change the data of the memory at the address
}

void call_cpu_str(char * address){
    stor_cpu_str("PC", "(SP)"); // M[SP] <= PC
    lodi_cpu_str("PC", address);        // PC <= address
    SP = SP + 1;                                // SP <= SP + 1
    stor_cpu_str("BP", "(SP)"); // M[SP] <= BP
    movr_cpu_str("SP", "BP");       // BP <= SP
    SP = SP + 1;                                // SP <= SP + 1
}

void ret_cpu_str(){
    movr_cpu_str("BP", "SP");       // SP <= BP
    lorr_cpu_str("BP", "(SP)"); // BP <= M[SP]
    SP = SP - 1;                                // SP <= SP - 1
    lorr_cpu_str("PC", "(SP)"); // BP <= M[SP]
}

void display_cpu(){
    printf("\n>>\t\t\tCPU\n");
    printf("==========================\n");
    printf("||  PC : %07p\t\t||\n", ProC);
    printf("||  IR : %s\n", (IR) ? IR->instruction_str : "EMPTY");
    printf("||  SP : %07p\t\t||\n", SP);
    printf("||  BP : %07p\t\t||\n", BP);
    printf("||  R0 : %07p\t\t||\n", R[0]);
    printf("||  R1 : %07p\t\t||\n", R[1]);
    printf("||  R2 : %07p\t\t||\n", R[2]);
    printf("||  R3 : %07p\t\t||\n", R[3]);
    printf("||  AC : %07p\t\t||\n", AC);
    printf("==========================\n");
}

void display_mem(char * start, char * stop){
    if(!str_val_to_us_IV(start)) return; // if invalid number for start, do nothing
    unsigned short start_add = IV; // get the unsigned version and store
    if(!str_val_to_us_IV(stop)) return; // if invalid number for stop, do nothing
    unsigned short stop_add = IV; // get the unsigned version and store

    if(stop_add < start_add) return; // stop must be greater than start
    printf("\n>>\t\t\t\t MEMORY\n");
    printf("===================================================\n");
    printf("\tADDRESS\t:\t DATA  \t:\t INSTRUCTION\n");
    for(int i = start_add; i <= stop_add; i++){
        printf("||\t%07p\t:\t%07p\t:\t%s\n",
               i, get_mem_data_from_us_address(i),
               (get_instruction_str_from_us_address(i)) ? (get_instruction_str_from_us_address(i)): "");
    }
    printf("===================================================\n");

}

void perform_IR(){
    if(IR == NULL) return;
    if(IR->operation == data) goto input_error;
    if(IR->operation == halt) {
        // if that is a string following halt
        if(IR->operand_a_str != NULL) goto input_error;
        printf("\n>> PROGRAM HALTED");
        // restore memory and cpu then exit
        initialize_cpu();
        initialize_memory();
        exit(-1);
    }

    if(IR->operation == jmp) {
        // must have operand a but not b and operand a must be a valid address
        if((IR->operand_a_str == NULL) || (IR->operand_b_str != NULL) || !str_val_to_us_IV(IR->operand_a_str)) {
            goto input_error;
        }
        lodi_cpu_str("PC", IR->operand_a_str); return;
    }

    if(IR->operation == jmpz) {
        // must have operand a but not b and AC must be 0 and operand a must be a valid address
        if((IR->operand_a_str == NULL) || (IR->operand_b_str != NULL) || !str_val_to_us_IV(IR->operand_a_str)) {
            goto input_error;
        }
        if (AC == 0) lodi_cpu_str("PC", IR->operand_a_str);
        return;
    }

    if(IR->operation == jmpn) {
        // must have operand a but not b and AC must be less than 0 (bit at 15 is 1) and operand a must be a valid address
        if((IR->operand_a_str == NULL) || (IR->operand_b_str != NULL) || !str_val_to_us_IV(IR->operand_a_str)) {
            goto input_error;
        }
        if((bitAt(AC, 15) == 1)) lodi_cpu_str("PC", IR->operand_a_str);
        return;
    }

    if(IR->operation == call){
        // must have operand a but not b
        if((IR->operand_a_str == NULL) || (IR->operand_b_str != NULL)) goto input_error;
        if(!str_val_to_us_IV(IR->operand_a_str)) goto input_error; // if invalid address, return

        call_cpu_str(IR->operand_a_str); return;
    }

    if(IR->operation == ret){
        if(IR->operand_a_str != NULL) goto input_error; // no string should follow ret
        ret_cpu_str(); return;
    }

    if(IR->operation == dumpCPU){
        if(IR->operand_a_str != NULL) goto input_error; // no string should follow .display_cpu
        display_cpu(); return;
    }

    if(IR->operation == dumpmemory){
        if(!str_val_to_us_IV(IR->operand_a_str)) goto input_error; // operand must be valid address
        unsigned short opA = IV;
        if(!str_val_to_us_IV(IR->operand_b_str)) goto input_error; // operand must be valid address
        unsigned short opB = IV;
        if(opB < opA) goto input_error; // first operand must be less than the second
        display_mem(IR->operand_a_str, IR->operand_b_str); return;
    }

    if(IR->operation == mova){
        // if invalid register or have extra substring, invalid
        if((regStrToInt(IR->operand_a_str) == -1) || (IR->operand_b_str != NULL)) goto input_error;
        mova_cpu_str(IR->operand_a_str); return;
    }

    if(IR->operation == movr){
        // both operand must be valid registers and reg_b is not AC
        if((regStrToInt(IR->operand_a_str) == -1) || (regStrToInt(IR->operand_b_str) == -1) || (regStrToInt(IR->operand_b_str) == 4)){
            goto input_error;
        }
        movr_cpu_str(IR->operand_a_str, IR->operand_b_str); return;
    }

    if(IR->operation == lodi){
        // reg_a must be valid and not AC and immediate value must be valid
        if((regStrToInt(IR->operand_a_str) == -1) || (regStrToInt(IR->operand_a_str) == 4) || !str_val_to_us_IV(IR->operand_b_str)){
            goto input_error;
        }
        lodi_cpu_str(IR->operand_a_str, IR->operand_b_str); return;
    }

    if(IR->operation == loda){
        // reg_a must be valid and not AC and address value must be valid
        if((regStrToInt(IR->operand_a_str) == -1) || (regStrToInt(IR->operand_a_str) == 4) || !str_val_to_us_IV(IR->operand_b_str)){
            goto input_error;
        }
        loda_cpu_str(IR->operand_a_str, IR->operand_b_str); return ;
    }

    if(IR->operation == lorr){
        // reg_a must be valid and not AC and address (indirect) value must be valid
        if((regStrToInt(IR->operand_a_str) == -1) || (regStrToInt(IR->operand_a_str) == 4) || !para_address_to_IV(IR->operand_b_str)){
            goto input_error;
        }
        lorr_cpu_str(IR->operand_a_str, IR->operand_b_str); return;
    }

    if(IR->operation == stoa){
        // reg_a must be valid and not AC and address value must be valid
        if((regStrToInt(IR->operand_a_str) == -1) || !str_val_to_us_IV(IR->operand_b_str)){
            goto input_error;
        }
        stoa_cpu_str(IR->operand_a_str, IR->operand_b_str); return;
    }

    if(IR->operation == stor){
        // reg_a must be valid and not AC and address (indirect) value must be valid
        if((regStrToInt(IR->operand_a_str) == -1) || !para_address_to_IV(IR->operand_b_str)){
            goto input_error;
        }
        stor_cpu_str(IR->operand_a_str, IR->operand_b_str); return;
    }

    if(IR->operation == stoi) {
        if(!str_val_to_us_IV(IR->operand_a_str)) goto input_error; // invalid immediate value
        // if invalid direct or indirect address
        if(!str_val_to_us_IV(IR->operand_b_str) && !para_address_to_IV(IR->operand_b_str)) goto input_error;

        stoi_cpu_str(IR->operand_a_str, IR->operand_b_str); return;
    }

    if(IR->operation == add){
        int reg_a = regStrToInt(IR->operand_a_str);
        int reg_b = regStrToInt(IR->operand_b_str);
        if(reg_a < 0 || reg_a > 3 || reg_b < 0 || reg_b > 3) goto input_error;
        add_cpu(reg_a, reg_b); return ;
    }

    if(IR->operation == sub){
        int reg_a = regStrToInt(IR->operand_a_str);
        int reg_b = regStrToInt(IR->operand_b_str);
        if(reg_a < 0 || reg_a > 3 || reg_b < 0 || reg_b > 3) goto input_error;
        sub_cpu(reg_a, reg_b); return ;
    }

    if(IR->operation == neg){
        int reg = regStrToInt(IR->operand_a_str);
        if(reg < 0 || reg > 3) goto input_error;
        neg_cpu(reg); return ;
    }

    input_error:
    fprintf(stderr, "Error in Code line %d", (ProC - 0x10));
    exit(-1);
}

void run_program(){
    // will keep running until there is an error or halt
    while(1) {
        IR = get_mem_from_us_address(ProC); // IR <= M[PC]
        ProC += 1;                                  // PC = PC + 1
        perform_IR();                               // perform the task
    }
}

void read_code_from_file_then_run(char* path){
    initialize_cpu();
    initialize_memory();
    load_code_to_mem(path);
    run_program();
}

/*** useful methods to make coding main methods easier ***/

unsigned short get_Reg(int reg){
    // assuming reg is valid because this function is only called when reg is valid, reg in [0, 7]
    if(reg < 4) return R[reg];
    if (reg == 4) return AC;
    if (reg == 5) return SP;
    if (reg == 6) return BP;
    return ProC; // if reg == 7
}

int para_address_to_IV(char * para_address){
    char *copy = para_address;
    char *tmp = malloc(sizeof (copy));
    char * param1 = NULL;
    char * param2 = NULL;
    char operation = '\0';

    // get para_address without space
    int i = 0;
    while(*copy){
        if(*copy == ' ') { copy++; continue; }
        tmp[i++] = *(copy++);
    }
    tmp[i] = '\0'; // terminate

    if(*tmp != '(') return 0; // the first character has to be (
    tmp++;
    param1 = tmp++; // get param1 then increment

    while(*tmp && (*tmp != '+') && (*tmp != '-') && (*tmp != ')')) tmp++; // go through characters of param1
    if(*tmp == '-') operation = '-';
    if(*tmp == '+') operation = '+';
    *tmp = '\0'; // terminate param1 no matter what
    tmp++; // increment tmp no matter what

    if(operation && iscntrl(*tmp)) return 0; // if operation found and the rest is empty, invalid

    // if one param1 only
    if(!operation && iscntrl(*tmp)) {
        // if it is a number string
        if(str_val_to_us_IV(param1)) {
            // the unsigned value is stored in IV then return 1;
            return 1;
        }

        // if it is a register instead
        int regi = regStrToInt(param1);
        if(regi != -1) {
            IV = get_Reg(regi); // store the value of register in IV
            return 1; // return 1
        }
        return 0; // if both invalid, return 0
    }

    param2 = tmp; // get param2
    while(*tmp && (*tmp != ')')) tmp++; // go through important characters
    if(iscntrl(*tmp)) return 0; // if end of string, not valid
    if(*tmp == ')') *tmp = '\0'; // if ) found terminate
    if(!iscntrl(*(tmp + 1))) return 0; // however, if it is not the end of the string, it is invalid


    // so we have param1, operation, and param2

    // let's take care of param1 first
    unsigned short param1num = 0;
    int reg1 = regStrToInt(param1);
    // if it is a number string
    if(str_val_to_us_IV(param1)) {
        // the unsigned value is stored in IV so get it and store in param1num
        param1num = IV;
    }
    else if(reg1 != -1) { // if it is a register instead
        param1num = get_Reg(reg1); // store the value of register in IV
    }
    else { // if not a number and not a register
        return 0; // if both invalid, return 0
    }

    // let's take care of param2 now
    unsigned short param2num = 0;
    int reg2 = regStrToInt(param2);
    // if it is a number string
    if(str_val_to_us_IV(param2)) {
        // the unsigned value is stored in IV so get it and store in param2num
        param2num = IV;
    }
    else if(reg2 != -1) { // if it is a register instead
        param2num = get_Reg(reg2); // store the value of register in IV
    }
    else { // if not a number and not a register
        return 0; // if both invalid, return 0
    }

    // let's take care of the operation
    if(operation == '-') param2num = negation(param2num); // if subtraction, negate param2num

    IV = add_uns(param1num, param2num); // store the result in IV to be retrieved after

    return 1;
}
