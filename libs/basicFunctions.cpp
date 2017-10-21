/**
 *    Implementation of basic functions required in set 1 of crypto challenge
 *    Description
 *
 *      TODO: Implement decoding from base64 to ASCII
 *
 *    Created: 20. Oct 2017.
 *    Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <cstdint>
#include <climits>
#include "basicFunctions.h"

//  Base64 character set
const string charSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//------------------------------------------------------------------------------
//      Mapping between characters and their integer values            [PRIVATE]
//      in different bases
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
//      Operations on data of any encoding                              [PUBLIC]
//------------------------------------------------------------------------------
/**
 *  General repeat-key XOR function
 *  Performs XOR between text and key for arbitrary key size. If key length is
 *  shorter than text, it is repeated until the sizes match
 *  @param text Text to encrypt with repeating key
 *  @param key Arbitrary-length key to use for encryption of text variable
 *  @param encod Encoding of text, key & result (one of ENC_* macros)
 *  @return result of XOR operation in the same encoding as input arguments
 */
string RepeatKeyXOR(string const &text, string const &key, uint8_t encod)
{
    switch(encod)
    {
    case ENC_ASCII:
        return ASCIIRepeatKeyXOR(text, key);
    case ENC_BASE64:
        return HexToBase64(HexRepeatKeyXOR(Base64ToHex(text), Base64ToHex(key)));
    case ENC_HEX:
        return HexRepeatKeyXOR(text, key);
    }
}
/**
 *  General fixed-key XOR function
 *  Performs XOR between text and key for key size of the same length as text.
 *  If key length is shorter than text, functions returns "ERROR"
 *  @param text Text to encrypt
 *  @param key Key to use for encryption of text variable
 *  @param encod Encoding of text, key & result (one of ENC_* macros)
 *  @return result of XOR operation in the same encoding as input arguments
 */
string FixedKeyXOR(string const &text, string const &key, uint8_t encod)
{
    switch(encod)
    {
    case ENC_ASCII:
        return ASCIIFixedXOR(text, key);
    case ENC_BASE64:
        return HexToBase64(HexFixedXOR(Base64ToHex(text), Base64ToHex(key)));
    case ENC_HEX:
        return HexFixedXOR(text, key);
    }
}
/**
 *  Pad text string by appending  padding character until string reaches desired
 *  length.
 *  @param text Text to pad
 *  @param paddingChar Padding character integer value to append to the end of
 *  text, integer is converted to the right encoding before appending it
 *  @param length Required length of returned string
 *  @param encod Encoding of txt (one of ENC_* macros)
 */
string PadString(string const &text, uint32_t length, uint8_t encod, int8_t paddingChar)
{
    string retVal(text);
    string paddingASCII;

    //  Calculate padding character based on difference in length (PCSK#7 scheme)
    paddingChar = length - text.length();

    switch(encod)
    {
    case ENC_ASCII:
        paddingASCII.resize(length-text.length(), paddingChar);
        retVal += paddingASCII;
        break;
    case ENC_BASE64:
        return "ERROR"; //  Illegal action
    case ENC_HEX:
        paddingASCII.resize((length-text.length())/2, paddingChar);
        string paddingHex = ASCIIToHex(paddingASCII);
        retVal += paddingHex;
        break;
    }

    return retVal;
}

//------------------------------------------------------------------------------
//      Operations on ASCII-encoded data                                [PUBLIC]
//------------------------------------------------------------------------------
/**
 *  Convert input ASCII string into a Base64 string
 *  @param arg Input ASCII string
 *  @return Corresponding Base64 string
 */
string ASCIIToBase64(string const &arg)
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
    retVal.resize(b64Len, 0);

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
 *  Convert input ASCII string to hex string. Additionally, if length is supplied
 *  function will repeat input string for as many time needed to reach the length.
 *  Example: if arg="okl" and length=7 function returns "okloklo" in HEX
 *  @param arg ASCII string to convert to HEX
 *  @param length (optional) length of output string
 *  @return HEX value of input ASCII string
 */
string ASCIIToHex(string const &arg, uint32_t length)
{
    string retVal;

    if (length == 0)
        length = arg.length()*2;

    retVal.resize(length, 0);

    for (int i = 0; i <length; i+=2)
    {
        retVal[i] = IntToHexChar((arg[((i/2)%arg.length())]>>4) & 0x0F);
        retVal[i+1] = IntToHexChar(arg[((i/2)%arg.length())] & 0x0F);
    }

    return retVal;
}

/**
 *  Perform XOR on two ASCII strings
 *  @param arg1 First ASCII string
 *  @param arg2 Second ASCII string
 *  @return ASCII-encoded result of XOR operator on two inputs
 */
string ASCIIFixedXOR(string const &arg1,string const &arg2)
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
 *  Perform repeating-key XORing of given text and key. In this process, key is
 *  extended by repeating original key to match the length of text string.
 *  Result is returned as HEX-encoded string
 *  @param text ASCII text to encrypt with repeating key
 *  @param key Arbitrary length key to use for encryption of text variable
 *  @return ASCII result of repeated-key XORing of text and key
 */
string ASCIIRepeatKeyXOR(string const &text, string const &key)
{
//    Using native implementation, without HEX
//    //  Convert text to hex
//    string txtHex = ASCIIToHex(text);
//    //  Convert key to hex and repeat it as many times as need to have the same
//    //  length as text
//    string keyHex = ASCIIToHex(key, txtHex.length());

    //  Ensure key and text have matching lengths
    string newKey;
    for (uint32_t i = 0; i < text.length(); i++)
        newKey += key[i % key.length()];

    return ASCIIFixedXOR(text, newKey);
}

