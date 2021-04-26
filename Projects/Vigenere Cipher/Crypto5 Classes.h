# pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include"Hash.hpp"


using namespace std;

typedef vector<string> VectString;

/*

 $$$$$$\                 $$\                                      $$$$$$\
 \_$$  _|                $$ |                                    $$  __$$\
   $$ |  $$$$$$$\   $$$$$$$ | $$$$$$\  $$\   $$\        $$$$$$\  $$ /  \__|
   $$ |  $$  __$$\ $$  __$$ |$$  __$$\ \$$\ $$  |      $$  __$$\ $$$$\
   $$ |  $$ |  $$ |$$ /  $$ |$$$$$$$$ | \$$$$  /       $$ /  $$ |$$  _|
   $$ |  $$ |  $$ |$$ |  $$ |$$   ____| $$  $$<        $$ |  $$ |$$ |
 $$$$$$\ $$ |  $$ |\$$$$$$$ |\$$$$$$$\ $$  /\$$\       \$$$$$$  |$$ |
 \______|\__|  \__| \_______| \_______|\__/  \__|       \______/ \__|



  $$$$$$\            $$\                     $$\       $$\
 $$  __$$\           \__|                    \__|      $$ |
 $$ /  \__| $$$$$$\  $$\ $$$$$$$\   $$$$$$$\ $$\  $$$$$$$ | $$$$$$\  $$$$$$$\   $$$$$$$\  $$$$$$\
 $$ |      $$  __$$\ $$ |$$  __$$\ $$  _____|$$ |$$  __$$ |$$  __$$\ $$  __$$\ $$  _____|$$  __$$\
 $$ |      $$ /  $$ |$$ |$$ |  $$ |$$ /      $$ |$$ /  $$ |$$$$$$$$ |$$ |  $$ |$$ /      $$$$$$$$ |
 $$ |  $$\ $$ |  $$ |$$ |$$ |  $$ |$$ |      $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$ |      $$   ____|
 \$$$$$$  |\$$$$$$  |$$ |$$ |  $$ |\$$$$$$$\ $$ |\$$$$$$$ |\$$$$$$$\ $$ |  $$ |\$$$$$$$\ \$$$$$$$\
  \______/  \______/ \__|\__|  \__| \_______|\__| \_______| \_______|\__|  \__| \_______| \_______|

*/
                                   
class Index_Of_Coincidence
{
protected:
	int IOC;
	int Size;
	int Sequence_Text_Length;
	string CipherText;
	string ShiftedText;
	vector<string> Sequences;

public:
	Index_Of_Coincidence()
	{
		Size = 16;
		IOC = 2;
		Sequence_Text_Length = 0;
	}

	Index_Of_Coincidence(int Z)
	{
		Size = 16;
		IOC = Z;
		Sequence_Text_Length = 0;
	}

	friend class CryptoMath;
	friend class Vigenere;
};


/*

 $$$$$$$\  $$\             $$\     $$\
 $$  __$$\ \__|            $$ |    \__|
 $$ |  $$ |$$\  $$$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$\  $$\   $$\
 $$ |  $$ |$$ |$$  _____|\_$$  _|  $$ |$$  __$$\ $$  __$$\  \____$$\ $$  __$$\ $$ |  $$ |
 $$ |  $$ |$$ |$$ /        $$ |    $$ |$$ /  $$ |$$ |  $$ | $$$$$$$ |$$ |  \__|$$ |  $$ |
 $$ |  $$ |$$ |$$ |        $$ |$$\ $$ |$$ |  $$ |$$ |  $$ |$$  __$$ |$$ |      $$ |  $$ |
 $$$$$$$  |$$ |\$$$$$$$\   \$$$$  |$$ |\$$$$$$  |$$ |  $$ |\$$$$$$$ |$$ |      \$$$$$$$ |
 \_______/ \__| \_______|   \____/ \__| \______/ \__|  \__| \_______|\__|       \____$$ |
									       $$\   $$ |
        								       \$$$$$$  |
										\______/
*/

