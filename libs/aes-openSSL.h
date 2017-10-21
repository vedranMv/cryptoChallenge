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


void InitAES128EBC();
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


