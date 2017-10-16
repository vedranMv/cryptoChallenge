/**
 *    Title
 *    Description
 *
 *    Created: 14. Oct 2017.
 *    Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "basicFunctions.h"

using namespace std;

int main()
{
    string  b1 = "1c0111001f010100061a024b53535009181c",
            b2 = "686974207468652062756c6c277320657965";

    string ret = FixedXOR(b1, b2);
    cout << ret << endl;

    /*  Verification
    ret = FixedXOR(b2, ret);
    cout << ret << endl;
    */
    return 0;
}
