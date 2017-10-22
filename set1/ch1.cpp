/**
 *  Hex to Base64 encoding
 *  Given a hex-encoded string, produce its base64 equivalent
 *
 *  Created: 14. Oct 2017.
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
    string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    //  Given output (to evaluate result of algorithm)
    string output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    cout<<HexToBase64(input)<<endl;
    return 0;
}
