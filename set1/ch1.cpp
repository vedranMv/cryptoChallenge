/**
 *    Title
 *    Description
 *
 *    Created: 14. Oct 2017.
 *    Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <string>
#include "basicFunctions.h"

using namespace std;


int main()
{
    string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    string output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

    cout<<ASCIItoBase64("sdlhldhlashfladhjljlsdfhjlhflkfhsdghldhskldghljsdhfsljvnjknvlibfifzrlwhgf+f5+48948641/&%$%&/()(/&%$")<<endl;
    cout<<HextoBase64(input)<<endl;
    return 0;
}
