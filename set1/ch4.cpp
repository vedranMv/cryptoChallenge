/**
 *  Detect single-character XOR
 *  From a list of ciphers find which one has been encrypted by XORing with a
 *  single character key.
 *
 *  Created: 16. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "../libs/basicFunctions.h"

using namespace std;

int main()
{
    //  Open external resource file
    fstream file, file1;
    file.open("ch4_res1.txt");
    //  Holds extracted line from file
    string b1;

    while (getline(file, b1))
    {
            //  Convert HEX string to ASCII string
            string b1ASCII = HexToASCII(b1);
            //  Generate string key used for decryption through XORing
            string key(b1ASCII);

        for (int i = 0; i < 127; i++)
        {
            for (int j = 0; j < key.length(); j++)
                key[j] = i;

            string ret = ASCIIFixedXOR(b1ASCII, key);

            //  Evaluate returned string
            //  Discard all strings which contain special characters
            if (validASCIIString(ret,true,true,true,true,true,false,false))
                cout <<"Key: "<< key<<", \tResult: " << ret;
        }
    }
    file.close();
    return 0;
}
