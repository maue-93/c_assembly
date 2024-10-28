//
// Created by Eliso Morazara on 11/5/23.
//

#include "assert.h"

#include "cpu.h"

// create copies of the cpu variables
unsigned short R[4];    // general purpose registers
unsigned short AC;      //accumulator, stores result of last operation (add or sub)

unsigned short SP;      // stack pointer, referencing next instruction
unsigned short BP;      // base pointer, referencing the local context
unsigned short ProC;    // program counter, referencing the next instruction

struct location_contents *IR; //instruction register referencing current instruction


int main(){
    /** test main methods in cpu ***/
    /* test initialize_cpu */
    initialize_cpu();
    for (int i = 0; i < 4; i++) assert(R[i] == 0);
    assert(AC == 0);
    assert(SP == 0x100);
    assert(BP == 0x100);
    assert(ProC == 0x10);
    assert(IR == NULL);

    /* test lodi_cpu */
    // making sure that negative number for reg will just do nothing
    lodi_cpu(-1, 7);
    for (int i = 0; i < 4; i++) assert(R[1] == 0);
    assert(AC == 0);
    assert(SP == 0x100);
    assert(BP == 0x100);
    assert(ProC == 0x10);
    assert(IR == NULL);

    // making sure that number greater than 7 for reg will just do nothing
    lodi_cpu(8, 9);
    for (int i = 0; i < 4; i++) assert(R[1] == 0);
    assert(AC == 0);
    assert(SP == 0x100);
    assert(BP == 0x100);
    assert(ProC == 0x10);
    assert(IR == NULL);

    // making sure that 4 for reg will just do nothing
    lodi_cpu(8, 9);
    for (int i = 0; i < 4; i++) assert(R[1] == 0);
    assert(AC == 0);
    assert(SP == 0x100);
    assert(BP == 0x100);
    assert(ProC == 0x10);
    assert(IR == NULL);

    // test on R0...R3
    lodi_cpu(0, 90);
    assert(R[0] == 90);
    lodi_cpu(1, 34789);
    assert(R[1] == 34789);
    lodi_cpu(2, 986);
    assert(R[2] == 986);
    lodi_cpu(3, 1);
    assert(R[3] == 1);

    // test on SP, BP, and ProC or PC
    lodi_cpu(5, 0x104);
    assert(SP == 0x104);
    lodi_cpu(6, 0x102);
    assert(BP == 0x102);
    lodi_cpu(7, 0x2c);
    assert(ProC == 0x2c);

    /* test add_cpu */
    lodi_cpu(0, 0);
    add_cpu(0, 0);
    assert(AC == 0);

    lodi_cpu(0, 0);
    lodi_cpu(1, 0b1111111111111111);
    add_cpu(0, 1);
    assert(AC == 0b1111111111111111);

    lodi_cpu(1, 0b1111111111111111);
    lodi_cpu(2, 0b1111111111111111);
    add_cpu(1, 2);
    assert(AC == 0b1111111111111110);

    lodi_cpu(2, 0b0111111111111111);
    lodi_cpu(3, 0b0111111111111111);
    add_cpu(3, 2);
    assert(AC == 0b1111111111111110);

    lodi_cpu(3, 0b0100000000000000);
    lodi_cpu(0, 0b0100000000000000);
    add_cpu(3, 0);
    assert(AC == 0b1000000000000000);

    lodi_cpu(3, 0b0100000000000000);
    lodi_cpu(0, 0b1110000000000000);
    add_cpu(3, 0);
    assert(AC == 0b10000000000000);

    // should not change anything
    add_cpu(-1, 0);
    assert(AC == 0b10000000000000);
    add_cpu(1, 4);
    assert(AC == 0b10000000000000);

    /* test sub */
    lodi_cpu(0, 0b1111111111111001);
    sub_cpu(0, 0);
    assert(AC == 0);

    lodi_cpu(0, 0);
    lodi_cpu(1, 1);
    sub_cpu(0, 1);
    assert(AC == 0b1111111111111111);

    lodi_cpu(1, 0b1111111111111111);
    lodi_cpu(2, 1);
    sub_cpu(1, 2);
    assert(AC == 0b1111111111111110);

    lodi_cpu(2, 0b0111111111111111);
    lodi_cpu(3, 0b1000000000000001);
    sub_cpu(2, 3);
    assert(AC == 0b1111111111111110);

    lodi_cpu(3, 0b0100000000000000);
    lodi_cpu(0, 0b1100000000000000);
    sub_cpu(3, 0);
    assert(AC == 0b1000000000000000);

    lodi_cpu(3, 0b0100000000000000);
    lodi_cpu(0, 0b0010000000000000);
    sub_cpu(3, 0);
    assert(AC == 0b10000000000000);

    // should not change anything
    sub_cpu(-1, 0);
    assert(AC == 0b10000000000000);
    sub_cpu(1, 4);
    assert(AC == 0b10000000000000);

    /* test neg */
    lodi_cpu(0, 0);
    neg_cpu(0);
    assert(R[0] == 0);

    lodi_cpu(1, 0b1111111111111111);
    neg_cpu(1);
    assert(R[1] == 1);

    lodi_cpu(2, 0b0101010101010101);
    neg_cpu(2);
    assert(R[2] == 0b1010101010101011);

    lodi_cpu(3, 0b1010101010101010);
    neg_cpu(3);
    assert(R[3] == 0b0101010101010110);

    lodi_cpu(0, 0);
    lodi_cpu(1, 1);
    sub_cpu(0, 1);
    movr_cpu(1, 4);
    assert(AC == 0b1111111111111111);

    /* test movr_cpu */
    initialize_cpu();

    lodi_cpu(0, 90);
    movr_cpu(0, 1);
    assert(R[1] == 90);

    lodi_cpu(1, 34789);
    movr_cpu(1, 2);
    assert(R[2] == 34789);

    lodi_cpu(2, 986);
    movr_cpu(2, 3);
    assert(R[3] == 986);

    movr_cpu(3, 4); // should do nothing
    assert(AC == 0);

    movr_cpu(3, 5);
    assert(SP == 986);

    movr_cpu(5, 6);
    assert(BP == 986);

    lodi_cpu(5, 0x168);
    movr_cpu(5, 1);
    assert(R[1] == 0x168);

    lodi_cpu(2, 0x1A);
    movr_cpu(2, 7);
    assert(ProC == 0x1A);
    movr_cpu(7, 3);
    assert(R[3] == 0x1A);

    /* test mova_cpu */
    lodi_cpu(0, 1);
    add_cpu(0, 0);
    mova_cpu(0);
    assert(R[0] == 2);

    lodi_cpu(0, 0);
    lodi_cpu(1, 0b1111111111111111);
    add_cpu(0, 1);
    mova_cpu(1);
    assert(R[1] == 0b1111111111111111);

    lodi_cpu(1, 0b1111111111111111);
    lodi_cpu(2, 0b1111111111111111);
    add_cpu(1, 2);
    mova_cpu(2);
    assert(R[2] == 0b1111111111111110);

    lodi_cpu(2, 0b0111111111111111);
    lodi_cpu(3, 0b0111111111111111);
    add_cpu(3, 2);
    mova_cpu(3);
    assert(R[3] == 0b1111111111111110);

    lodi_cpu(3, 0b0100000000000000);
    lodi_cpu(0, 0b0100000000000000);
    add_cpu(3, 0);
    mova_cpu(5);
    assert(SP == 0b1000000000000000);

    lodi_cpu(3, 0b0100000000000000);
    lodi_cpu(0, 0b1110000000000000);
    add_cpu(3, 0);
    mova_cpu(6);
    assert(BP == 0b10000000000000);

    lodi_cpu(0, 0);
    lodi_cpu(1, 1);
    sub_cpu(0, 1);
    mova_cpu(7);
    assert(ProC == 0b1111111111111111);

    /* test loda_cpu */
    lodi_cpu(0, 87);
    loda_cpu(0, 0x100);
    assert(R[0] == get_mem_data_from_us_address(0x100));

    lodi_cpu(3, 90);
    loda_cpu(3, 0x102);
    assert(R[3] == get_mem_data_from_us_address(0x102));

    /* test stoa_cpu */
    lodi_cpu(3, 90);
    stoa_cpu(3, 0x67b);
    assert(get_mem_data_from_us_address(0x67b) == 90);

    lodi_cpu(7, 0x9af);
    stoa_cpu(7, 0xabd);
    assert(get_mem_data_from_us_address(0xabd) == 0x9af);


    /*** main methods using register string reference ***/
    /* lodi_cpu_str */
    initialize_cpu();
    // making sure that invalid register input will result in no change
    lodi_cpu_str("R4", "0x89");
    for (int i = 0; i < 4; i++) assert(R[1] == 0);
    assert(AC == 0);
    assert(SP == 0x100);
    assert(BP == 0x100);
    assert(ProC == 0x10);
    assert(IR == NULL);

    // making sure that invalid value input will result in no change
    lodi_cpu_str("R2", "0xx78");
    for (int i = 0; i < 4; i++) assert(R[1] == 0);
    assert(AC == 0);
    assert(SP == 0x100);
    assert(BP == 0x100);
    assert(ProC == 0x10);
    assert(IR == NULL);

    // making sure that AC for reg will just do nothing
    lodi_cpu_str("AC", "89");
    for (int i = 0; i < 4; i++) assert(R[1] == 0);
    assert(AC == 0);
    assert(SP == 0x100);
    assert(BP == 0x100);
    assert(ProC == 0x10);
    assert(IR == NULL);

    // test on R0...R3
    lodi_cpu_str("R0", "90");
    assert(R[0] == 90);
    lodi_cpu_str("R1", "34789");
    assert(R[1] == 34789);
    lodi_cpu_str("R2", "0x986");
    assert(R[2] == 0x986);
    lodi_cpu_str("R3", "0b11");
    assert(R[3] == 3);

    // test on SP, BP, and ProC or PC
    lodi_cpu_str("SP", "0x104");
    assert(SP == 0x104);
    lodi_cpu_str("BP", "0x102");
    assert(BP == 0x102);
    lodi_cpu_str("PC", "0x2c");
    assert(ProC == 0x2c);

    /* test add_cpu_str */
    lodi_cpu_str("R0", "0");
    add_cpu_str("R0", "R0");
    assert(AC == 0);

    lodi_cpu_str("R0", "0");
    lodi_cpu_str("R1", "0b1111111111111111");
    add_cpu_str("R0", "R1");
    assert(AC == 0b1111111111111111);

    lodi_cpu_str("R1", "0b1111111111111111");
    lodi_cpu_str("R2", "0b1111111111111111");
    add_cpu_str("R1", "R2");
    assert(AC == 0b1111111111111110);

    lodi_cpu_str("R2", "0b0111111111111111");
    lodi_cpu_str("R3", "0b0111111111111111");
    add_cpu_str("R3", "R2");
    assert(AC == 0b1111111111111110);

    lodi_cpu_str("R3", "0b0100000000000000");
    lodi_cpu_str("R0", "0b0100000000000000");
    add_cpu_str("R3", "R0");
    assert(AC == 0b1000000000000000);

    lodi_cpu_str("R3", "0b0100000000000000");
    lodi_cpu_str("R0", "0b1110000000000000");
    add_cpu_str("R3", "R0");
    assert(AC == 0b10000000000000);

    // should not change anything
    add_cpu_str("AC", "R0");
    assert(AC == 0b10000000000000);
    add_cpu_str("R1", "AC");
    assert(AC == 0b10000000000000);

    /* test sub_cpu_str */
    lodi_cpu_str("R0", "0b1111111111111001");
    sub_cpu_str("R0", "R0");
    assert(AC == 0);

    lodi_cpu_str("R0", "0");
    lodi_cpu_str("R1", "1");
    sub_cpu_str("R0", "R1");
    assert(AC == 0b1111111111111111);

    lodi_cpu_str("R1", "0b1111111111111111");
    lodi_cpu_str("R2", "1");
    sub_cpu_str("R1", "R2");
    assert(AC == 0b1111111111111110);

    lodi_cpu_str("R2", "0b0111111111111111");
    lodi_cpu_str("R3", "0b1000000000000001");
    sub_cpu_str("R2", "R3");
    assert(AC == 0b1111111111111110);

    lodi_cpu_str("R3", "0b0100000000000000");
    lodi_cpu_str("R0", "0b1100000000000000");
    sub_cpu_str("R3", "R0");
    assert(AC == 0b1000000000000000);

    lodi_cpu_str("R3", "0b0100000000000000");
    lodi_cpu_str("R0", "0b0010000000000000");
    sub_cpu_str("R3", "R0");
    assert(AC == 0b10000000000000);

    // should not change anything
    sub_cpu_str("RP", "R0");
    assert(AC == 0b10000000000000);
    sub_cpu_str("R1", "AC");
    assert(AC == 0b10000000000000);

    /* test neg_cpu_str */
    lodi_cpu_str("R0", "0");
    neg_cpu_str("R0");
    assert(R[0] == 0);

    lodi_cpu_str("R1", "0b1111111111111111");
    neg_cpu_str("R1");
    assert(R[1] == 1);

    lodi_cpu_str("R2", "0b0101010101010101");
    neg_cpu_str("R2");
    assert(R[2] == 0b1010101010101011);

    lodi_cpu_str("R3", "0b1010101010101010");
    neg_cpu_str("R3");
    assert(R[3] == 0b0101010101010110);

    lodi_cpu_str("R0", "0");
    lodi_cpu_str("R1", "1");
    sub_cpu_str("R0", "R1");
    movr_cpu_str("R1", "AC"); // should not change AC
    assert(AC == 0b1111111111111111);


    /* test movr_cpu_str */
    initialize_cpu();

    lodi_cpu_str("R0", "90");
    movr_cpu_str("R0", "R1");
    assert(R[1] == 90);

    lodi_cpu_str("R1", "34789");
    movr_cpu_str("R1", "R2");
    assert(R[2] == 34789);

    lodi_cpu_str("R2", "986");
    movr_cpu_str("R2", "R3");
    assert(R[3] == 986);

    movr_cpu_str("R3", "AC"); // should do nothing
    assert(AC == 0);

    movr_cpu_str("R3", "SP");
    assert(SP == 986);

    movr_cpu_str("SP", "BP");
    assert(BP == 986);

    lodi_cpu_str("SP", "0x168");
    movr_cpu_str("SP", "R1");
    assert(R[1] == 0x168);

    lodi_cpu_str("R2", "0x1A");
    movr_cpu_str("R2", "PC");
    assert(ProC == 0x1A);
    movr_cpu_str("PC", "R3");
    assert(R[3] == 0x1A);

    /* test mova_cpu_str */
    lodi_cpu_str("R0", "1");
    add_cpu_str("R0", "R0");
    mova_cpu_str("R0");
    assert(R[0] == 2);

    lodi_cpu_str("R0", "0");
    lodi_cpu_str("R1", "0b1111111111111111");
    add_cpu_str("R0", "R1");
    mova_cpu_str("R1");
    assert(R[1] == 0b1111111111111111);

    lodi_cpu_str("R1", "0b1111111111111111");
    lodi_cpu_str("R2", "0b1111111111111111");
    add_cpu_str("R1", "R2");
    mova_cpu_str("R2");
    assert(R[2] == 0b1111111111111110);

    lodi_cpu_str("R2", "0b0111111111111111");
    lodi_cpu_str("R3", "0b0111111111111111");
    add_cpu_str("R3", "R2");
    mova_cpu_str("R3");
    assert(R[3] == 0b1111111111111110);

    lodi_cpu_str("R3", "0b0100000000000000");
    lodi_cpu_str("R0", "0b0100000000000000");
    add_cpu_str("R3", "R0");
    mova_cpu_str("SP");
    assert(SP == 0b1000000000000000);

    lodi_cpu_str("R3", "0b0100000000000000");
    lodi_cpu_str("R0", "0b1110000000000000");
    add_cpu_str("R3", "R0");
    mova_cpu_str("BP");
    assert(BP == 0b10000000000000);

    lodi_cpu_str("R0", "0");
    lodi_cpu_str("R1", "1");
    sub_cpu_str("R0", "R1");
    mova_cpu_str("PC");
    assert(ProC == 0b1111111111111111);

    /* test loda_cpu_str */
    lodi_cpu_str("R0", "87");
    loda_cpu_str("R0", "0x100");
    assert(R[0] == get_mem_data_from_us_address(0x100));

    lodi_cpu_str("R3", "90");
    loda_cpu_str("R3", "0x102");
    assert(R[3] == get_mem_data_from_us_address(0x102));

    /* test lorr_cpu_str */
    lodi_cpu_str("R0", "87");
    lodi_cpu_str("R1", "0x103");
    set_data_from_us_address(0x10a, 266);
    lorr_cpu_str("R0", "( R1 + 7)");
    assert(R[0] == 266);

    add_cpu_str("R0", "R1");
    set_data_from_us_address(0x20d, 810);
    lorr_cpu_str("R0", "(AC)");
    assert(R[0] == 810);


    /* test stoa_cpu_str */
    lodi_cpu_str("R1", "89");
    stoa_cpu_str("R1", "0x67e");
    assert(get_mem_data_from_us_address(0x67e) == 89);

    lodi_cpu_str("BP", "0x9f");
    stoa_cpu_str("BP", "0xa");
    assert(get_mem_data_from_us_address(0xa) == 0x9f);

    /* test stor_cpu_str */
    lodi_cpu_str("R1", "260");
    stor_cpu_str("R1", "(0x89a)");
    assert(get_mem_data_from_us_address(0x89a) == 260);

    lodi_cpu_str("R1", "789");
    stor_cpu_str("R1", "(R1 - 4)");
    assert(get_mem_data_from_us_address(785) == 789);

    /* test stoi_cpu_str */
    stoi_cpu_str("0b1010101", "0x109");
    assert(get_mem_data_from_us_address(0x109) == 0b1010101);

    stoi_cpu_str("8743", "0x290");
    assert(get_mem_data_from_us_address(0x290) == 8743);

    lodi_cpu_str("SP", "0x200");
    lodi_cpu_str("R0", "0x102");

    stoi_cpu_str("0x567", "(SP)");
    assert(get_mem_data_from_us_address(0x200) == 0x567);

    stoi_cpu_str("0x90b", "(SP - 4)");
    assert(get_mem_data_from_us_address(0x1fc) == 0x90b);

    add_cpu_str("R0", "R0");
    stoi_cpu_str("0xab9", "(2+     AC)");
    assert(get_mem_data_from_us_address(0x206) == 0xab9);


    /* test display and display_mem */
    display_cpu();
    display_mem("0x10", "0x14");

    /* test load_code_to_mem */
    load_code_to_mem("../test0.txt");
    display_mem("0x10", "0x14");


    /*** test helper methods ***/
    /* test get_Reg */
    initialize_cpu();
    for (int i = 0; i < 4; i++) assert(get_Reg(i) == 0);
    assert(get_Reg(4) == 0);        // AC
    assert(get_Reg(5) == 0x100);    // SP
    assert(get_Reg(6) == 0x100);    // BP
    assert(get_Reg(7) == 0x10);     // ProC

    /* test para_address_to_IV */
    // invalid
    assert(para_address_to_IV("()") == 0);
    assert(para_address_to_IV("(R4)") == 0);
    assert(para_address_to_IV("(90))") == 0);
    assert(para_address_to_IV("8)") == 0);
    assert(para_address_to_IV("SP") == 0);

    // valid
    assert(para_address_to_IV("(0x89)") == 1);
    assert(IV == 0x89);

    lodi_cpu_str("SP", "0x100");
    assert(para_address_to_IV("(SP + 2)") == 1);
    assert(IV == 0x102);

    lodi_cpu_str("R2", "0x12a");
    assert(para_address_to_IV("(4 +    R2      )") == 1);
    assert(IV == 0x12e);

    lodi_cpu_str("BP", "0x120");
    assert(para_address_to_IV("(-0x2   + BP)") == 1);
    assert(IV == 0x11e);

    lodi_cpu_str("R0", "0x123");
    assert(para_address_to_IV("(     R0     -    0b11 )") == 1);
    assert(IV == 0x120);

    lodi_cpu_str("R0", "0x123");
    lodi_cpu_str("R1", "0x4");
    assert(para_address_to_IV("(    R0     +   R1 )") == 1);
    assert(IV == 0x127);






    return 0;
}