/**
 *  Repeating-key encryption example
 *  Given the input string b1 and and encryption key whose length is smaller
 *  than that of b1, encrypt b1 by performing repeating-key XOR encryption.
 *
 *  Created: 18. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "../libs/basicFunctions.h"

using namespace std;

int main()
{
    //  Message to encrypt and encryption key
    string  b1 = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal",
            key = "ICE";

    string ret = ASCIIToHex(ASCIIRepeatKeyXOR(b1, key));
    cout<<ret<<endl;

    return 0;
}
