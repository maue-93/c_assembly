//
// Created by Eliso Morazara on 11/7/23.
//

#include "mem.h"

struct location_contents mem[ADDRESS_SIZE];
int mem_size;

// initializes the main memory to empty values,
// and a dot operation
void initialize_memory(){
    for (int i = 0; i < ADDRESS_SIZE; i++){
        mem[i].data = 0x0;
        mem[i].operation = data;

        mem[i].instruction_str = NULL;
        mem[i].operand_a_str = NULL;
        mem[i].operand_b_str = NULL;
    }
}

/*** main methods using unsigned address reference ***/

void set_mem_value_from_us_address(unsigned short address, char * property, char *value){
    if(strcmp(property, "data") == 0) {
        int valid_value = str_val_to_us_IV(value);
        if(!valid_value) return;
        mem[address].data = IV;
        return;
    }

    if(strcmp(property, "operation") == 0) {
        mem[address].operation = getOperation(value);
        return;
    }


    if(strcmp(property, "instruction_str") == 0) {
        // make a copy of the value because a pointer changes all the time
        char * value_copy = (char *) malloc(strlen(value));
        memcpy(value_copy, value, strlen(value));
        mem[address].instruction_str = value_copy;
        return;
    }

    if(strcmp(property, "operand_a_str") == 0) {
        // make a copy of the value because a pointer changes all the time
        char * value_copy = (char *) malloc(strlen(value));
        memcpy(value_copy, value, strlen(value));
        mem[address].operand_a_str = value_copy;
        return;
    }

    if(strcmp(property, "operand_b_str") == 0) {
        // make a copy of the value because a pointer changes all the time
        char * value_copy = (char *) malloc(strlen(value));
        memcpy(value_copy, value, strlen(value));
        mem[address].operand_b_str = value_copy;
        return;
    }

}

void set_data_from_us_address(unsigned short address, unsigned short value){
    mem[address].data = value;
}

unsigned short get_mem_data_from_us_address(unsigned short address){
    unsigned short res = mem[address].data;
    return res;
}

char * get_instruction_str_from_us_address(unsigned short address){
    return mem[address].instruction_str;
}

struct location_contents * get_mem_from_us_address(unsigned short address){
    // because of time, I will not unit test this
    return &mem[address];
}

void load_code_to_mem(char * path){
    FILE *file;
    file = fopen(path, "r");
    if (file == NULL){
        printf("ERROR: %s\n", __FUNCTION__);
        printf("     : %s\n", strerror(errno));

        // will end the program
        exit(-1);
    }

    char *line = malloc(128);
    int line_cnt = 0;
    char * str; // extract operation, and operands

    unsigned short address = 0x10;
    while(fgets(line, 128, file) != NULL) {
        line_cnt++; // increment line_cnt

        while(*line == ' ') line++; // get rid of spaces
        str = line;
        // break the line
        while(!iscntrl(*str)) str++;
        if(*str == '\n') *str++ = '\0';
        else *++str = '\0'; // somehow *++str = '\0' instead of *str++ = '\0' solved my problem with single operand at the end issue
        // set instruction_str
        set_mem_value_from_us_address(address, "instruction_str", line);

        // set operation
        str = line;
        while(!iscntrl(*str) && *str != ' ') str++; // go through the characters
        *str = '\0'; str++; // terminate and increment
        set_mem_value_from_us_address(address, "operation", line);

        if(iscntrl(*str)) goto continues; // if no character left, move to the next line

        while(*str == ' ') str++; // get rid of the spaces
        line = str; // for this sake, we are just using line as a temp variable
        while(!iscntrl(*str) && *str != ' ') str++; // go through the characters
        *str++ = '\0'; // terminate and increment
        set_mem_value_from_us_address(address, "operand_a_str", line);

        if(iscntrl(*str)) goto continues; // if no character left, move to the next line

        while(*str == ' ') str++; // get rid of the spaces
        line = str; // for this sake, we are just using line as a temp variable
        while(!iscntrl(*str)) str++; // go through the characters including space, get all the rest of the line
        *str++ = '\0'; // terminate and increment
        set_mem_value_from_us_address(address, "operand_b_str", line);

        continues:
        address++; // increment address
    }

    fclose(file); // close file

}

/*** main methods using string address reference ***/
void set_mem_value_from_str_address(char * address, char * property, char *value){
    int valid_address = str_val_to_us_IV(address);
    if(!valid_address) return;
    set_mem_value_from_us_address(IV, property, value);
}


/*** useful methods to make coding main methods easier ***/
enum OP getOperation(char * opera){
    if(strcmp(opera, ".display_mem") == 0) return dumpmemory;
    if(strcmp(opera, ".display_cpu") == 0) return dumpCPU;
    if(strcmp(opera, "halt") == 0) return halt;
    if(strcmp(opera, "jmp") == 0) return jmp;
    if(strcmp(opera, "jmpz") == 0) return jmpz;
    if(strcmp(opera, "jmpn") == 0) return jmpn;
    if(strcmp(opera, "call") == 0) return call;
    if(strcmp(opera, "ret") == 0) return ret;
    if(strcmp(opera, "mova") == 0) return mova;
    if(strcmp(opera, "movr") == 0) return movr;
    if(strcmp(opera, "lodi") == 0) return lodi;
    if(strcmp(opera, "loda") == 0) return loda;
    if(strcmp(opera, "lorr") == 0) return lorr;
    if(strcmp(opera, "stoa") == 0) return stoa;
    if(strcmp(opera, "stor") == 0) return stor;
    if(strcmp(opera, "stoi") == 0) return stoi;
    if(strcmp(opera, "add") == 0) return add;
    if(strcmp(opera, "sub") == 0) return sub;
    if(strcmp(opera, "neg") == 0) return neg;

    return data; // default
}

