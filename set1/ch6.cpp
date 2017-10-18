/**
 *  Break repeating-key XOR
 *  Given a text file whose content has been base64'd after encryption with
 *  repeating-key XOR, break the encryption, decrypt content of file.
 *
 *  Created: 18. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "basicFunctions.h"

using namespace std;

int main()
{

    //  Test newly-implemented Base64ToHex function
    string b1 = ASCIIstrToHexstr("May string in ASCII41698/4*7*/7d*/s7wr*45tzjz6(/&%&$%#%#");
    cout<<b1<<"("<<b1.length()<<")"<<endl;

    string b2 = HextoBase64(b1);
    cout<<b2<<endl;

    b2 = Base64ToHex(b2);
    cout<<b2<<endl;

    b2 = HexstrToASCIIstr(b2);
    cout<<b2<<endl;


//    //  Open external resource file
//    fstream file, file1;
//    file.open("ch6_res1.txt");
//    //  Holds extracted line from file
//    string b1;
//
//    while (getline(file, b1))
//    {
//            //  Convert HEX string to ASCII string
//            string b1ASCII = HexstrToASCIIstr(b1);
//            //  Generate string key used for decryption through XORing
//            string key(b1ASCII);
//
//        for (int i = 0; i < 127; i++)
//        {
//            for (int j = 0; j < key.length(); j++)
//                key[j] = i;
//
//            string ret = FixedASCIIXOR(b1ASCII, key);
//
//            //  Evaluate returned string
//            //  Discard all strings which contain special characters
//            if (validASCIIString(ret,true,true,true,true,true,false,false))
//                cout <<"Key: "<< key<<", \tResult: " << ret;
//        }
//    }
//    file.close();
    return 0;
}
