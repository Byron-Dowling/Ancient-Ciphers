#include "Crypto5 Classes.h"
#include <iomanip>

using namespace std;

void Vigenere::openFiles(ifstream& infile, ofstream& outfile)
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


void Vigenere::SetCipherText(string CT)
{
	CipherText = CT;

	if (CT[CT.back()] != 32)
	{
		CipherText += "";
	}
}


void Vigenere::HT_Stats()
{
	Dictionary_Lookup.BuildTable();
	Dictionary_Lookup.Stats();

	cout << "Longest Chain: " << Dictionary_Lookup.LongestChain() << endl;
	cout << "Average Chain: " << Dictionary_Lookup.AverageChain() << endl;
	cout << "Empty Slots: " << Dictionary_Lookup.Empties() << endl;
	cout << "Load Factor: " << Dictionary_Lookup.LoadFactor() << endl << endl;
}


void Vigenere::Start_Cracking()
{
	IOC_Order.resize(18);

	for (int z = 2; z < 17; z++)			// Looping through key lengths of 2 - 16
	{
		Index_Of_Coincidence* Cracking = new Index_Of_Coincidence(z);
		int Text_Length = CipherText.length();

		string TCT;							// TCT = Temp Cipher Text

		int KL = Cracking->IOC;				// KL = Key Length


		for (int i = 0; i < Text_Length; i++)
		{
			if (int(CipherText[i]) > 64 && int(CipherText[i]) < 91)	// Ignoring spaces and leaving them in place
			{
				TCT += CipherText[i];
			}
		}


		for (int j = 0; j < Cracking->IOC; j++)
		{
			int RT = j;						// Running Total
			string Temp = "";

			for (int k = 0; k < TCT.length(); k++)
			{
				if (RT < TCT.length())
				{
					Temp += TCT[RT];
				}

				RT = RT + KL;
			}

			Cracking->Sequences.push_back(Temp);
		}

		Calculate_IOC(Cracking, z);

	}
}


void Vigenere::Calculate_IOC(Index_Of_Coincidence* C, int z)
{
	CryptoMath* Summation = new CryptoMath;

	float Final_IOC = 0;

	Summation->Stack_Size = C->Sequences.size();

	for (int i = 0; i < Summation->Stack_Size; i++)
	{
		string Temp = C->Sequences[i];

		Summation->BigN = Temp.length();

		for (int j = 0; j < Temp.length(); j++)
		{
			for (int k = 0; k < 26; k++)
			{
				if (Temp[j] == Summation->Alphabet[k])
				{
					Summation->Frequency[k] = (Summation->Frequency[k] + 1);
				}

			}
		}


		float Temp_IOC = 0, small_n = 0, Num = 0, Denom = 0, Result = 0;


		for (int m = 0; m < 26; m++)
		{
			small_n = Summation->Frequency[m];

			Num = (small_n * (small_n - 1));
			Denom = (Summation->BigN * (Summation->BigN - 1));

			Temp_IOC = (Num / Denom);

			Result += Temp_IOC;
		}

		Final_IOC += Result;

		for (int n = 0; n < 26; n++)
		{
			Summation->Frequency[n] = 0;
		}
	}

	Final_IOC = Final_IOC / Summation->Stack_Size;

	C->IOC = Final_IOC;

	IOC_Order[z] = Final_IOC;

	delete Summation;
	delete C;
}


void Vigenere::Calculate_IOC(string Encrypted)
{
	CryptoMath* Summation = new CryptoMath;

	float Final_IOC = 0;

	Summation->BigN = Encrypted.length();
	Summation->Stack_Size = 1;

	for (int j = 0; j < Encrypted.length(); j++)
	{
		for (int k = 0; k < 26; k++)
		{
			if (Encrypted[j] == Summation->Alphabet[k])
			{
				Summation->Frequency[k] = (Summation->Frequency[k] + 1);
			}

		}
	}


	float Temp_IOC = 0, small_n = 0, Num = 0, Denom = 0, Result = 0;


	for (int m = 0; m < 26; m++)
	{
		small_n = Summation->Frequency[m];

		Num = (small_n * (small_n - 1));
		Denom = (Summation->BigN * (Summation->BigN - 1));

		Temp_IOC = (Num / Denom);

		Result += Temp_IOC;
	}

	Final_IOC += Result;

	Final_IOC = Final_IOC / Summation->Stack_Size;

	//cout << "Final IOC is: " << setprecision(3) << Final_IOC << endl;

	if (Final_IOC > IOC_Value)
	{
		cout << "Pushing vector, IOC Value: " << setprecision(4) << Final_IOC << endl;
		IOC_Value = Final_IOC;
		Plaintext.push_back(Encrypted);
	}

	delete Summation;
}


void Vigenere::Sort_IOC()
{
	/* 
		Finding the highest I.O.C value and its corresponding key length and
		loading them into a vector that we will use for testing. This will determine
		which key lengths are tested first as the highest value I.O.C is most likely
		the Key Length needed to crack the cipher.
	*/


	for (int z = 0; z < IOC_Order.size(); z++)
	{
		float highest = IOC_Order[0];

		for (int j = 0; j < 18; j++)
		{
			if (IOC_Order[j] > highest)
			{
				highest = IOC_Order[j];

				Key_Length = j;
			}
		}

		Key_Order.push_back(Key_Length);

		IOC_Order[Key_Length] = 0;
	}

	cout << "\n\nBased on the IOC Freqency Analysis, the most likely key length is: " << Key_Order[0] << endl << endl;

	cout << "The test order of the keys is as follows: ";

	for (int k = 0; k < Key_Order.size(); k++)
	{
		cout << Key_Order[k] << " ";
	}

	cout << endl;

	Key_Length = Key_Order[0];		// Setting initial Key Length to most probably result
}


