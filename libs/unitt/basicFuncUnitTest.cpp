#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <string>
#include "testCases.h"

#include "../mycrypto-basic.h"



/**
 *  Unit tests for conversion functions in basicFunctions.h file
 */

TEST_CASE( "Test HEX to Base64", "[base64Str]" ) {
    for (uint8_t i = 0; i < 10; i++)
        REQUIRE( HexToBase64(testCases[i][TC_HEX]) == testCases[i][TC_BASE64] );
}

TEST_CASE( "Test Base64 to HEX", "[HEXstr]" ) {
    for (uint8_t i = 0; i < 10; i++)
        REQUIRE( Base64ToHex(testCases[i][TC_BASE64]) == testCases[i][TC_HEX] );
}

TEST_CASE( "Test ASCII to HEX", "[HEXstr]" ) {
    for (uint8_t i = 0; i < 10; i++)
        REQUIRE( ASCIIToHex(testCases[i][TC_ASCII]) == testCases[i][TC_HEX] );
}

TEST_CASE( "Test HEX to ASCII", "[ASCIIstr]" ) {
    for (uint8_t i = 0; i < 10; i++)
        REQUIRE( HexToASCII(testCases[i][TC_HEX]) == testCases[i][TC_ASCII] );
}

TEST_CASE( "Test ASCII to Base64", "[base64Str]" ) {
    for (uint8_t i = 0; i < 10; i++)
        REQUIRE( ASCIIToBase64(testCases[i][TC_ASCII]) == testCases[i][TC_BASE64] );
}

/**
 *  Test Repeating-key XOR in various encodings (this also test Fixed-key XOR
 *  since repeating-key XOR only expands the key and calls fixed-key XOR)
 */

 TEST_CASE( "Test repeated-key XOR", "[repkeyXOR]" ) {
    //  Compute RepKeyXOR in ASCII, then convert it to HEX. Compare it to a
    //  native conversion of the same string in HEX
    REQUIRE( ASCIIToHex(ASCIIRepeatKeyXOR(testCases[3][TC_ASCII], testCases[4][TC_ASCII])) ==
             HexRepeatKeyXOR(testCases[3][TC_HEX], testCases[4][TC_HEX]) );

    REQUIRE( ASCIIRepeatKeyXOR(testCases[1][TC_ASCII], testCases[4][TC_ASCII]) ==
             HexToASCII(HexRepeatKeyXOR(testCases[1][TC_HEX], testCases[4][TC_HEX])) );

    REQUIRE( ASCIIRepeatKeyXOR(testCases[8][TC_ASCII], testCases[4][TC_ASCII]) ==
             HexToASCII(HexRepeatKeyXOR(testCases[8][TC_HEX], testCases[4][TC_HEX])) );

    //  Compute RepKeyXOR in ASCII, then convert it to HEX. Compare it to a
    //  native conversion of the same string in HEX
    REQUIRE( ASCIIToHex(ASCIIRepeatKeyXOR(testCases[3][TC_ASCII], testCases[2][TC_ASCII])) ==
             HexRepeatKeyXOR(testCases[3][TC_HEX], testCases[2][TC_HEX]) );

    REQUIRE( ASCIIRepeatKeyXOR(testCases[3][TC_ASCII], testCases[1][TC_ASCII]) ==
             HexToASCII(HexRepeatKeyXOR(Base64ToHex(testCases[3][TC_BASE64]),
                                        Base64ToHex(testCases[1][TC_BASE64]))) );
}
