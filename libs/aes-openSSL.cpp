/**
 *    Implementation of functions from AES-OpenSSL header
 *    Description
 *
 *    Created: 21. Oct 2017.
 *    Author: Vedran Mikov
 */
#include <vector>
#include <memory>
#include <limits>
#include <stdexcept>

#include <openssl/evp.h>
#include <openssl/rand.h>

#include "aes-openSSL.h"
#include "basicFunctions.h"


//------------------------------------------------------------------------------
//      Custom OpenSSL data-types                                      [PRIVATE]
//------------------------------------------------------------------------------
template <typename T>
struct zallocator
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer address (reference v) const {return &v;}
    const_pointer address (const_reference v) const {return &v;}

    pointer allocate (size_type n, const void* hint = 0) {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
            throw std::bad_alloc();
        return static_cast<pointer> (::operator new (n * sizeof (value_type)));
    }

    void deallocate(pointer p, size_type n) {
        OPENSSL_cleanse(p, n*sizeof(T));
        ::operator delete(p);
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof (T);
    }

    template<typename U>
    struct rebind
    {
        typedef zallocator<U> other;
    };

    void construct (pointer ptr, const T& val) {
        new (static_cast<T*>(ptr) ) T (val);
    }

    void destroy(pointer ptr) {
        static_cast<T*>(ptr)->~T();
    }

#if __cpluplus >= 201103L
    template<typename U, typename... Args>
    void construct (U* ptr, Args&&  ... args) {
        ::new (static_cast<void*> (ptr) ) U (std::forward<Args> (args)...);
    }

    template<typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
#endif
};

typedef unsigned char byte;
typedef std::basic_string<char, std::char_traits<char>, zallocator<char> > secure_string;
using EVP_CIPHER_CTX_free_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;


//  Function prototypes for low-level OpenSSL calls
void aes_encrypt(const byte key[AES_ECB_BLOCK_SIZE],
                 const byte iv[AES_ECB_BLOCK_SIZE],
                 const secure_string& ptext,
                 secure_string& ctext);
void aes_decrypt(const byte key[AES_ECB_BLOCK_SIZE],
                 const byte iv[AES_ECB_BLOCK_SIZE],
                 const secure_string& ctext,
                 secure_string& rtext);


/**
 *  Load OpenSSL cipher
 */
void InitAES128EBC()
{
    // Load the necessary cipher
    EVP_add_cipher(EVP_aes_128_ecb());
}

//------------------------------------------------------------------------------
//      Encryption/Decryption functions for single block                [PUBLIC]
//------------------------------------------------------------------------------
/**
 *  AES-128 CBC encryption of a single block
 *  @param key Key for encryption
 *  @param iv Initialization vector used to encrypt original text, for this
 *  function usually set to zero vector
 *  @param cipherblock One block of ciphertext
 *  @return Result of AES encryption of given block (note that length might not
 *  be the same as length of a block since AES might pad it to 2*block_length)
 */
std::string AESCBCEncryptBlock(const std::string key, const std::string iv, std::string const &text)
{
    secure_string   ptext(text.c_str(), text.length());
    secure_string   ctext;

    aes_encrypt((const byte*)key.c_str(), (const byte*)iv.c_str(), ptext, ctext);

    return std::string(ctext.c_str(), ctext.length());
}

/**
 *  AES-128 CBC decryption of a single block
 *  @param key Key for decryption
 *  @param iv Initialization vector used to encrypt original text, for this
 *  function usually set to zero vector
 *  @param cipherblock One block of ciphertext data
 *  @return Result of AES decryption of given block
 */
std::string AESCBCDecryptBlock(const std::string key, const std::string iv, std::string const &cipherblock)
{
    std::string retVal;
    secure_string   ctext(cipherblock.c_str(), cipherblock.length());
    secure_string   rtext;

    //  Instead of calling this function it needs to be pasted here, otherwise
    //  linking errors
    aes_decrypt((const byte*)key.c_str(), (const byte*)iv.c_str(), ctext, rtext);

    retVal = std::string(rtext.c_str(), rtext.length());
    return retVal;
}

//------------------------------------------------------------------------------
//      Encryption/Decryption functions for plain text                  [PUBLIC]
//------------------------------------------------------------------------------
/**
 *  AES-128 CBC encryption of plain text
 *  @param key Key for encryption
 *  @param iv Initialization vector used to encrypt first block of text
 *  @param text
 *  @return Ciphertext, result of AES encryption of plain text input
 */
string AESCBCEncryptText(const string key, const string iv, string const &text)
{
    string cipherText;

    //  Split text into AES_ECB_BLOCK_SIZE long blocks
    vector<string>block;
    string tmp("");
    for (uint32_t i = 1; i <= text.length(); i++)
    {
        tmp += text[i-1];
        if ((i % AES_ECB_BLOCK_SIZE) == 0)
            block.push_back(tmp), tmp = string("");
    }
    //  If the last block isn't long enough pad it t a given block size according
    //  to PKCS#7
    if (tmp != "")
        block.push_back(PadString(tmp, AES_ECB_BLOCK_SIZE, ENC_ASCII));

    //  Initialize variable that holds last value of cipher that will be XORed
    //  with block in the next loop iteration
    //  CBC encryption takes XOR between cipher from last iteration, and block of
    //  plain text from this iteration. Result is then encrypted using simple ECB
    //  encryption and truncated to the length of a block
    string lastBlock(iv.c_str(), iv.length());
    for (uint32_t i = 0; i < block.size(); i++)
    {
        //  XOR of block from this iteration, and cipher of a block from last
        //  iteration (or initialization vector if this is first iteration)
        string tmp = ASCIIFixedXOR(block[i], lastBlock);
        //  Encrypt this block with given key, zeroVect simply says we apply no
        //  initialization vector in encryption (because it got applied in line
        //  above manually)
        tmp = AESCBCEncryptBlock(key, zeroVect, tmp);
        //  Truncate result of encryption to block size
        lastBlock = string(tmp.c_str(), AES_ECB_BLOCK_SIZE);
        //  Add result to ciphertext
        cipherText += lastBlock;
    }

    //  Return ciphertext
    return cipherText;
}