void Vigenere::Cipher_Substrings(string C)
{
	string Cipher_Substring;
	vector<string> Slices;
	int S_Count = 0;
	int E_Count = 0;

	for (int i = 0; i < C.length(); i++)
	{
		if (int(C[i]) > 64 && int(C[i]) < 91)
		{
			Cipher_Substring += C[i];
		}

		else
		{
			Slices.push_back(Cipher_Substring);
			Cipher_Substring = "";
		}

	}

	//cout << "Slices size is " << Slices.size() << endl;

	for (int j = 0; j < Slices.size(); j++)
	{
		string T = Slices[j];
		if (Slices[j] == "" || Slices[j] == " ")
		{
			Slices.erase(Slices.begin() + j);
		}
	}

	Slices.shrink_to_fit();

	//cout << "Slices size is " << Slices.size() << endl;

	for (int k = 0; k < Slices.size(); k++)
	{
		bool English = false;

		//cout << Slices[k] << " ";

		English = Dictionary_Lookup.Search(Slices[k]);

		//cout << endl;

		// issue with mismatch of cipher strings and strings checked
		if (English == true)
		{
			E_Count++;
		}

	}

	S_Count = Slices.size();

	if (S_Count == E_Count)
	{
		Plaintext.push_back(C);
	}

}



void Vigenere::Dictionary_Attack_Key()
{
	Dictionary* List = new Dictionary;

	for (int i = 0; i < Key_Order.size(); i++)
	{
		for (int j = 0; j < List->Words.size(); j++)
		{
			if (List->Words[j].length() == Key_Order[i])
			{
				Narrowed.push_back(List->Words[j]);
			}
		}

		for (int k = 0; k < Narrowed.size(); k++)
		{
			Dictionary_Attack* D = new Dictionary_Attack;

			D->Key = Narrowed[k];

			int j = 0;

			for (int l = 0; l < CipherText.length(); l++)
			{

				if (j == D->Key.length())
				{
					j = 0;
				}

				if (int(CipherText[l]) != 32)
				{
					int Temp = CipherText[l] - D->Key[j];

					if (Temp < 0)
					{
						Temp += 26;
					}

					else
					{
						Temp %= 26;
					}

					Temp += 65;

					D->Decrypted += Temp;
					j++;
				}

				else
				{
					D->Decrypted += CipherText[l];
				}

			}

			Cipher_Substrings(D->Decrypted);

			delete D;
		}
	}

	delete List;
}



void Vigenere::Dictionary_Attack_IOC()
{
	Dictionary* List = new Dictionary;

	for (int j = 0; j < List->Words.size(); j++)
	{
		if (List->Words[j].length() == Key_Length)
		{
			Narrowed.push_back(List->Words[j]);
		}
	}

	for (int k = 0; k < Narrowed.size(); k++)
	{
		Dictionary_Attack* D = new Dictionary_Attack;

		D->Key = Narrowed[k];

		int j = 0;

		for (int l = 0; l < CipherText.length(); l++)
		{

			if (j == D->Key.length())
			{
				j = 0;
			}

			if (int(CipherText[l]) != 32)
			{
				int Temp = CipherText[l] - D->Key[j];

				if (Temp < 0)
				{
					Temp += 26;
				}

				else
				{
					Temp %= 26;
				}

				Temp += 65;

				D->Decrypted += Temp;
				j++;
			}

			else
			{
				D->Decrypted += CipherText[l];
			}

		}

		Calculate_IOC(D->Decrypted);

		delete D;
	}

	delete List;
}



void Vigenere::GetPlaintext()
{
	int i = Plaintext.size();
	cout << endl << "Encrypted Text of: " << endl << CipherText << endl << endl << "becomes" << endl << endl;

	cout << Plaintext[i - 1] << endl;
	//for (int i = 0; i < Plaintext.size(); i++)
	//{
	//	cout << Plaintext[i] << endl << endl;
	//}

	cout << endl;
}


void HashTable::BuildTable()
{
	for (int i = 0; i < Lookup.Words.size(); i++)
	{
		string Temp = Lookup.Words[i];
		int T;
		T = H1.ELFHash(Temp) % TableSize;

		HT[T].push_back(Temp);
		Count++;
	}
}


double HashTable::LoadFactor()
{
	return (double)Count / (double)TableSize;
}


void HashTable::Stats()
{
	for (int i = 0; i < TableSize; i++) 
	{
		if (HT[i].size() > maxChainLength) 
		{
			maxChainLength = HT[i].size();
		}

		if (HT[i].size() == 0) 
		{
			numEmptySlots++;
		}

		else 
		{
			avgChainLength += HT[i].size();
		}
	}

	avgChainLength /= (double)TableSize - (double)numEmptySlots;
}


int HashTable::LongestChain() 
{
	return maxChainLength;
}


int HashTable::Empties() 
{
	return numEmptySlots;
}


double HashTable::AverageChain() 
{
	return avgChainLength;
}


bool HashTable::Search(string word)
{
	int Passed_Key = H1.ELFHash(word) % TableSize;

	if (!HT[Passed_Key].empty())
	{
		for (int i = 0; i < HT[Passed_Key].size(); i++)
		{
			if (HT[Passed_Key][i] == word)
			{
				//cout << "Word is English!";
				return true;
			}
		}
	}

	return false;
}