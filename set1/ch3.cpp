/**
 *  Single-byte XOR cipher
 *  Retrieve original message from provided cipher (result of encryption) and
 *  knowing that the message has been encrypted by XORing with
 *  single-character key.
 *
 *  Created: 15. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "basicFunctions.h"

using namespace std;

int main()
{
    //  HEX-encoded cypher
    string  b1 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    //  Convert HEX string to ASCII string
    string b1ASCII = HexstrToASCIIstr(b1);

    //  Loop through all 128 possible hex characters in an attempt to brute-force
    //  decription with all possible single-char keys
    for (int i = 0; i < 127; i++)
    {
        //  Generate string key used for decryption through XORing
        string key(b1ASCII);
        for (int j = 0; j < key.length(); j++)
            key[j] = i;

        //  Perform Fixed XOR operation on ASCII strings
        string ret = FixedASCIIXOR(b1ASCII, key);

        //  Evaluate returned string
        //  Discard all strings which contain special & control characters
        if (validASCIIString(ret))
            cout <<"Key: "<< key<<", \tResult: " << ret << endl;
    }


    return 0;
}
