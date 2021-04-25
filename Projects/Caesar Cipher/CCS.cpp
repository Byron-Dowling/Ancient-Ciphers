/*
	Author:           Byron Dowling
	Email:            byrondowling7@gmail.com
	Label:            DSP3
	Title:            Caesar Cipher
	Course:           2433
	Semester:         Fall 2020

	Description:
		 Program reads from a file a number of test cases and strings of
		 encrypted text to be decrypted using a Frequency Analysis.

	Usage:
		 Can be used to Decipher Text that has been encrypted using a Shift
		 Cipher of varying shift lengths and not limited to just the traditional
		 shift length of 4 that Caesar was known for.

	Files:
		 CCS.cpp
		 CCS.h
		 CCS.hpp
		 CC.txt
		 Results.txt
		 CC2.txt
		 Results2.txt

*/

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include "CCS.h"
#include "CCS.hpp"

using namespace std;

int main()
{
	CaesarCipher Run1;								// Declaring Class Object to start the process

	ifstream in;
	ofstream out;
	Run1.openFiles(in, out);						// Calling function to set I/O files

	int SampleSize;
	string Encrypted_Text;


	while (in >> SampleSize)						// Reading in the number of test cases
	{
		Run1.SetSampleSize(SampleSize);				// Setting the Sample Size variables

		for (int i = 0; i < SampleSize; i++)
		{
			getline(in, Encrypted_Text, '#');		// Reading up to the # symbol per string
			Run1.PushToStack(Encrypted_Text, i);	// Adding the Encrypted text to our Pointer Arrays
		}
	}


	Run1.FrequencyAnalysis(out);					// Starting the Frequeny Analysis


	return 0;
}