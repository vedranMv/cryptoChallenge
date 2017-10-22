/**
 *  Implement PKCS#7 padding
 *  Given ASCII string, pad it to specified length according to PKCS#7 scheme
 *
 *  Created: 21. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include "../libs/mycrypto-basic.h"

using namespace std;


int main()
{
    //  Given input
    string input = "YELLOW SUBMARINE";
    //  Given output (to evaluate result of algorithm)
    string output = "YELLOW SUBMARINE\x04\x04\x04\x04";

    cout<<(PadString(input, 20, ENC_ASCII) == output)<<endl;
    return 0;
}