/**
 *  AES-128 CBC decryption of a ciphertext
 *  @param key Key for decryption
 *  @param iv Initialization vector used to encrypt original text
 *  @param cyphertext
 *  @return Plain text retrieved from cipher
 */
string AESCBCDecryptText(const string key, const string iv, string const &ciphertext)
{
    //  Split ciphertext in blocks of size AES_ECB_BLOCK_SIZE
    vector<string>encryptedBlock;
    string tmp("");
    for (uint32_t i = 1; i <= ciphertext.length(); i++)
    {
        tmp += ciphertext[i-1];
        if ((i % AES_ECB_BLOCK_SIZE) == 0)
        {
            encryptedBlock.push_back(tmp);
            tmp = string("");
        }
    }

    //  Initialize variable that holds last value of cipher that will be XORed
    //  with block in the next loop iteration
    //  CBC decryption first decrypts a block of ciphertext, then XORs it with
    //  block of ciphertext(unencrypted) from previous iteration (or initialization
    //  vector if this is first iteration) to get original text.
    string lastBlock(iv.c_str(), iv.length());
    string plainText;
    for (uint32_t i = 0; i < encryptedBlock.size(); i++)
    {
        string tmp = encryptedBlock[i];
        //  We're decrypting a block of AES_ECB_BLOCK_SIZE of ciphertext, which
        //  has to be twice the block size in order to be a valid AES ciphertext.
        //  (remember AES pads strings before encryption to have size that's
        //  multiple of block length but if the text to encrypt is already a
        //  multiple of block length, it will be padded to its current length +
        //  another block length). Since we're expecting exactly AES_ECB_BLOCK_SIZE
        //  of decrypted data, our encrypted block needs to be 2*AES_ECB_BLOCK_SIZE,
        //  so we pad it. Padding gets discarded anyway and it doesn't affect
        //  encryption because we're encrypting in ECB mode :)
        tmp = PadString(tmp, 2* AES_ECB_BLOCK_SIZE, ENC_ASCII);

        //  Decrypting the ciphertext block after padding
        tmp = AESCBCDecryptBlock(key, zeroVect, tmp);
        //  Truncate result to the length of one block
        tmp = string(tmp.c_str(), AES_ECB_BLOCK_SIZE);

        //  XORing it against ciphertext block from last iteration (or
        //  initialization vector in case this is first iteration)
        tmp = ASCIIFixedXOR(lastBlock, tmp);

        //  Save block of ciphertext for XORing in next iteration
        lastBlock = encryptedBlock[i];
        plainText += tmp;
    }

    //  Remove padding from the end
    plainText.resize(plainText.length() - plainText[plainText.length()-1]);
    return plainText;
}

//------------------------------------------------------------------------------
//      Encryption/Decryption functions from low-level OpenSSL library  [PUBLIC]
//------------------------------------------------------------------------------
void aes_encrypt(const byte key[AES_ECB_BLOCK_SIZE],
                 const byte iv[AES_ECB_BLOCK_SIZE],
                 const secure_string& ptext,
                 secure_string& ctext
){
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_128_ecb(), NULL, key, iv);
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptInit_ex failed");

    // Recovered text expands upto BLOCK_SIZE
    ctext.resize(ptext.size()+AES_ECB_BLOCK_SIZE);
    int out_len1 = (int)ctext.size();

    rc = EVP_EncryptUpdate(ctx.get(), (byte*)&ctext[0], &out_len1,
                           (const byte*)&ptext[0], (int)ptext.size());
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptUpdate failed");

    int out_len2 = (int)ctext.size() - out_len1;
    rc = EVP_EncryptFinal_ex(ctx.get(), (byte*)&ctext[0]+out_len1, &out_len2);
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptFinal_ex failed");

    // Set cipher text size now that we know it
    ctext.resize(out_len1 + out_len2);
}

void aes_decrypt(const byte key[AES_ECB_BLOCK_SIZE],
                 const byte iv[AES_ECB_BLOCK_SIZE],
                 const secure_string& ctext,
                 secure_string& rtext)
{
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_128_ecb(), NULL, key, iv);
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptInit_ex failed");

    // Recovered text contracts upto BLOCK_SIZE
    rtext.resize(ctext.size());
    int out_len1 = (int)rtext.size();

    rc = EVP_DecryptUpdate(ctx.get(), (byte*)&rtext[0], &out_len1, (const byte*)&ctext[0], (int)ctext.size());
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptUpdate failed");

    int out_len2 = (int)rtext.size() - out_len1;
    rc = EVP_DecryptFinal_ex(ctx.get(), (byte*)&rtext[0]+out_len1, &out_len2);

//    if (rc != 1)
//      throw std::runtime_error("EVP_DecryptFinal_ex failed");

    // Set recovered text size now that we know it
    rtext.resize(out_len1 + out_len2);
}
