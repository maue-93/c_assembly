//
// Created by Eliso Morazara on 11/8/23.
//

#include "assert.h"

#include "helper_methods.h"

int main (){

    /*** test helper methods ***/
    /* test bitAt */
    assert(bitAt(0, 0) == 0);
    assert(bitAt(1, 0) == 1);
    assert(bitAt(0, 2) == 0);
    assert(bitAt(0b100, 2) == 1);
    assert(bitAt(0b000001000000, 6) == 1);
    assert(bitAt(0b1000000000000000, 15) == 1);
    assert(bitAt(0b1111111111111111, 15) == 1);
    // should always return 0 if pos > 15
    assert(bitAt(0b1111111111111111, 16) == 0);

    /* test changeBitAt */
    unsigned short a = 0b00;
    assert(changeBitAt(a, 0) == 0b1);
    assert(changeBitAt(a, 1) == 0b10);
    assert(changeBitAt(a, 2) == 0b100);
    a = 0b0110011101100111;
    assert(changeBitAt(a, 0) == 0b0110011101100110);
    assert(changeBitAt(a, 7) == 0b0110011111100111);
    assert(changeBitAt(a, 10) == 0b0110001101100111);
    assert(changeBitAt(a, 12) == 0b0111011101100111);
    assert(changeBitAt(a, 9) == 0b0110010101100111);

    /* test add_uns */
    assert(add_uns(0, 0) == 0);
    assert(add_uns(1, 1) == 2);
    assert(add_uns(67, 1000) == 1067);
    assert(add_uns(23939, 9837) == 33776);
    // overflow
    assert(add_uns(32768, 49152) == 16384);

    /* test negation */
    assert(negation(0b1111111111111111) == 1);
    assert(negation(0) == 0);
    assert(negation(0b0101010101010101) == 0b1010101010101011);
    assert(negation(0b1010101010101010) == 0b0101010101010110);

    /* test regStrToInt */
    assert(regStrToInt("R0") == 0);
    assert(regStrToInt("R1") == 1);
    assert(regStrToInt("R2") == 2);
    assert(regStrToInt("R3") == 3);
    assert(regStrToInt("AC") == 4);
    assert(regStrToInt("SP") == 5);
    assert(regStrToInt("BP") == 6);
    assert(regStrToInt("PC") == 7);
    assert(regStrToInt("PCU") == -1);

    /* test valid_dec_val */
    assert(valid_dec_val("") == 0);
    assert(valid_dec_val("-") == 0);
    assert(valid_dec_val("0") == 1);
    assert(valid_dec_val("1") == 1);
    assert(valid_dec_val("123445678910") == 12);
    assert(valid_dec_val("-65435") == 6);
    assert(valid_dec_val(" 123") == 0);
    assert(valid_dec_val("0x123") == 0);
    assert(valid_dec_val("12u78") == 0);
    assert(valid_dec_val("12 3") == 0);

    /* test valid_hex_val */
    assert(valid_hex_val("") == 0);
    assert(valid_hex_val("-") == 0);
    assert(valid_hex_val("0x") == 0);
    assert(valid_hex_val("0X") == 0);
    assert(valid_hex_val("-0x") == 0);
    assert(valid_hex_val("-0X") == 0);
    assert(valid_hex_val(" abdf") == 0);
    assert(valid_hex_val("0xabdf") == 6);
    assert(valid_hex_val("0Xabdf") == 6);
    assert(valid_hex_val("-0x234df") == 8);
    assert(valid_hex_val("1") == 0);
    assert(valid_hex_val("0X1") == 3);
    assert(valid_hex_val("0xaBD12E") == 8);
    assert(valid_hex_val("-0X13DEb9") == 9);
    assert(valid_hex_val("0x8bgA") == 0);

    /* test valid_bin_val */
    assert(valid_bin_val("") == 0);
    assert(valid_bin_val("1") == 0);
    assert(valid_bin_val("0b") == 0);
    assert(valid_bin_val("0B") == 0);
    assert(valid_bin_val("-0b") == 0);
    assert(valid_bin_val("-0B") == 0);
    assert(valid_bin_val("-0b1") == 4);
    assert(valid_bin_val("0b100100101") == 11);
    assert(valid_bin_val("-0b100100101") == 12);
    assert(valid_bin_val("0B100100101") == 11);
    assert(valid_bin_val("-0B100100101") == 12);

    /* test dec_str_val_to_us_IV */
    assert(dec_str_val_to_us_IV("") == 0);
    assert(dec_str_val_to_us_IV("0") == 1);
    assert(IV == 0);
    assert(dec_str_val_to_us_IV("65343") == 1);
    assert(IV == 65343);
    assert(dec_str_val_to_us_IV("-00000000065343") == 1);
    assert(IV == (unsigned short)(~65343 + 1));
    assert(dec_str_val_to_us_IV("123343") == 0);
    assert(dec_str_val_to_us_IV("0x8") == 0);
    assert(dec_str_val_to_us_IV("0b01") == 0);
    assert(dec_str_val_to_us_IV("-o08") == 0);
    assert(dec_str_val_to_us_IV("-90") == 1);
    assert(IV == (unsigned short)(~90 + 1));
    assert(dec_str_val_to_us_IV("-0") == 1);
    assert(IV == 0);
    assert(dec_str_val_to_us_IV("-000000098") == 1);
    assert(IV == (unsigned short) (~98 + 1));

    /* test hex_str_val_to_us_IV */
    assert(hex_str_val_to_us_IV("") == 0);
    assert(hex_str_val_to_us_IV("12") == 0);
    assert(hex_str_val_to_us_IV("0x12") == 1);
    assert(IV == 0x12);
    assert(hex_str_val_to_us_IV("0X1A") == 1);
    assert(IV == 0x1a);
    assert(hex_str_val_to_us_IV("-0x90b") == 1);
    assert(IV == (unsigned short)(~0x90b + 1));
    assert(hex_str_val_to_us_IV("0b1") == 0);
    assert(hex_str_val_to_us_IV("0x7f000") == 0);

    /* test bin_str_val_to_us_IV */
    assert(bin_str_val_to_us_IV("") == 0);
    assert(bin_str_val_to_us_IV("0101") == 0);
    assert(bin_str_val_to_us_IV("0b102") == 0);
    assert(bin_str_val_to_us_IV("0b1011") == 1);
    assert(IV == 0b1011);
    assert(bin_str_val_to_us_IV("-0b1011") == 1);
    assert(IV == (unsigned short)(~0b1011 + 1));
    assert(bin_str_val_to_us_IV("0B00000001") == 1);
    assert(IV == 1);
    assert(bin_str_val_to_us_IV("0B11111111111111110") == 0);

    /* test str_val_to_us_IV */
    assert(str_val_to_us_IV("") == 0);
    assert(str_val_to_us_IV("0") == 1);
    assert(IV == 0);
    assert(str_val_to_us_IV("65343") == 1);
    assert(IV == 65343);
    assert(str_val_to_us_IV("-00000000065343") == 1);
    assert(IV == (unsigned short)(~65343 + 1));
    assert(str_val_to_us_IV("123343") == 0);
    assert(str_val_to_us_IV("0x8") == 1);
    assert(IV == 0x8);
    assert(str_val_to_us_IV("0b01") == 1);
    assert(IV == 1);
    assert(str_val_to_us_IV("-o08") == 0);
    assert(str_val_to_us_IV("-90") == 1);
    assert(IV == (unsigned short)(~90 + 1));
    assert(str_val_to_us_IV("-0") == 1);
    assert(IV == 0);
    assert(str_val_to_us_IV("-000000098") == 1);
    assert(IV == (unsigned short) (~98 + 1));

    assert(str_val_to_us_IV("12") == 1);
    assert(IV == 12);
    assert(str_val_to_us_IV("0x12") == 1);
    assert(IV == 0x12);
    assert(str_val_to_us_IV("0X1A") == 1);
    assert(IV == 0x1a);
    assert(str_val_to_us_IV("-0x90b") == 1);
    assert(IV == (unsigned short)(~0x90b + 1));
    assert(str_val_to_us_IV("0b1") == 1);
    assert(IV == 1);
    assert(str_val_to_us_IV("0x7f000") == 0);

    assert(str_val_to_us_IV("0101") == 1);
    assert(IV == 101);
    assert(str_val_to_us_IV("0b102") == 0);
    assert(str_val_to_us_IV("0b1011") == 1);
    assert(IV == 0b1011);
    assert(str_val_to_us_IV("-0b1011") == 1);
    assert(IV == (unsigned short)(~0b1011 + 1));
    assert(str_val_to_us_IV("0B00000001") == 1);
    assert(IV == 1);
    assert(str_val_to_us_IV("0B11111111111111110") == 0);


    return 0;
}
