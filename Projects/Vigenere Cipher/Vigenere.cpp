/*
	Author:           Byron Dowling
	Email:            byrondowling7@gmail.com
	Title:            Vigenere Auto Solver


	Description:
		Program will receive a file containing a message that has been 
		encrypted using a Vigenere Cipher. The program will begin the 
		deciphering process by calculating the index of coincidence on all
		possbile key lengths and order them in order from most likely key length
		to least likely. Once completed, the program will perform a dictionary
		attack on the key length and then recheck the index of coincidence to
		see which dictionary key is the keyword that was used to encrypt the
		message. Once completed, the console provides the decrypted result.


	What the heck is a Vigenere Cipher and how does it work?:
		- https://www.cs.uri.edu/cryptography/classicalvigenere.htm
		- https://github.com/Byron-Dowling/Ancient-Ciphers

	Files:
		Vigenere.cpp
		VigenereClass.hpp
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<chrono>
#include "VigenereClass.hpp"


int main()
{
	std::ifstream in;
	std::ofstream out;

	bool DecryptSuccess = false;
	char Ans;
	int index = 0;

	Vigenere Decoder;				// Vigenere object declared. Main driver of the program.
	Decoder.openFiles(in, out);		// Declaring the file that contains the encrypted text to be cracked


	std::string Temp;
	std::getline(in, Temp);
	Decoder.SetCipherText(Temp);

	/*
		The next 3 method calls will determine the most likely key length by calcultating the Index of Coincidence
		for a key length of 2 through 16. Once each length has been tested, the key order will be sorted
		so that they can be accessed and tested if the top result is not the actual key length. 
	*/

	auto start = std::chrono::high_resolution_clock::now();

	Decoder.Start_Cracking();		
	Decoder.Sort_IOC();
	Decoder.Cipher_Substrings(Temp);

	/*
		Once the key order has been established, this method assumes that the key used to encrypt the message is 
		a word that can be found in the dictionary such as "ENIGMA" and not something like "ASDFGGHS". Therefore,
		the program will perform a dictionary attack by taking the most likely key length and finding all the words
		in the dictionary that match that length. The method will then shift the encrypted text by that dictionary
		word and then check the IOC value of the new string. The results are pushed to a vector and after the first
		push, only results that have an IOC value higher than the current highest are pushed onto the vector. The
		last item pushed on to the vector should be the result.
	*/
	Decoder.Dictionary_Attack_IOC();
	Decoder.GetPlaintext();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast< std::chrono::seconds >(stop - start);

	std::cout << "\nWas the decryption process succcessful? Y/N?\n";
	std::cin >> Ans;

	if (Ans == 'Y' || Ans == 'y')
	{
		DecryptSuccess = true;
		std::cout << "\nCipher was cracked in " << duration.count() << " seconds.\n";
	}

	else
	{
		"Well, that's the weakness of I.O.C based attacks, they can be defeated on small messages.\n";
	}



	/* 
		Everything below this is a work in progress. Currently the cipher will only crack large text examples
		where the IOC is calculated correctly on the first result. 

		Future revisions are likely to still use the IOC key length results and then do a 1:1 dictionary lookup
		of the shifted words. I have been learning CUDA to try and potentially implement a CUDA kernal to assist
		with this number crunching.
	*/

	// while (DecryptSuccess == false && index < 14)
	// {
	// 	std::cout << "\nWas the decryption process succcessful? Y/N?\n";
	// 	std::cin >> Ans;

	// 	while (Ans != 'Y' && Ans != 'y' && Ans != 'N' && Ans != 'n')
	// 	{
	// 		std::cout << "Please enter a valid response\n";

	// 		std::cout << "\nWas the decryption process succcessful? Y/N?\n";
	// 		std::cin >> Ans;
	// 	}

	// 	if (Ans == 'N' || Ans == 'n')
	// 	{
	// 		index++;
	// 		Decoder.Dictionary_Attack_IOC(index);
	// 		Decoder.GetPlaintext();
	// 	}

	// 	else
	// 	{
	// 		DecryptSuccess = true;
	// 		Decoder.GetPlaintext();
	// 	}
	// }
}