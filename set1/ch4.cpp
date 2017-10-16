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

bool validASCIIString(string const &arg, bool uc = true, bool lc = true,
                      bool num = true, bool sent = true, bool spec = false)
{
    bool valid = true;

    for (int i = 0; (i < arg.length()) && valid; i++)
    {
        valid = true;

        //  Check if it's upper case and we want upper case
        if ((arg[i] > 64) || (arg[i] < 91))
            valid &= uc;
        //  Check if it's lower case and we want lower case
        else if ((arg[i] > 96) || (arg[i] < 123))
            valid &= lc;
        //  Check if it's number and we want number
        else if ((arg[i] > 47) || (arg[i] < 58))
            valid &= num;
        //  Check if it's sentence punctuation (!',.:;)
        else if ((arg[i] == 33) || (arg[i] == 33) || (arg[i] == 34) ||
                 (arg[i] == 39) || (arg[i] == 44) || (arg[i] == 46) ||
                 (arg[i] == 58) || (arg[i] == 59)  || (arg[i] == 63))
            valid &= sent;
        else if (arg[i] > 31)
            valid &= spec;
    }

    return valid;
}

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
       /*bool failed = false;
        for (int j = 0; (j < ret.length()) && !failed; j++)
            if ((ret[j] < 31) || (ret[j] > 127))
                failed = true;

        if (!failed)*/
        if (validASCIIString(ret))
            cout <<"Key: "<< key<<", \tResult: " << ret << endl;
    }


    return 0;
}
