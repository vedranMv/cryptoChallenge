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
 *  Mapping of Base64 character set to integer numbers they represent (0-63)
 *  @param arg Input digit/char of Base64 string
 *  @return Integer value in range 0-63 corresponding to input digit
 */
uint8_t B64CharToInt(uint8_t arg)
{
    //  Upper case letters map to 0-25
    if ((arg > 64) && (arg < 91))
        return (arg - 65);
    //  Lower case letters map to 26-51
    if ((arg > 96) && (arg < 123))
        return (arg - 97 + 26);
    //  Numbers map to 52-61
    if ((arg > 47) && (arg < 58))
        return (arg - 48 + 52);
    //  '+' is 62
    if (arg == '+')
        return 62;
    //  '/' is 63
    if (arg == '/')
        return 63;
}

/**
 *  Convert input ASCII string into a Base64 string
 *  @param arg Input ASCII string
 *  @return Corresponding Base64 string
 */
string ASCIItoBase64(string const &arg)
{
    string retVal;
    uint32_t b64Len = 0, b64Pad = 0;

    //  Calculate length of output b64 string and 0 padding. If input string has
    //  length dividable by 3 then no padding is needed, if not, padding is
    //  equal to difference between first multiple of 3 larger than string's len
    //  and string's len
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
 *  Convert input HEX string into a Base64 string
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
 *  Convert input Base64 string into a HEX string
 *  @param arg Input Base64 string
 *  @return Corresponding HEX string
 */
string Base64ToHex(string const &arg)
{
    string retVal;
    uint32_t b64Len = 0, b64Pad = 0;

    //  Find length and padding of b64 input
    b64Len = arg.length();
    for (uint32_t i = (b64Len-1); 1==1 ; i--)
        if (arg[i] == '=')
            b64Pad++;
        else
            break;

    //  Set the length on data part of Base64
    b64Len -= b64Pad;

    //  Length of HEX is simply length data part of Base64*6/4 (since B64 takes
    //  6 bits to encode one sign and HEX only 4) reduced by the number of
    //  padded zeros to B64 string)
    //  Allocate memory for output string
    retVal.resize(b64Len*6/4-b64Pad*2, 0);

    //  Process input string by taking 4 chars at the time, combine them into a
    //  single decimal number of 24bit that can be split in 4bit HEX chunks
    for (uint32_t i = 0; i < b64Len; i += 4)
    {
        uint32_t chunk24bit = 0;

        //  Accumulate 4 (or max avail. less than 4) b64 digits(3 bytes) in a row
        for (uint32_t j = 0; (j < 4) && ((i+j) < b64Len); j++)
            chunk24bit |= ((uint32_t)B64CharToInt(arg[j+i]))<<((3-j)*6);

        //  Split accumulated 24-bit chunk in six 4-bit chunks, HEX digits
        for (uint32_t j = 5; (j >= 0) && ((i/4)*6 + (5-j)) < retVal.length(); j--)
            retVal[(i/4)*6 + (5-j)] = IntToHexChar((chunk24bit >> (4*j)) & 0x0F);
    }

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
 *  Convert input ASCII string to hex string. Additionally, if length is supplied
 *  function will repeat input string for as many time needed to reach the length.
 *  Example: if arg="okl" and length=7 function returns "okloklo"
 *  @param arg ASCII string to convert to HEX
 *  @param length (optional) length of output string
 */
string ASCIIstrToHexstr(string const &arg, uint32_t length = 0)
{
    string retVal;

    if (length == 0)
        length = arg.length()*2;

    retVal.resize(length, 0);

    for (int i = 0; i <length; i+=2)
    {
//        cout<< ((arg[((i/2)%arg.length())]>>4) & 0x0F) << " : "<<(arg[((i/2)%arg.length())] & 0x0F)<<endl;
        retVal[i] = IntToHexChar((arg[((i/2)%arg.length())]>>4) & 0x0F);
        retVal[i+1] = IntToHexChar(arg[((i/2)%arg.length())] & 0x0F);
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


string ASCIIRepeatKeyXOR(string const &text, string const &key)
{
    //  Convert text to hex
    string txtHex = ASCIIstrToHexstr(text);
    //  Convert key to hex and repeat it as many times as need to have the same
    //  length as text
    string keyHex = ASCIIstrToHexstr(key, txtHex.length());

    return FixedHEXXOR(txtHex, keyHex);
}
