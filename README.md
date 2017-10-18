My solutions to Crypto challenge 
===============================
*Implementation language: __C++__*

Recently I've completed a project in web-development which, among other things, dealt with implementing session management and user registration. The literature I used constantly emphasized the importance of using the right cryptographic functions and their initialization in order to protect user data and prevent possible attacks aimed at reveling sensitive data.

In an attempt to grasp basic concepts of cryptography and gain better understanding of some of the functions I've used in previous project, I've decided to try [Crypto challenge](https://cryptopals.com/). It seemed like a cool way that demonstrates basic principles in crypto through a number of programming problems starting from the lowest level, simple artificial problems, which then gradually increase in difficulty to match real-life cases.

## Folder organization
Project files are organized according to problems sets. Folders 'set``*``' (``*`` is integer corresponding to set number) contain :

* One header file with declarations of commonly used functions in this problem set (e.g. `FixedXORASCII()`, `HexToBase64()` etc.) and a matching .cpp file with implementation of these functions
* Number of ch``*``.cpp (``*`` is integer corresponding to challenge number) files with solution to challenges within the set
