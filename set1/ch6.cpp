/**
 *  Break repeating-key XOR
 *  Given a text file whose content has been base64'd after encryption with
 *  repeating-key XOR, break the encryption, decrypt content of file.
 *
 *  Created: 18. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "../libs/basicFunctions.h"

//  Used for sorting distances
#include <vector>
#include <tuple>
#include <algorithm>

//  Number of blocks used in computing average humming distance
#define DIST_BLOCKS 5

using namespace std;

typedef tuple<uint16_t, uint32_t> entry;


int main()
{
    //  Open external resource file
    fstream file;
    file.open("ch6_res1.txt");
    //  Holds extracted line from file
    string b1, txtStr;

    //  Load file into a single string
    while (getline(file, b1))
        txtStr += b1;

    //  Close file, we're done
    file.close();

    //  Generate string key used for decryption through XORing
    string txtASCII = HexToASCII(Base64ToHex(txtStr));

    //  This vector will hold a rank(Hamming distance)
    vector< entry >ranking;

    //  Here with take DIST_BLOCKS keysize-long blocks from the beginning of the
    //  ciphertext and calculate Humming distance, normalized by dividing with
    //  keysize and averaged
    for (uint8_t keysize = 2; keysize < 40; keysize++)
    {
        //  Blocks
        vector <string> block(DIST_BLOCKS);

        //  Load DIST_BLOCKS keysize-long blocks with data
        for (uint8_t i = 0; i < keysize; i++)
            for (uint8_t j = 0; j < block.size(); j++)
                block[j] += txtASCII[i+j*keysize];

        //  Calculate hamming distance between all blocks, and normalize it by
        //  dividing with keysize
        uint32_t hDistNorm = 0;
        for (uint8_t i = 0; i < block.size(); i++)
            for (uint8_t j = (i+1); j < block.size(); j++)
                hDistNorm += ASCIIDistHamming(block[i], block[j])/keysize;

        //  Save average distance for each keysize parameter into a vector
        ranking.push_back(make_tuple(keysize, hDistNorm/block.size()));
    }

    //  Sort vector in ascending order based on distances
    sort(ranking.begin(), ranking.end(),
        [](entry const &t1, entry const &t2) {
            return get<1>(t1) < get<1>(t2);
        }
    );

    //  Loop through different key lengths based on their scoring and attempt to
    //  find the right one for decrypting
    for(auto X : ranking)
    {
        cout<<"Testing "<<(get<0>(X))<<" char long key"<<endl;
        //  We're splitting ciphertext in blocks of keysize length, then we group
        //  all first letters into a separate string, 2nd letters into another
        //  string and so on for the whole keysize-long block, resulting in
        //  keysize number of substrings (or the first argument of ranking vector)
        vector<string>block(get<0>(X));

        //  Split ciphertext in string blocks described above
        for (uint32_t i = 0; i < txtASCII.length(); i++)
            block[(i%get<0>(X))] += txtASCII[i];

        //  Loop through all possible single-char keys and find the char which
        //  produces meaningful result on a given block. All possible
        //  chars decrypting this block are saved in charpool 2D vector
        vector< vector<uint8_t> >charpool(get<0>(X));

        for (uint8_t key = 0; key < 128; key++)
        {
            string keyASCII(" ");
            keyASCII[0] = key;

            //  Do repeating-key XOR, where key is single-char
            for (uint16_t i = 0; i < block.size(); i++)
            {
                //  XOR a block against a single-char key, which will get repeated
                string res = ASCIIRepeatKeyXOR(block.at(i), keyASCII);

                //  We "know" we're looking for a normal text, alphanumeric chars
                //  and sentence characters. Nothing else
                if (validASCIIString(res,true,true,true,true,true,false))
                    charpool[i].push_back(key);
            }
        }

        //  Check if we've got a hit on all block for at least one key
        bool totalPass = true;
        //  This is product of sizes of all vectors in order to generate all
        //  possible combinations of keys to test later on
        uint64_t totalComb = 1;
        //  Loop through all blocks and compute two parameters above
        for (uint32_t i = 0; i < get<0>(X); i++)
            totalPass &= (charpool[i].size() > 0), totalComb *= charpool[i].size();


        if (totalPass)
        {
            cout<<"BBBIIIIINNGGOOOOO!!!, "<<totalComb<<" keys to test"<<endl;
            for (uint32_t i = 0; i < totalComb; i++)
            {
                string key;
                uint32_t tComb = i;
                for (uint32_t j = 0; j < get<0>(X); j++)
                {
                    key += charpool[j][tComb % charpool[j].size()];
                    tComb = tComb - (tComb % charpool[j].size());
                }
                cout<<key<< endl;
            }
        }
    }

    //  Procedure above prints out all possible keys, now we prompt user to input
    //  tone of the keys and test the program
    char inputKey[256];
    string masterKey;

    cout<<"Input one of the above keys to try and decrypt input file: ";
    cin.getline(inputKey, 256);
    masterKey = string(inputKey);

    cout<<"Decrypting, check output file decrypted.out";

    //  Open external resource file
    file.open("ch6_decrypted.out", ios::out);
    file << ASCIIRepeatKeyXOR(txtASCII, masterKey);
    file.close();

    cout<<"done"<<endl;

    return 0;
}
