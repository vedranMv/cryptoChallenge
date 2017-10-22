/**
 *    Declaration of AES-related functions from OpenSSL
 *    Credit: https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
 *
 *    Created: 21. Oct 2017.
 *    Author: Vedran Mikov
 */
#include <string>

#define AES_ECB_BLOCK_SIZE   16

using namespace std;


//  Zero initialization vector, used when no initialization vector is given
const std::string zeroVect(AES_ECB_BLOCK_SIZE, 0x00);

/**
 *  Initialize AES engine and seed rand number generator
 */
void InitAES128EBC();
/**
 *  Generate a random string of specified length
 *  @param keySize Desired length of returned string
 *  @param spec If true allows generator to use special ASCII chars (127, <32),
 *  else generated string consists only of readable characters [32,126]
 *  @return Random ASCII string of specified length
 */
string AESGenerateRandString(const uint8_t keySize, bool spec = false);
/**
 *  AES-128 CBC encryption of a single block
 *  @param key Key for encryption
 *  @param iv Initialization vector used to encrypt original text, for this
 *  function usually set to zero vector
 *  @param cipherblock One block of ciphertext
 *  @return Result of AES encryption of given block (note that length might not
 *  be the same as length of a block since AES might pad it to 2*block_length)
 */
std::string AESCBCEncryptBlock(const std::string key, const std::string iv, std::string const &text);
/**
 *  AES-128 CBC decryption of a single block
 *  @param key Key for decryption
 *  @param iv Initialization vector used to encrypt original text, for this
 *  function usually set to zero vector
 *  @param cipherblock One block of ciphertext data
 *  @return Result of AES decryption of given block
 */
std::string AESCBCDecryptBlock(const std::string key, const std::string iv, std::string const &cipherblock);
/**
 *  AES-128 CBC encryption of plain text
 *  @param key Key for encryption
 *  @param iv Initialization vector used to encrypt first block of text
 *  @param text
 *  @return Ciphertext, result of AES encryption of plain text input
 */
string AESCBCEncryptText(const string key, const string iv, string const &text);
/**
 *  AES-128 CBC decryption of a ciphertext
 *  @param key Key for decryption
 *  @param iv Initialization vector used to encrypt original text
 *  @param cyphertext
 *  @return Plain text retrieved from cipher
 */
string AESCBCDecryptText(const string key, const string iv, string const &ciphertext);
/**
 *  AES-128 EBC encryption of plain text
 *  @param key Key for encryption
 *  @param iv Initialization vector used to encrypt first block of text
 *  @param text
 *  @return Ciphertext, result of AES encryption of plain text input
 */
string AESEBCEncryptText(const string key, const string iv, string const &text);
/**
 *  AES-128 EBC decryption of a ciphertext
 *  @param key Key for decryption
 *  @param iv Initialization vector used to encrypt original text
 *  @param cyphertext
 *  @return Plain text retrieved from cipher
 */
string AESEBCDecryptText(const string key, const string iv, string const &ciphertext);

