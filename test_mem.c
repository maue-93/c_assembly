//
// Created by Eliso Morazara on 11/7/23.
//
#include "assert.h"

#include "mem.h"
// have a copy of memory to do the test
struct location_contents mem[ADDRESS_SIZE];
int mem_size;

int main(){

    initialize_memory();
    /*** main methods using address unsigned reference ***/
    /* test set_mem_value_from_us_address */
    // data
    set_mem_value_from_us_address(0, "data", "789");
    assert(mem[0].data == 789);
    set_mem_value_from_us_address(0x100, "data", "0x6");
    assert(mem[0x100].data == 0x6);
    set_mem_value_from_us_address(0x101, "data", "0b10101");
    assert(mem[0x101].data == 0b10101);
    set_mem_value_from_us_address(0x104, "data", "-0b10101");
    assert(mem[0x104].data == negation(0b10101));

    set_mem_value_from_us_address(0x104, "data", "-0bx10101"); // invalid value
    assert(mem[0x104].data == negation(0b10101)); // no change
    set_mem_value_from_us_address(0x104, "data", ""); // invalid value
    assert(mem[0x104].data == negation(0b10101)); // no change

    // operation
    set_mem_value_from_us_address(0x10, "operation", "data");
    assert(mem[0x10].operation == data);
    set_mem_value_from_us_address(0x11, "operation", "dumpmemory");
    assert(mem[0x11].operation == dumpmemory);
    set_mem_value_from_us_address(0x12, "operation", "dumpCPU");
    assert(mem[0x12].operation == dumpCPU);
    set_mem_value_from_us_address(0x13, "operation", "halt");
    assert(mem[0x13].operation == halt);
    set_mem_value_from_us_address(0x14, "operation", "jmp");
    assert(mem[0x14].operation == jmp);
    set_mem_value_from_us_address(0x15, "operation", "jmpz");
    assert(mem[0x15].operation == jmpz);
    set_mem_value_from_us_address(0x16, "operation", "jmpn");
    assert(mem[0x16].operation == jmpn);
    set_mem_value_from_us_address(0x17, "operation", "call");
    assert(mem[0x17].operation == call);
    set_mem_value_from_us_address(0x18, "operation", "ret");
    assert(mem[0x18].operation == ret);
    set_mem_value_from_us_address(0x19, "operation", "mova");
    assert(mem[0x19].operation == mova);
    set_mem_value_from_us_address(0x1a, "operation", "movr");
    assert(mem[0x1a].operation == movr);
    set_mem_value_from_us_address(0x1b, "operation", "lodi");
    assert(mem[0x1b].operation == lodi);
    set_mem_value_from_us_address(0x1c, "operation", "loda");
    assert(mem[0x1c].operation == loda);
    set_mem_value_from_us_address(0x1d, "operation", "lorr");
    assert(mem[0x1d].operation == lorr);
    set_mem_value_from_us_address(0x1e, "operation", "stoa");
    assert(mem[0x1e].operation == stoa);
    set_mem_value_from_us_address(0x1f, "operation", "stor");
    assert(mem[0x1f].operation == stor);
    set_mem_value_from_us_address(0x20, "operation", "stoi");
    assert(mem[0x20].operation == stoi);
    set_mem_value_from_us_address(0x21, "operation", "add");
    assert(mem[0x21].operation == add);
    set_mem_value_from_us_address(0x22, "operation", "sub");
    assert(mem[0x22].operation == sub);
    set_mem_value_from_us_address(0x23, "operation", "neg");
    assert(mem[0x23].operation == neg);

    // invalid operation
    set_mem_value_from_us_address(0x24, "operation", "neg ");
    assert(mem[0x24].operation == data);
    set_mem_value_from_us_address(0x25, "operation", "addsum");
    assert(mem[0x25].operation == data);
    set_mem_value_from_us_address(0x26, "operation", "");
    assert(mem[0x26].operation == data);
    set_mem_value_from_us_address(0x27, "operation", "whatever");
    assert(mem[0x27].operation == data);

    // test for the rest of properties because they are all strings
    // they will pretty much accept whatever thrown at them
    set_mem_value_from_us_address(0x28, "instruction_str", "lodi R0 0x123");
    assert(strcmp(mem[0x28].instruction_str, "lodi R0 0x123") == 0);

    set_mem_value_from_us_address(0x28, "operand_a_str", "R0");
    assert(strcmp(mem[0x28].operand_a_str, "R0") == 0);

    set_mem_value_from_us_address(0x28, "operand_b_str", "0x123");
    assert(strcmp(mem[0x28].operand_b_str, "0x123") == 0);

    set_mem_value_from_us_address(0x29, "instruction_str", "mova R1");
    assert(strcmp(mem[0x29].instruction_str, "mova R1") == 0);
    assert(strcmp(mem[0x28].instruction_str, "lodi R0 0x123") == 0);

    /* test set_data_from_us_address */
    set_data_from_us_address(0x100, 90);
    assert(mem[0x100].data == 90);

    set_data_from_us_address(0x102, 0b10101);
    assert(mem[0x102].data == 0b10101);

    /* test get_mem_data_from_us_address */
    set_mem_value_from_us_address(0, "data", "789");
    assert(get_mem_data_from_us_address(0) == 789);
    set_mem_value_from_us_address(0x100, "data", "0x6");
    assert(get_mem_data_from_us_address(0x100) == 0x6);
    set_mem_value_from_us_address(0x101, "data", "0b10101");
    assert(get_mem_data_from_us_address(0x101) == 0b10101);
    set_mem_value_from_us_address(0x104, "data", "-0b10101");
    assert(get_mem_data_from_us_address(0x104) == negation(0b10101));

    /*** main methods using address string reference ***/
    /* test set_mem_value_from_str_address */
    // data
    set_mem_value_from_str_address("0", "data", "789");
    assert(mem[0].data == 789);
    set_mem_value_from_str_address("0x100", "data", "0x6");
    assert(mem[0x100].data == 0x6);
    set_mem_value_from_str_address("0x101", "data", "0b10101");
    assert(mem[0x101].data == 0b10101);
    set_mem_value_from_str_address("0x104", "data", "-0b10101");
    assert(mem[0x104].data == negation(0b10101));

    set_mem_value_from_str_address("0x104", "data", "-0bx10101"); // invalid value
    assert(mem[0x104].data == negation(0b10101)); // no change
    set_mem_value_from_str_address("0x104", "data", ""); // invalid value
    assert(mem[0x104].data == negation(0b10101)); // no change

    // operation
    set_mem_value_from_str_address("0x10", "operation", "data");
    assert(mem[0x10].operation == data);
    set_mem_value_from_str_address("0x11", "operation", "dumpmemory");
    assert(mem[0x11].operation == dumpmemory);
    set_mem_value_from_str_address("0x12", "operation", "dumpCPU");
    assert(mem[0x12].operation == dumpCPU);
    set_mem_value_from_str_address("0x13", "operation", "halt");
    assert(mem[0x13].operation == halt);
    set_mem_value_from_str_address("0x14", "operation", "jmp");
    assert(mem[0x14].operation == jmp);
    set_mem_value_from_str_address("0x15", "operation", "jmpz");
    assert(mem[0x15].operation == jmpz);
    set_mem_value_from_str_address("0x16", "operation", "jmpn");
    assert(mem[0x16].operation == jmpn);
    set_mem_value_from_str_address("0x17", "operation", "call");
    assert(mem[0x17].operation == call);
    set_mem_value_from_str_address("0x18", "operation", "ret");
    assert(mem[0x18].operation == ret);
    set_mem_value_from_str_address("0x19", "operation", "mova");
    assert(mem[0x19].operation == mova);
    set_mem_value_from_str_address("0x1a", "operation", "movr");
    assert(mem[0x1a].operation == movr);
    set_mem_value_from_str_address("0x1b", "operation", "lodi");
    assert(mem[0x1b].operation == lodi);
    set_mem_value_from_str_address("0x1c", "operation", "loda");
    assert(mem[0x1c].operation == loda);
    set_mem_value_from_str_address("0x1d", "operation", "lorr");
    assert(mem[0x1d].operation == lorr);
    set_mem_value_from_str_address("0x1e", "operation", "stoa");
    assert(mem[0x1e].operation == stoa);
    set_mem_value_from_str_address("0x1f", "operation", "stor");
    assert(mem[0x1f].operation == stor);
    set_mem_value_from_str_address("0x20", "operation", "stoi");
    assert(mem[0x20].operation == stoi);
    set_mem_value_from_str_address("0x21", "operation", "add");
    assert(mem[0x21].operation == add);
    set_mem_value_from_str_address("0x22", "operation", "sub");
    assert(mem[0x22].operation == sub);
    set_mem_value_from_str_address("0x23", "operation", "neg");
    assert(mem[0x23].operation == neg);

    // invalid operation
    set_mem_value_from_str_address("0x24", "operation", "neg ");
    assert(mem[0x24].operation == data);
    set_mem_value_from_str_address("0x25", "operation", "addsum");
    assert(mem[0x25].operation == data);
    set_mem_value_from_str_address("0x26", "operation", "");
    assert(mem[0x26].operation == data);
    set_mem_value_from_str_address("0x27", "operation", "whatever");
    assert(mem[0x27].operation == data);

    // test for the rest of properties because they are all strings
    // they will pretty much accept whatever thrown at them
    set_mem_value_from_us_address(0x28, "instruction_str", "lodi R0 0x123");
    assert(strcmp(mem[0x28].instruction_str, "lodi R0 0x123") == 0);

    set_mem_value_from_us_address(0x28, "operand_a_str", "R0");
    assert(strcmp(mem[0x28].operand_a_str, "R0") == 0);

    set_mem_value_from_us_address(0x28, "operand_b_str", "0x123");
    assert(strcmp(mem[0x28].operand_b_str, "0x123") == 0);


    /*** useful methods to make coding main methods easier ***/
    /* test getOperation */
    assert(getOperation("data") == data);
    assert(getOperation("dumpCPU") == dumpCPU);
    assert(getOperation("halt") == halt);
    assert(getOperation("jmp") == jmp);
    assert(getOperation("jmpz") == jmpz);
    assert(getOperation("jmpn") == jmpn);
    assert(getOperation("call") == call);
    assert(getOperation("ret") == ret);
    assert(getOperation("mova") == mova);
    assert(getOperation("movr") == movr);
    assert(getOperation("lodi") == lodi);
    assert(getOperation("loda") == loda);
    assert(getOperation("lorr") == lorr);
    assert(getOperation("stoa") == stoa);
    assert(getOperation("stor") == stor);
    assert(getOperation("stoi") == stoi);
    assert(getOperation("add") == add);
    assert(getOperation("sub") == sub);
    assert(getOperation("neg") == neg);

    // invalid string operation is by default data
    assert(getOperation("data  ") == data);
    assert(getOperation("djflkd") == data);
    assert(getOperation("") == data);
    assert(getOperation("dkkl") == data);


    return 0;
}
