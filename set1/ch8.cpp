/**
 *  Detect AES in ECB mode
 *  By following the logic that AES in ECB mode is stateless and deterministic
 *  (the same 16 byte plaintext block will always produce the same 16 byte
 *  ciphertext) find string in the file that is most likely to have been encoded
 *  with AES in EBC.
 *
 *
 *  Created: 21. Oct 2017.
 *  Author: Vedran Mikov
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include "../libs/basicFunctions.h"

//  Used for sorting distances
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

typedef tuple<string, uint32_t> entry;


int main()
{
    //  Open external resource file
    fstream file;
    file.open("ch8_res1.txt");

    string b1;  //  Holds extracted line from file
    //  Open file, load one line of HEX data, split it in blocks and compare all
    //  blocks for matches
    vector< entry >ranking;
    while (getline(file, b1))
    {
        //  Store blocks of data for matching
        vector<string>block;
        //  Holds temporary block of data extracted from ciphertext
        string tmp;
        //  Here we split the ciphertext in 16byte-long blocks -> in HEX one 1
        //  byte is 2 HEX characters, ergo i%32
        for (uint32_t i = 0; i < b1.length(); i++)
        {
            tmp += b1[i];
            if ((i % 32) == 0)
            {
                block.push_back(tmp);
                tmp = string();
            }
        }

        //  Count matches between blocks
        uint32_t match = 0;
        for (uint32_t i = 0; i < block.size(); i++)
            for (uint32_t j = (i+1); j < block.size(); j++)
                if (block[i] == block[j])
                    match++;

        //  Save result
        ranking.push_back(make_tuple(b1, match));
    }

    //  Close file, we're done
    file.close();

    //  Sort vector in descending order based on number of matches
    sort(ranking.begin(), ranking.end(),
        [](entry const &t1, entry const &t2) {
            return get<1>(t1) > get<1>(t2);
        }
    );

    //  Count how many entries have non-zero number of matches
    uint32_t nonZero = 0;
    for (auto &X : ranking)
        if (get<1>(X) > 0)
        nonZero++;

    //  Report to user
    cout<<"Found "<< nonZero <<" string with non-zero block repeats"<<endl;
    cout << "With "<<get<1>(ranking[0])<<" matches, most probable string is: \n\t"<<get<0>(ranking[0])<<endl;
    cout << "Next one has "<<get<1>(ranking[1])<<" matches, string is: \n\t"<<get<0>(ranking[1])<<endl;

    return 0;
}


