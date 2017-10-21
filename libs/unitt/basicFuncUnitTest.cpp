#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../basicFunctions.h"
#include <string>

#define TC_ASCII    0
#define TC_BASE64   1
#define TC_HEX      2


const std::string testCases[][4] =
{
    {
"Convert from plain text to bin binary",
"Q29udmVydCBmcm9tIHBsYWluIHRleHQgdG8gYmluIGJpbmFyeQ==",
"436f6e766572742066726f6d20706c61696e207465787420746f2062696e2062696e617279"
    },
    {
"The quick brown fox jumps over 13 lazy dogs.",
"VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIDEzIGxhenkgZG9ncy4=",
"54686520717569636b2062726f776e20666f78206a756d7073206f766572203133206c617a7920646f67732e"
    },
    {
"Convert from plain text to hex hexadecimal",
"Q29udmVydCBmcm9tIHBsYWluIHRleHQgdG8gaGV4IGhleGFkZWNpbWFs",
"436f6e766572742066726f6d20706c61696e207465787420746f206865782068657861646563696d616c"
    },
    {
"Delectus velit omnis eum. Sint porro dolorem distinctio quae soluta quibusdam. Aut eligendi temporibus soluta molestiae.",
"RGVsZWN0dXMgdmVsaXQgb21uaXMgZXVtLiBTaW50IHBvcnJvIGRvbG9yZW0gZGlzdGluY3RpbyBxdWFlIHNvbHV0YSBxdWlidXNkYW0uIEF1dCBlbGlnZW5kaSB0ZW1wb3JpYnVzIHNvbHV0YSBtb2xlc3RpYWUu",
"44656c65637475732076656c6974206f6d6e69732065756d2e2053696e7420706f72726f20646f6c6f72656d2064697374696e6374696f207175616520736f6c7574612071756962757364616d2e2041757420656c6967656e64692074656d706f726962757320736f6c757461206d6f6c6573746961652e"
    },
    {
"Iste hic commodi quia",
"SXN0ZSBoaWMgY29tbW9kaSBxdWlh",
"497374652068696320636f6d6d6f64692071756961"
    },
    {
"Aperiam voluptatem sint voluptas laudantium quasi atque.",
"QXBlcmlhbSB2b2x1cHRhdGVtIHNpbnQgdm9sdXB0YXMgbGF1ZGFudGl1bSBxdWFzaSBhdHF1ZS4=",
"4170657269616d20766f6c7570746174656d2073696e7420766f6c7570746173206c617564616e7469756d2071756173692061747175652e"
    },
    {
"Deserunt distinctio minus quaerat ut est. Culpa expedita error occaecati.",
"RGVzZXJ1bnQgZGlzdGluY3RpbyBtaW51cyBxdWFlcmF0IHV0IGVzdC4gQ3VscGEgZXhwZWRpdGEgZXJyb3Igb2NjYWVjYXRpLg==",
"4465736572756e742064697374696e6374696f206d696e75732071756165726174207574206573742e2043756c7061206578706564697461206572726f72206f63636165636174692e"
    },
    {
"Et cum at fugiat in nemo molestias vitae sed.",
"RXQgY3VtIGF0IGZ1Z2lhdCBpbiBuZW1vIG1vbGVzdGlhcyB2aXRhZSBzZWQu",
"45742063756d2061742066756769617420696e206e656d6f206d6f6c657374696173207669746165207365642e"
    },
    {
"Incidunt dolores iste totam sit earum a qui.",
"SW5jaWR1bnQgZG9sb3JlcyBpc3RlIHRvdGFtIHNpdCBlYXJ1bSBhIHF1aS4=",
"496e636964756e7420646f6c6f726573206973746520746f74616d2073697420656172756d2061207175692e"
    },
    {
"Qui perferendis eaque itaque qui quis.",
"UXVpIHBlcmZlcmVuZGlzIGVhcXVlIGl0YXF1ZSBxdWkgcXVpcy4=",
"51756920706572666572656e646973206561717565206974617175652071756920717569732e"
    }
};



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