class Dictionary
{
	ifstream input;
	int count;
	vector<string> Words;
	vector<int> Used;

public:

	Dictionary()
	{
		string Temp;
		count = 0;

		input.open("Words.txt");

		while (!input.eof())
		{
			input >> Temp;
			Words.push_back(Temp);
			Used.push_back(0);
			count++;
		}
	}

	friend class HashTable;
	friend class Vigenere;
};


/*

 $$\   $$\                     $$\             $$$$$$$$\        $$\       $$\
 $$ |  $$ |                    $$ |            \__$$  __|       $$ |      $$ |
 $$ |  $$ | $$$$$$\   $$$$$$$\ $$$$$$$\           $$ | $$$$$$\  $$$$$$$\  $$ | $$$$$$\
 $$$$$$$$ | \____$$\ $$  _____|$$  __$$\          $$ | \____$$\ $$  __$$\ $$ |$$  __$$\
 $$  __$$ | $$$$$$$ |\$$$$$$\  $$ |  $$ |         $$ | $$$$$$$ |$$ |  $$ |$$ |$$$$$$$$ |
 $$ |  $$ |$$  __$$ | \____$$\ $$ |  $$ |         $$ |$$  __$$ |$$ |  $$ |$$ |$$   ____|
 $$ |  $$ |\$$$$$$$ |$$$$$$$  |$$ |  $$ |         $$ |\$$$$$$$ |$$$$$$$  |$$ |\$$$$$$$\
 \__|  \__| \_______|\_______/ \__|  \__|         \__| \_______|\_______/ \__| \_______|

*/

class HashTable
{
	vector<VectString> HT;
	Dictionary Lookup;
	int TableSize;
	int Count;
	Hash H1;
	int maxChainLength;
	int avgChainLength;
	int numEmptySlots;

public:
	HashTable()
	{
		TableSize = 168451;		// Prime Number with an appropriate load factor relative to the 
								// size of our data and not near a power of two.
		HT.resize(TableSize);
		maxChainLength = 0;
		avgChainLength = 0;
		numEmptySlots = 0;
		Count = 0;
	}

	void BuildTable();
	void Stats();
	double LoadFactor();
	int LongestChain();
	int Empties();
	double AverageChain();
	bool Search(string word);
	friend class Dictionary;
	friend class Vigenere;
};


/*

 $$$$$$$\  $$\             $$\     $$\
 $$  __$$\ \__|            $$ |    \__|
 $$ |  $$ |$$\  $$$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$\  $$\   $$\
 $$ |  $$ |$$ |$$  _____|\_$$  _|  $$ |$$  __$$\ $$  __$$\  \____$$\ $$  __$$\ $$ |  $$ |
 $$ |  $$ |$$ |$$ /        $$ |    $$ |$$ /  $$ |$$ |  $$ | $$$$$$$ |$$ |  \__|$$ |  $$ |
 $$ |  $$ |$$ |$$ |        $$ |$$\ $$ |$$ |  $$ |$$ |  $$ |$$  __$$ |$$ |      $$ |  $$ |
 $$$$$$$  |$$ |\$$$$$$$\   \$$$$  |$$ |\$$$$$$  |$$ |  $$ |\$$$$$$$ |$$ |      \$$$$$$$ |
 \_______/ \__| \_______|   \____/ \__| \______/ \__|  \__| \_______|\__|       \____$$ |
       									       $$\   $$ |
								      	       \$$$$$$  |
										\______/
  $$$$$$\    $$\     $$\                         $$\
 $$  __$$\   $$ |    $$ |                        $$ |
 $$ /  $$ |$$$$$$\ $$$$$$\    $$$$$$\   $$$$$$$\ $$ |  $$\
 $$$$$$$$ |\_$$  _|\_$$  _|   \____$$\ $$  _____|$$ | $$  |
 $$  __$$ |  $$ |    $$ |     $$$$$$$ |$$ /      $$$$$$  /
 $$ |  $$ |  $$ |$$\ $$ |$$\ $$  __$$ |$$ |      $$  _$$<
 $$ |  $$ |  \$$$$  |\$$$$  |\$$$$$$$ |\$$$$$$$\ $$ | \$$\
 \__|  \__|   \____/  \____/  \_______| \_______|\__|  \__|

*/

