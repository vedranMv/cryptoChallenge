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
  - [x]  Convert hex to base64
  - [x]  Fixed XOR
  - [x]  Single-byte XOR cipher
  - [x]  Detect single-character XOR
  - [x]  Implement repeating-key XOR
  - [x]  Break repeating-key XOR
  - [x]  AES in ECB mode
  - [x]  Detect AES in ECB mode

**Set 2**
  - [x]  Implement PKCS#7 padding
  - [x]  Implement CBC mode
  - [ ]  An ECB/CBC detection oracle
  - [ ]  Byte-at-a-time ECB decryption (Simple)
  - [ ]  ECB cut-and-paste
  - [ ]  Byte-at-a-time ECB decryption (Harder)
  - [ ]  PKCS#7 padding validation
  - [ ]  CBC bitflipping attacks
