My solutions to Crypto challenge
===============================
*Implementation language: __C++__*

Recently I've completed a project in web-development which, among other things, dealt with implementing session management and user registration. The literature I used constantly emphasized the importance of using the right cryptographic functions and their initialization in order to protect user data and prevent possible attacks aimed at reveling sensitive data.

In an attempt to grasp basic concepts of cryptography and gain better understanding of some of the functions I've used in previous project, I've decided to try [Crypto challenge](https://cryptopals.com/). It seemed like a cool way that demonstrates basic principles in crypto through a number of programming problems starting from the lowest level, simple artificial problems, which then gradually increase in difficulty to match real-life cases.

## Folder organization
Project files are organized according to problems sets:

* **'set``*``'** folders (``*`` is integer corresponding to set number) containing :
  * Number of **ch``*``.cpp** (``*`` is integer corresponding to challenge number) files with solution to challenges within the set
  *  Any input/output files connected to the challenge, with prefix **ch``*``\_fileName**
* **'libs'** folder containing:
  * Header and source files of libraries made while solving problems
  * `librarize.bash` bash script which produces linkable library libbasicfunc.a to be used while compiling source files from **'set``*``'** folders
  * **'unitt'** folder with files related to unit test of libraries in its parent folder

## Progress
**Set 1**
    1. [X]  Convert hex to base64
    2. [X]  Fixed XOR
    3. [X]  Single-byte XOR cipher
    4. [X]  Detect single-character XOR
    5. [X]  Implement repeating-key XOR
    6. [X]  Break repeating-key XOR
    7. [X]  AES in ECB mode
    8. [X]  Detect AES in ECB mode

**Set 2**
     9. [X]  Implement PKCS#7 padding
    10. []  Implement CBC mode
    11. []  An ECB/CBC detection oracle
    12. []  Byte-at-a-time ECB decryption (Simple)
    13. []  ECB cut-and-paste
    14. []  Byte-at-a-time ECB decryption (Harder)
    15. []  PKCS#7 padding validation
    16. []  CBC bitflipping attacks
