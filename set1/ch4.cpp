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
#include <fstream>
#include "basicFunctions.h"

using namespace std;

bool validSentence(string const &arg)
{
    bool valid = false;

    if ((arg[0] > 64) && (arg[0] < 91))
        valid = true;
    //  Check if it's lower case and we want lower case
    else if ((arg[0] > 96) && (arg[0] < 123))
        valid = true;
}

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
            string b1ASCII = HexstrToASCIIstr(b1);
            //  Generate string key used for decryption through XORing
            string key(b1ASCII);

        for (int i = 0; i < 127; i++)
        {
            for (int j = 0; j < key.length(); j++)
                key[j] = i;

            string ret = FixedASCIIXOR(b1ASCII, key);

            //  Evaluate returned string
            //  Discard all strings which contain special characters
            if (validASCIIString(ret,true,true,true,true,true,false,false))
                //if (validSentence(ret))
                //cout <<"Key: "<< key<<", \tResult: " << ret;
                cout<<ret<<endl;
        }
    }
    file.close();
    return 0;
}
