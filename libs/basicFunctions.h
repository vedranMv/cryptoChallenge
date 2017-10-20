/**
 *    Basic functions implemented through Set 1 of crypto challenges
 *
 *    Created: 14. Oct 2017.
 *    Author: Vedran Mikov
 */
#include <string>
#include <cstdint>

using namespace std;

/**
 *  Provides mapping of hex characters to their integer value
 *  Example: '0'->0, '9'->9, 'B'->11, 'f'->15
 */
uint8_t HexCharToInt (int8_t const &arg);

/**
 *  Convert input ASCII string into a Base64 string
 *  @param arg Input ASCII string
 *  @return Corresponding Base64 string
 */
string ASCIItoBase64(string const &arg);
/**
 *  Convert input ASCII string to hex string. Additionally, if length is supplied
 *  function will repeat input string for as many time needed to reach the length.
 *  Example: if arg="okl" and length=7 function returns "okloklo" in HEX
 *  @param arg ASCII string to convert to HEX
 *  @param length (optional) length of output string
 *  @return HEX value of input ASCII string
 */
string ASCIIToHex(string const &arg, uint32_t length = 0);
/**
 *  Perform XOR on two ASCII strings
 *  @param arg1 First ASCII string
 *  @param arg2 Second ASCII string
 *  @return ASCII-encoded result of XOR operator on two inputs
 */
string ASCIIFixedXOR(string const &arg1,string const &arg2);
/**
 *  Perform repeating-key XORing of given text and key. In this process, key is
 *  extended by repeating original key to match the length of text string.
 *  Result is returned as HEX-encoded string
 *  @param text ASCII text to encrypt with repeating key
 *  @param key Arbitrary length key to use for encryption of text variable
 *  @return ASCII result of repeated-key XORing of text and key
 */
string ASCIIRepeatKeyXOR(string const &text, string const &key);
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
uint32_t ASCIIDistHamming(string const &arg1, string const &arg2);
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
bool   validASCIIString(string const &arg, bool lc = true, bool uc = true,
                      bool num = true, bool sent = true, bool comm = true,
                      bool spec = false, bool cont = false);


/**
 *  Convert input Base64 string into a HEX string
 *  @param arg Input Base64 string
 *  @return Corresponding HEX string
 */
string Base64ToHex(string const &arg);
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
uint32_t Base64DistHamming(string const &arg1, string const &arg2);


/**
 *  Convert HEX-encoded string into its ASCII representation
 *  @param arg HEX-encoded string to decode
 *  @return ASCII representation of input string
 */
string HextoBase64(string const &arg);
/**
 *  Convert input HEX string into a Base64 string
 *  @param arg Input HEX string
 *  @return Corresponding Base64 string
 */
string HexToASCII(string const &arg);
/**
 *  Perform XOR on two HEX encoded strings
 *  @param arg1 First HEX-encoded string
 *  @param arg2 Second HEX-encoded string
 *  @return HEX-encoded result of XOR operator on two inputs
 */
string HexFixedXOR(string const &arg1,string const &arg2);
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
uint32_t HexDistHamming(string const &arg1, string const &arg2);
