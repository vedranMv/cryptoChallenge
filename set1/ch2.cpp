/**
 *  Fixed XOR on two equal length hex-encoded strings
 *  Write a function that takes two equal-length buffers and produces their
 *  XOR combination.
 *
 *  Created: 14. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "../libs/mycrypto-basic.h"

using namespace std;

int main()
{
    //  Input strings
    string  b1 = "1c0111001f010100061a024b53535009181c",
            b2 = "686974207468652062756c6c277320657965";

    //  Result of fixed XOR between strings
    string ret = HexFixedXOR(b1, b2);
    cout << ret << endl;

    return 0;
}
