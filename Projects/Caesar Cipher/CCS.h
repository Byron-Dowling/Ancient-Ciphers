/**
	Class Name: Caesar Cipher

	Description:
		This class implements the testing process of decrypting strings that
		have been encrypted utilizing a Caesar Cipher. This is acheived by the
		use of Parallel Arrays with Dynamically Allocatated Memory based on the
		number of test cases that is read in and passed to the Class. There are
		strings that are looped through to assist in the Frequency Analysis as
		well as a Dynamic Array for the Key Lengths of each Cipher Text entry.

	Public Methods:
		- CaesarCipher() - default constructor
		- void PushToStack(string CT, int num)
		- void SetSampleSize(int num)
		- void FrequencyAnalysis(ofstream& out)
		- void SetShiftRate(int index, ofstream& out)
		- void Decrypt(ofstream& out)
		- void Print(ofstream& out)

	Private Methods:
		- No Private or Protected methods

	Usage:

		- Read in the numbers of test cases and push to the Pointer Arrays
		- Start decrypting text that was encrypted using shift ciphers
		- Ask the user to confirm if decryption worked
		- Print the results to a file

 */

#pragma once
#include<iostream>

using namespace std;

class CaesarCipher
{
protected:
	string* EncryptedStack;
	string* DecryptedStack;
	int TestCases;
	string Alphabet;
	string FrequencyAnalysisOrder;
	int* Key;
	vector<int> Frequency;

public:

	CaesarCipher()
	{
		Alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";				// String Alphabet accounting for empty spaces as well
		Frequency.resize(27);							// Initializing an empty array to be used to count occurences of letters
		FrequencyAnalysisOrder = "ETAOINSHRDLCUMWFGYPBVKJXQZ";			// Order for most occuring letters in Frequency Analysis
	}

	void PushToStack(string CT, int num)
	{
		EncryptedStack[num] = CT;						// Pushing the CipherText strings to the Array
	}

	void SetSampleSize(int num)							// Setting the number of Test Cases with the read in value
	{										// This is used as the size variable for the Dynamic Memory
		TestCases = num;
		EncryptedStack = new string[TestCases];
		DecryptedStack = new string[TestCases];
		Key = new int[TestCases];
	}

	void openFiles(ifstream& infile, ofstream& outfile);
	void FrequencyAnalysis(ofstream& out);
	void SetShiftRate(int index, ofstream& out);
	void Decrypt(ofstream& out);
	void Print(ofstream& out);


	~CaesarCipher()									// Deallocating Memory upon completion
	{
		delete[] EncryptedStack;
		delete[] DecryptedStack;
		delete[] Key;
	}
};
