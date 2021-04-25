#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "Crypto5 Classes.h"
#include "Timer Clock.hpp"

using namespace std;


int main()
{
	ifstream in;
	ofstream out;

	Vigenere Decoder;

	Decoder.HT_Stats();

	Decoder.openFiles(in, out);


	string Temp;
	getline(in, Temp);
	Decoder.SetCipherText(Temp);

	Decoder.Start_Cracking();
	Decoder.Sort_IOC();
	Decoder.Cipher_Substrings(Temp);
	//Decoder.Dictionary_Attack_Key();

	//Decoder.GetPlaintext();

	return 0;
}