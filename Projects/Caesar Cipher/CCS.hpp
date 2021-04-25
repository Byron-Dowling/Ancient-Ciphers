#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "CCS.h"

using namespace std;


/**
   Public : FrequencyAnalysis

   Description:
        This method performs a Frequency Analysis on the each CipherText string and logs
        the results to determine which cipher letter is occuring the most. This will also
        account for spaces but these are skipped. Upon completion the SetShiftRate function
        is called after each iteration. When the loop executes again, the Frequency array is
        reset to zero so the next string can be tested.

   Params:
        - ofstream& outfile
        - Protected Class Data Members

   Returns:
        - void
 */

void CaesarCipher::FrequencyAnalysis(ofstream& out)
{
    string Temp;
    int count = 0;

    for (int i = 0; i < TestCases; i++)
    {
        for (int l = 0; l < 27; l++)
        {
            Frequency[l] = 0;
        }

        Temp = EncryptedStack[i];


        for (int j = 0; j < Temp.length(); j++)
        {
            for (int k = 0; k < Alphabet.size(); k++)
            {
                if (Temp[j] == Alphabet[k])
                {
                    count = (Frequency[k] + 1);
                    Frequency[k] = count;
                }
            }
        }

        SetShiftRate(i, out);
    }

    Decrypt(out);
    Print(out);
}



/**
   Public : SetShiftRate

   Description:
        This method builds upon what Frequency Analysis does by determining the length of our Key.
        This is done by determining what index has the highest occuring Cipher Text letter and then
        walking this back until it reaches E within the Alphabet string if the index is greater than
        the index of E, if it is less than E than modular arithmetic is performed. The final result
        is pushed to our pointer array of integer "Keys" with the passed index value keeping track
        of which position of the array receives what.

   Params:
        - ofstream& outfile
        - int index
        - Protected Class Data Members

   Returns:
        - void
 */

void CaesarCipher::SetShiftRate(int index, ofstream& out)
{
    int ShiftIndex = 0;
    int HF = 0;                             // Highest Frequency
    int TempKey = 0;
    int FAO_Index = 0;

    ShiftIndex = Frequency[1];              // Start the highest frequency at position A
                                            // Skipping index 0 which is for spaces
    for (int i = 2; i < 27; i++)
    {
        if (Frequency[i] > ShiftIndex)      // If Frequency is higher, it becomes new highest
        {
            HF = i;
            ShiftIndex = Frequency[i];
        }

    }

    for (int j = 0; j < Alphabet.size(); j++)
    {
        if (Alphabet[j] == FrequencyAnalysisOrder[0])
        {
            FAO_Index = j;
        }

    }


    if (HF > FAO_Index)
    {
        TempKey = HF - FAO_Index;
    }
    else
    {
        TempKey = (26 - (FAO_Index - HF));
    }

    Key[index] = TempKey;                   // Key Length is stored in the pointer array

}


/**
   Public : Decrypt

   Description:
        This method is responsible for performing the shifting of the Encrypted Text to the length of the
        key associated with said index position. This is achieved by assigning the current iteration of the
        encrypted stack into a temporary string and shifting each letter of the string. As the shifting occurs
        the new plaintext is pushed to a Temperoray Stack which is eventually assigned to the member variable
        Decrypted Stack so that it can be printed at a later time.

   Params:
        - ofstream& outfile
        - Protected Class Data Members

   Returns:
        - void
 */

void CaesarCipher::Decrypt(ofstream& out)
{
    string* TempDecrypt = new string[TestCases];                    // Dynamically creating temporary memory to store our Temp strings

    for (int i = 0; i < TestCases; i++)
    {
        string Temp = EncryptedStack[i];
        int TempKey = Key[i];

        for (int j = 0; j < Temp.length(); j++)
        {
            if (int(Temp[j]) < 65 || int(Temp[j]) > 91)             // Ignoring spaces and other undesired characters
            {
                TempDecrypt[i] += Temp[j];
            }
            else
            {                                                       // Shifting the text while keeping within the proper ASCII range
                TempDecrypt[i] += ((((Temp[j] - TempKey) + 65) % 26) + 65);
            }
        }

        DecryptedStack[i] = TempDecrypt[i];
    }

    delete[] TempDecrypt;                                           // Deallocating memory after it has served its purpose
}


/**
   Public : Print

   Description:
        This method is fairly self-explanatory as the method will print the results of the decryption
        to a file. The user will be prompted to confirm if decryption worked correctly or not and their
        response will be captured and written to the file as well. Some basic error control is implemented
        to account for variations of responses and should improper input be typed in, the loop will begin
        again at the same prompt.

   Params:
        - ofstream& outfile
        - Protected Class Data Members

   Returns:
        - void
 */

void CaesarCipher::Print(ofstream& out)
{
    for (int i = 0; i < TestCases; i++)
    {
        string Response;

        cout << EncryptedStack[i] << endl << endl;
        cout << "Translates to: " << endl << endl;
        cout << DecryptedStack[i] << endl;

        cout << endl << "Did the message decrypt successfully?" << endl;
        cin >> Response;

        if (Response == "Y" || Response == "y" || Response == "Yes" || Response == "yes")
        {
            out << DecryptedStack[i] << endl;
            out << "Was Decryption Successful? - ";
            out << Response << endl;
        }

        else if (Response == "N" || Response == "n" || Response == "No" || Response == "no")
        {
            out << DecryptedStack[i] << endl;
            out << "Was Decryption Successful? - ";
            out << Response << endl;
        }

        else
        {
            cout << "Sorry, that's not a valid option.\n";      // Error control
            i--;                                                // Resets to prior index
        }

    }

}



/**
   Public : openFiles

   Description:
        Prompts the user to define the input and output files the program will use.
        I/O variables are passed by reference so their content can be edited here.

   Params:
        ifstream&    :  array of integers
        ofstream&    :  array size

   Returns:
        Void		 : Variables passed by reference, no return type
 */

void CaesarCipher::openFiles(ifstream& infile, ofstream& outfile)
{
    char inFileName[40];
    char outFileName[40];

    cout << "Enter the input file name: ";
    cin >> inFileName;

    // open input file
    infile.open(inFileName);
    cout << "Enter the output file name: ";
    cin >> outFileName;

    // Open output file.
    outfile.open(outFileName);
}