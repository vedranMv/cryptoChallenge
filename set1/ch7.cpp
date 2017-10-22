/**
 *  AES-128-ECB decryption through OpenSSL
 *
 *
 *  Created: 21. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "../libs/mycrypto-basic.h"
#include "../libs/mycrypto-aes.h"

using namespace std;


int main()
{
    //  Open external resource file
    fstream file;
    file.open("ch7_res1.txt");
    //  Holds extracted line from file
    string b1, txtStr;

    //  Load file into a single string
    while (getline(file, b1))
        txtStr += b1;

    //  Close file, we're done
    file.close();

    InitAES128EBC();

    string  ciphertext = HexToASCII(Base64ToHex(txtStr)).c_str(), rtext;
    string  key = "YELLOW SUBMARINE",
            iv(17,0x48);


    rtext = AESEBCDecryptText(key, iv, ciphertext);

    cout<<"Decrypting, check output file decrypted.out";

    //  Open external resource file
    file.open("ch7_decrypted.out", ios::out);
    file << rtext;
    file.close();

    return 0;
}