class Dictionary_Attack
{
protected:
	string Decrypted;
	string Key;
	int Key_Size;

public:

	Dictionary_Attack()
	{
		Decrypted = "";
	}

	friend class Vigenere;
};



/*
 $$\    $$\ $$\
 $$ |   $$ |\__|
 $$ |   $$ |$$\  $$$$$$\   $$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\
 \$$\  $$  |$$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\
  \$$\$$  / $$ |$$ /  $$ |$$$$$$$$ |$$ |  $$ |$$$$$$$$ |$$ |  \__|$$$$$$$$ |
   \$$$  /  $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$   ____|$$ |      $$   ____|
    \$  /   $$ |\$$$$$$$ |\$$$$$$$\ $$ |  $$ |\$$$$$$$\ $$ |      \$$$$$$$\
     \_/    \__| \____$$ | \_______|\__|  \__| \_______|\__|       \_______|
		$$\   $$ |
		\$$$$$$  |
		 \______/
 */

class Vigenere
{
protected:
	string CipherText;
	vector<string> Plaintext;
	string Key;
	float IOC_Value;
	int Key_Length;		// Between 2-16
	vector<float> IOC_Order;
	vector<int> Key_Order;
	vector<string> Narrowed;
	HashTable Dictionary_Lookup;


public:
	friend class CryptoMath;
	friend class Index_Of_Coincidence;
	friend class Dictionary_Attack;
	friend class HashTable;
	friend class Dictionary;
	void openFiles(ifstream& infile, ofstream& outfile);
	void SetCipherText(string CT);
	void Start_Cracking();
	void Calculate_IOC(Index_Of_Coincidence* C, int z);
	void Calculate_IOC(string Encrypted);
	void Sort_IOC();
	void Cipher_Substrings(string C);
	void Dictionary_Attack_Key();
	void Dictionary_Attack_IOC();
	void GetPlaintext();
	void HT_Stats();
};



/*

  $$$$$$\                                 $$\                       $$\      $$\            $$\     $$\
 $$  __$$\                                $$ |                      $$$\    $$$ |           $$ |    $$ |
 $$ /  \__| $$$$$$\  $$\   $$\  $$$$$$\ $$$$$$\    $$$$$$\          $$$$\  $$$$ | $$$$$$\ $$$$$$\   $$$$$$$\
 $$ |      $$  __$$\ $$ |  $$ |$$  __$$\\_$$  _|  $$  __$$\ $$$$$$\ $$\$$\$$ $$ | \____$$\\_$$  _|  $$  __$$\
 $$ |      $$ |  \__|$$ |  $$ |$$ /  $$ | $$ |    $$ /  $$ |\______|$$ \$$$  $$ | $$$$$$$ | $$ |    $$ |  $$ |
 $$ |  $$\ $$ |      $$ |  $$ |$$ |  $$ | $$ |$$\ $$ |  $$ |        $$ |\$  /$$ |$$  __$$ | $$ |$$\ $$ |  $$ |
 \$$$$$$  |$$ |      \$$$$$$$ |$$$$$$$  | \$$$$  |\$$$$$$  |        $$ | \_/ $$ |\$$$$$$$ | \$$$$  |$$ |  $$ |
  \______/ \__|       \____$$ |$$  ____/   \____/  \______/         \__|     \__| \_______|  \____/ \__|  \__|
	 	     $$\   $$ |$$ |
 		     \$$$$$$  |$$ |
		      \______/ \__|

 */

class CryptoMath
{
protected:
	string Alphabet;
	float Sigma;
	int BigN;
	int Stack_Size;
	int Frequency[26];

public:

	CryptoMath()
	{
		Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		Sigma = 0;
		BigN = 0;
		Stack_Size = 0;
		
		for (int i = 0; i < 26; i++)
		{
			Frequency[i] = 0;
		}
	}

	friend class Vigenere;
	friend class Index_Of_Coincidence;
};
