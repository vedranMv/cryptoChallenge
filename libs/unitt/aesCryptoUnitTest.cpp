#define CATCH_CONFIG_MAIN

#include <string>

#include "catch.hpp"

#include "testCases.h"
#include "../mycrypto-basic.h"
#include "../mycrypto-aes.h"


/**
 *  Test encryption/decryption with ASCII data
 */

TEST_CASE( "AES CDC encryption/decryption on ASCII, 128b block", "[asciiStr]" ) {

    string  iv (16, 0x12),
            key("WogThi85$#22ehwb");

    for (uint8_t i = 0; i < 10; i++)
        REQUIRE( AESCBCDecryptText(key, iv, AESCBCEncryptText(key, iv, testCases[i][TC_ASCII])) == testCases[i][TC_ASCII]);

}