/**
 *  Calculate Hamming distance between two equal-length ASCII strings
 *  To do so, chars at the same index are XORed which produces 1 at the position
 *  where bits in two characters mismatch. The result is just counting number of
 *  1s in XORed variable
 *  @param arg1 First ASCII string
 *  @param arg2 Second ASCII string
 *  @return Humming distance between 2 input strings; ULLONG_MAX if length of
 *  strings is not the same
 */
uint32_t ASCIIDistHamming(string const &arg1, string const &arg2)
{
    uint32_t retVal = 0;

    if (arg1.length() != arg2.length())
        return (ULLONG_MAX & 0xFFFFFFF);

    for (uint32_t i = 0; i < arg1.length(); i++)
    {
        //  XOR two chars, this will set 1 in all bits that don't match, then we
        //  just need to count number of bits that are 1
        uint8_t xorRes = arg1[i] ^ arg2[i];

        //  Count number of bits that are 1
        for (uint8_t j = 0; j < 8; j++)
            if ((xorRes>>j) & 0x01)
                retVal++;
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
bool validASCIIString(string const &arg, bool lc, bool uc, bool num, bool sent,
                      bool comm, bool spec, bool cont)
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
        //  Check if it's sentence punctuation !'",.:;()/
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

//------------------------------------------------------------------------------
//      Operations on Base64-encoded data                               [PUBLIC]
//------------------------------------------------------------------------------
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

    //  Length of HEX is simply length data part of Base64*6 (since B64 takes
    //  6 bits to encode one sign) reduced by the number of padded zeros to
    //  B64 string(2*number of '=') divided by 4 (since HEX encodes char with 4
    //                                            bits)
    //  Allocate memory for output string
    retVal.resize((b64Len*6-b64Pad*2)/4, 0);

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
 *  Calculate Hamming distance between two equal-length Base64-encoded strings
 *  To do so, chars at the same index are XORed which produces 1 at the position
 *  where bits in two characters mismatch. The result is just counting number of
 *  1s in XORed variable
 *  @param arg1 First Base64-encoded string
 *  @param arg2 Second Base64-encoded string
 *  @return Humming distance between 2 input strings; ULLONG_MAX if length of
 *  strings is not the same
 */
uint32_t Base64DistHamming(string const &arg1, string const &arg2)
{
    uint32_t retVal = 0;

    if (arg1.length() != arg2.length())
        return (ULLONG_MAX & 0xFFFFFFF);

    for (uint32_t i = 0; i < arg1.length(); i++)
    {
        //  XOR two chars, this will set 1 in all bits that don't match, then we
        //  just need to count number of bits that are 1
        uint8_t xorRes =  B64CharToInt(arg1[i]) ^ B64CharToInt(arg2[i]);

        //  Count number of bits that are 1
        for (uint8_t j = 0; j < 8; j++)
            if ((xorRes>>j) & 0x01)
                retVal++;
    }

    return retVal;
}

//------------------------------------------------------------------------------
//      Operations on HEX-encoded data                                  [PUBLIC]
//------------------------------------------------------------------------------
/**
 *  Convert HEX-encoded string into its ASCII representation
 *  @param arg HEX-encoded string to decode
 *  @return ASCII representation of input string
 */
string HexToASCII(string const &arg)
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
 *  Convert input HEX string into a Base64 string
 *  @param arg Input HEX string
 *  @return Corresponding Base64 string
 */
string HexToBase64(string const &arg)
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

    for (int8_t j = b64Len; j < (b64Len+b64Pad); j++)
        retVal[j] = '=';

    return retVal;
}

/**
 *  Perform XOR on two HEX encoded strings
 *  @param arg1 First HEX-encoded string
 *  @param arg2 Second HEX-encoded string
 *  @return HEX-encoded result of XOR operator on two inputs
 */
string HexFixedXOR(string const &arg1,string const &arg2)
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
 *  Perform repeating-key XORing of given text and key. In this process, key is
 *  extended by repeating original key to match the length of text string.
 *  Result is returned as HEX-encoded string
 *  @param text HEX text to encrypt with repeating key
 *  @param key Arbitrary-length key to use for encryption of text variable
 *  @return HEX result of repeated-key XORing of text and key
 */
string HexRepeatKeyXOR(string const &text, string const &key)
{
    string keyNew;

    //  Ensure that text and key have matching sizes
    for (uint32_t i = 0; i < text.length(); i++)
        keyNew += key[i % key.length()];

    return HexFixedXOR(text, keyNew);
}

/**
 *  Calculate Hamming distance between two equal-length HEX-encoded strings
 *  To do so, chars at the same index are XORed which produces 1 at the position
 *  where bits in two characters mismatch. The result is just counting number of
 *  1s in XORed variable
 *  @param arg1 First HEX-encoded string
 *  @param arg2 Second HEX-encoded string
 *  @return Humming distance between 2 input strings; ULLONG_MAX if length of
 *  strings is not the same
 */
uint32_t HexDistHamming(string const &arg1, string const &arg2)
{
    uint32_t retVal = 0;

    if (arg1.length() != arg2.length())
        return (ULLONG_MAX & 0xFFFFFFF);

    for (uint32_t i = 0; i < arg1.length(); i++)
    {
        //  XOR two chars, this will set 1 in all bits that don't match, then we
        //  just need to count number of bits that are 1
        uint8_t xorRes = HexCharToInt(arg1[i]) ^ HexCharToInt(arg2[i]);

        //  Count number of bits that are 1
        for (uint8_t j = 0; j < 8; j++)
            if ((xorRes>>j) & 0x01)
                retVal++;
    }

    return retVal;
}
