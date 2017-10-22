/**
 *  Implement CBC mode
 *  Implement CBC mode by hand by taking the ECB function you wrote earlier,
 *  making it encrypt instead of decrypt (verify this by decrypting whatever you
 *  encrypt to test), and using your XOR function from the previous exercise to
 *  combine them.
 *
 *  Created: 21. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>

#include <iostream>
#include <vector>
#include <fstream>

#include "../libs/mycrypto-basic.h"
#include "../libs/mycrypto-aes.h"

#include <string>


int main()
{
    //  Initialization vector & encryption/decryption key
    string  key = "YELLOW SUBMARINE",
            iv (AES_ECB_BLOCK_SIZE, 0x00);

    //  Split input plaintext into blocks
    string text = "This is my plaintext to encrypt with AES and then try to decrypt it back unchanged.";

    //  Open external resource file
    fstream file;
    file.open("ch10_res1.txt");
    //  Holds extracted line from file
    string b1, txtStr;

    //  Load file into a single string
    while (getline(file, b1))
        txtStr += b1;

    //  Close file, we're done
    file.close();

    //  String from file is base64-encoded, decode it to ASCII (no direct
    //  conversion available at the moment :( )
    txtStr = HexToASCII(Base64ToHex(txtStr));

    //  Initialize openSSL
    InitAES128EBC();

    //  Perform decryption
    string plainText = AESCBCDecryptText(key, iv, txtStr);

    //  Write result to file
    file.open("ch10_decrypted.out", ios::out);
    file<<"Got the following plaintext: \n\t"<<plainText<<endl;
    file.close();
    return 0;
}
