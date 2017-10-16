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
    string  b1 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";


    for (int i = 0; i < 127; i++)
    {
        //  Convert HEX string to ASCII string
        string b1ASCII = HexstrToASCIIstr(b1);

        //  Generate string key used for decryption through XORing
        string key(b1ASCII);
        for (int j = 0; j < key.length(); j++)
            key[j] = i;

        string ret = FixedASCIIXOR(b1ASCII, key);

        //  Evaluate returned string
        //  Discard all strings which contain special characters
        bool failed = false;
        for (int j = 0; (j < ret.length()) && !failed; j++)
            if ((ret[j] < 31) || (ret[j] > 127))
                failed = true;

        if (!failed)
            cout <<"Key: "<< key<<", \tResult: " << ret << endl;
    }


    return 0;
}
