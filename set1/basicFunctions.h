/**
 *    Basic functions implemented through Set 1 of crypto challenges
 *
 *    Created: 14. Oct 2017.
 *    Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <cstdint>

using namespace std;

const string charSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 *  Convert input ASCII string into a base64 string
 *  @param arg Input ASCII string
 *  @return Corresponding Base64 string
 */
string ASCIItoBase64(string const &arg)
{
    string retVal;
    uint32_t b64Len = 0, b64Pad = 0;

    //  Calculate length of output b64 string and 0 padding
    if ((arg.length() % 3) != 0) {
        b64Pad = 3 - (arg.length() % 3);
        b64Len = (1+arg.length()/3)*4 - b64Pad;
    } else {
        b64Pad = 0;
        b64Len = (arg.length()/3)*4 - b64Pad;
    }

    //  Allocate memory for output string
    retVal.resize(b64Len + b64Pad, 0);

    //  Process input string by taking 3 chars at the time, combine them into a
    //  single decimal number
    for (uint32_t i = 0; i < arg.length(); i += 3)
    {
        uint32_t chunk24bit = 0;

        //  Accumulate 3 (or max avail. less than 3) bytes in a row
        for (uint32_t j = 0; (j < 3) && ((i+j) < arg.length()); j++)
            chunk24bit |= ((uint32_t)arg[j+i]<<((2-j)*8));

        //  Split accumulated 24-bit chunk in 6-bit, base64 signs
        for (uint32_t j = 3; (j >= 0) && ((i/3)*4 + (3-j)) < b64Len; j--)
            retVal[(i/3)*4 + (3-j)] = charSet[(chunk24bit >> (6*j)) & 0x3F];
    }

    for (int8_t j = 0; j < b64Pad; j++)
        retVal += "=";

    return retVal;
}

/**
 *  Provides mapping of hex characters to their integer value
 *  Example: '0'->0, '9'->9, 'B'->11, 'f'->15
 */
uint8_t HexCharToInt (int8_t const &arg)
{
    //  If (input - 65) is less than zero, then input must be digit, in ASCII table
    //  digits span from 48('0') to 57('9'). Else it's a char so we convert it to
    //  lower case and subtract 97('a'). But since hex 'a' is 10 we add 10 to
    //  returned value, ergo -87.
    if ((arg - 65) < 0)
        return (arg - 48);
    else
        return (tolower(arg)-87);
}

/**
 *  Provides mapping of integer values to their lower case hex characters
 *  Example: 0->'0', 9->'9', 11->'b', 15->'f'
 */
int8_t IntToHexChar (uint8_t const &arg)
{
    if (arg < 10)
        return (arg + 48);
    else
        return (arg + 87);
}

/**
 *  Convert input HEX string into a base64 string
 *  @param arg Input HEX string
 *  @return Corresponding Base64 string
 */
string HextoBase64(string const &arg)
{
    string retVal;
    uint32_t b64Len = 0, b64Pad = 0;

    //  HEX input has to have even size
    if ((arg.length() % 2) != 0)
        return "ERROR";

    //  Calculate length of output b64 string and 0 padding
    if ((arg.length() % 3) != 0) {
        b64Pad = 3 - (arg.length()/2 % 3);
        b64Len = (1+arg.length()/6)*4 - b64Pad;
    } else {
        b64Pad = 0;
        b64Len = (arg.length()/6)*4 - b64Pad;
    }

    //  Allocate memory for output string
    retVal.resize(b64Len + b64Pad, 0);

    //  Process input string by taking 3 chars at the time, combine them into a
    //  single decimal number
    for (uint32_t i = 0; i < arg.length(); i += 6)
    {
        uint32_t chunk24bit = 0;

        //  Accumulate 6 (or max avail. less than 6) hex digits(3 bytes) in a row
        for (uint32_t j = 0; (j < 6) && ((i+j) < arg.length()); j++)
            chunk24bit |= ((uint32_t)HexCharToInt(arg[j+i])<<((5-j)*4));

        //  Split accumulated 24-bit chunk in 6-bit, base64 signs
        for (uint32_t j = 3; (j >= 0) && ((i/6)*4 + (3-j)) < b64Len; j--)
            retVal[(i/6)*4 + (3-j)] = charSet[(chunk24bit >> (6*j)) & 0x3F];
    }

    for (int8_t j = 0; j < b64Pad; j++)
        retVal += "=";

    return retVal;
}

/**
 *  Perform XOR on two HEX encoded strings
 *  @param arg1 First HEX-encoded string
 *  @param arg2 Second HEX-encoded string
 *  @return HEX-encoded result of XOR operator on two inputs
 */
string FixedHEXXOR(string const &arg1,string const &arg2)
{
    string retVal;
    retVal.resize(arg1.length(), 0);
    if (arg1.length() != arg2.length())
        return "ERROR";

    for (uint32_t i = 0; i < arg1.length(); i++)
    {
        uint8_t res = HexCharToInt(arg1[i]) ^ HexCharToInt(arg2[i]);
        retVal[i] = IntToHexChar(res);
    }

    return retVal;
}

/**
 *  Perform XOR on two ASCII strings
 *  @param arg1 First ASCII string
 *  @param arg2 Second ASCII string
 *  @return ASCII-encoded result of XOR operator on two inputs
 */
string FixedASCIIXOR(string const &arg1,string const &arg2)
{
    string retVal;
    retVal.resize(arg1.length(), 0);

    if (arg1.length() != arg2.length())
        return "ERROR";

    for (uint32_t i = 0; i < arg1.length(); i++)
        retVal[i] = arg1[i] ^ arg2[i];

    return retVal;
}

/**
 *  Convert HEX-encoded string into its ASCII representation
 *  @param arg HEX-encoded string to decode
 *  @return ASCII representation of input string
 */
string HexstrToASCIIstr(string const &arg)
{
    string retVal;
    uint32_t i = 0;

    retVal.resize(arg.length()/2, 0);

    for (i; i < arg.length(); i+=2)
    {
        retVal[i/2] = ((HexCharToInt(arg[i])<<4) | HexCharToInt(arg[i+1]));
    }

    return retVal;
}

/**
 *  Checks if input string consists of valid characters. Use bool selectors to
 *  choose valid groups of characters
 *  @param lc Allows for lower-case letters in string
 *  @param uc Allows for upper-case letters in string
 *  @param num Allows for numbers in string
 *  @param sent Allows for sentence chars in string (!',.:;)
 *  @param comm Allows for characters used in common slang #$&+-
 *  @param spec Allows for special chars in string (not in all the other rules)
 *  @param cont Allows for control chars in string (ASCII < 32)
 *  @return True if string passed all requirements, false if it didn't
 */
bool validASCIIString(string const &arg, bool lc = true, bool uc = true,
                      bool num = true, bool sent = true, bool comm = true,
                      bool spec = false, bool cont = false)
{
    bool valid = true;

    for (int i = 0; (i < arg.length()) && valid; i++)
    {
        //  Check if it's upper case and we want upper case
        if ((arg[i] > 64) && (arg[i] < 91))
            valid &= uc;
        //  Check if it's lower case and we want lower case
        else if ((arg[i] > 96) && (arg[i] < 123))
            valid &= lc;
        //  Check if it's number and we want number
        else if ((arg[i] > 47) && (arg[i] < 58))
            valid &= num;
        //  Check if it's sentence punctuation (!'",.:;) ()/
        else if ((arg[i] == 32) || (arg[i] == 33) || (arg[i] == 34) ||
                 (arg[i] == 39) || (arg[i] == 44) || (arg[i] == 46) ||
                 (arg[i] == 58) || (arg[i] == 59) || (arg[i] == 63))
            valid &= sent;
        else if (((arg[i] > 34) && (arg[i] < 44)) || (arg[i] == 42)
                 || (arg[i] == 43) || (arg[i] == 45) || (arg[i] == 47) || (arg[i] == 10) || (arg[i] == 13))
            valid &=comm;
        else if ((arg[i] < 32) || (arg[i] == 127))
            valid &= cont;
        else
            valid &= spec;
    }

    return valid;
}
