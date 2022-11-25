# pragma once

#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<memory>
#include<map>

// Typedef for a Vector of String Vectors to be used to implement a hash table with chaining
typedef std::vector<std::string> VectString;

/*

	██╗███╗   ██╗██████╗ ███████╗██╗  ██╗     ██████╗ ███████╗                         
	██║████╗  ██║██╔══██╗██╔════╝╚██╗██╔╝    ██╔═══██╗██╔════╝                         
	██║██╔██╗ ██║██║  ██║█████╗   ╚███╔╝     ██║   ██║█████╗                           
	██║██║╚██╗██║██║  ██║██╔══╝   ██╔██╗     ██║   ██║██╔══╝                           
	██║██║ ╚████║██████╔╝███████╗██╔╝ ██╗    ╚██████╔╝██║                              
	╚═╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝     ╚═════╝ ╚═╝                              
																						
	 ██████╗ ██████╗ ██╗███╗   ██╗ ██████╗██╗██████╗ ███████╗███╗   ██╗ ██████╗███████╗
	██╔════╝██╔═══██╗██║████╗  ██║██╔════╝██║██╔══██╗██╔════╝████╗  ██║██╔════╝██╔════╝
	██║     ██║   ██║██║██╔██╗ ██║██║     ██║██║  ██║█████╗  ██╔██╗ ██║██║     █████╗  
	██║     ██║   ██║██║██║╚██╗██║██║     ██║██║  ██║██╔══╝  ██║╚██╗██║██║     ██╔══╝  
	╚██████╗╚██████╔╝██║██║ ╚████║╚██████╗██║██████╔╝███████╗██║ ╚████║╚██████╗███████╗
	 ╚═════╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝ ╚═════╝╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝╚══════╝
                                                                                

	Description:

		This class implements an object that is used to calculate the Index of Coincidence
		value for either a string to test how likely that string is the English language, 
		or to determine the possible Key Length used to encrypt the cipher text. Objects are 
		pushed on the heap and then deleted once their purpose has been served to improve 
		program run time and faster decryption.
 
	Usage:

		- The IOC value is pivotal to cracking these ciphers
 		- THe higher the IOC value, the more likely something is "English"
		- If a key length of 3 tests as 0.14 and a key length of 9 tests as 0.67
		  then the key length of 9 is more likely to be correct than 3.
		- If a cipher string is shifted by the word "TURING" and the IOC value is 0.53
		  but another cipher string is shifted by the word "ENIGMA" and that IOC value
		  is 0.71, then ENIGMA is more likely to be the key as opposed to "TURING".
 */
                                   
struct Index_Of_Coincidence
{
	int IOC;
	int Size;
	int Sequence_Text_Length;
	std::string CipherText;
	std::string ShiftedText;
	std::vector<std::string> Sequences;

	Index_Of_Coincidence() {
		Size = 16;
		IOC = 2;
		Sequence_Text_Length = 0;
	}

	Index_Of_Coincidence(int Z) {
		Size = 16;
		IOC = Z;
		Sequence_Text_Length = 0;
	}

	friend class CryptoMath;
	friend class Vigenere;
};



/*
 
 ██████╗ ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗ █████╗ ██████╗ ██╗   ██╗
 ██╔══██╗██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔══██╗██╔══██╗╚██╗ ██╔╝
 ██║  ██║██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████║██████╔╝ ╚████╔╝ 
 ██║  ██║██║██║        ██║   ██║██║   ██║██║╚██╗██║██╔══██║██╔══██╗  ╚██╔╝  
 ██████╔╝██║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║██║  ██║██║  ██║   ██║   
 ╚═════╝ ╚═╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   
                                                                            
  █████╗ ████████╗████████╗ █████╗  ██████╗██╗  ██╗                         
 ██╔══██╗╚══██╔══╝╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝                         
 ███████║   ██║      ██║   ███████║██║     █████╔╝                          
 ██╔══██║   ██║      ██║   ██╔══██║██║     ██╔═██╗                          
 ██║  ██║   ██║      ██║   ██║  ██║╚██████╗██║  ██╗                         
 ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝                         
                                                                            

	Description:

		This struct implements a dictionary attack object and is intended to be dynamically
		allocated and then destroyed upon serving its purpose to improve the program run
		time. This class is utilized when the program performs a dictionary attack on the
		key after the program has determined what the key length most likely is. A new object
		will be created with a dictionary word and then it will shift the cipher text according
		to that word. The new cipher string will then have its IOC value evaluated and depending
		on what the score is, it may be pushed on to the results vector. The object is destroyed
		once this is completed.

	Usage:

		- Dictionary Attack the key of the Cipher assuming the key is an English Word
*/

struct Dictionary_Attack
{
	std::string Decrypted;
	std::string Key;
	int Key_Size;

	Dictionary_Attack() {
		Decrypted = "";
	}
};


/*
 
 ██╗   ██╗██╗ ██████╗ ███████╗███╗   ██╗███████╗██████╗ ███████╗
 ██║   ██║██║██╔════╝ ██╔════╝████╗  ██║██╔════╝██╔══██╗██╔════╝
 ██║   ██║██║██║  ███╗█████╗  ██╔██╗ ██║█████╗  ██████╔╝█████╗  
 ╚██╗ ██╔╝██║██║   ██║██╔══╝  ██║╚██╗██║██╔══╝  ██╔══██╗██╔══╝  
  ╚████╔╝ ██║╚██████╔╝███████╗██║ ╚████║███████╗██║  ██║███████╗
   ╚═══╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚══════╝


	Description:

		This class is the main driver for the entire program and this is why
		the Vigenere class is a friend class to every other class so it can 
		access their protected data members. This class essentially keeps track
		of all the things related to the cracking of the cipher text such as the
		testing order of the key length, the hash table lookup, and the final plaintext
		results. 

	Usage:

		- This class creates an object that drives the decryption process
		- The IOC key length is tested 2 - 16
 */

class Vigenere
{
	protected:

		std::string CipherText;
		std::vector<std::string> Plaintext;
		std::string Key;
		float IOC_Value;
		int Key_Length;
		std::vector<float> IOC_Order;
		std::vector<int> Key_Order;
		std::vector<std::string> Narrowed;
		std::map<std::string, int> DictionaryWords;


	public:

		// Default constructor loads the dictionary words
		Vigenere() {
			std::ifstream Fin;
			Fin.open("words.txt");

			while (!Fin.eof()) {
				std::string temp;
				Fin >> temp;
				DictionaryWords[temp] = temp.length();
			}
		}

		friend class CryptoMath;
		friend class Index_Of_Coincidence;
		friend class Dictionary_Attack;
		void openFiles(std::ifstream& infile, std::ofstream& outfile);
		void SetCipherText(std::string CT);
		void Start_Cracking();
		void Calculate_IOC(std::shared_ptr<Index_Of_Coincidence> C, int z);
		void Calculate_IOC(std::string Encrypted);
		void Sort_IOC();
		void Cipher_Substrings(std::string C);
		void Dictionary_Attack_Key();
		void Dictionary_Attack_IOC();
		void Dictionary_Attack_IOC(int num);
		void GetPlaintext();
};



/*
 
  ██████╗██████╗ ██╗   ██╗██████╗ ████████╗ ██████╗       ███╗   ███╗ █████╗ ████████╗██╗  ██╗
 ██╔════╝██╔══██╗╚██╗ ██╔╝██╔══██╗╚══██╔══╝██╔═══██╗      ████╗ ████║██╔══██╗╚══██╔══╝██║  ██║
 ██║     ██████╔╝ ╚████╔╝ ██████╔╝   ██║   ██║   ██║█████╗██╔████╔██║███████║   ██║   ███████║
 ██║     ██╔══██╗  ╚██╔╝  ██╔═══╝    ██║   ██║   ██║╚════╝██║╚██╔╝██║██╔══██║   ██║   ██╔══██║
 ╚██████╗██║  ██║   ██║   ██║        ██║   ╚██████╔╝      ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║
  ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚═╝        ╚═╝    ╚═════╝       ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝


	Description:

		This struct implements an object that is used in tandem with the Index of Coincidence Class
		to determine what the IOC value is. This class creates an object that strictly handles the
		math involved with calculating the Index of Coincidence value. 
		
		The formula to find this is:

		IOC = Sigma/Series (From A to Z) of: ni(ni - 1) / N(N-1)

		where:
				ni = the number of occurences of the letter "i" in the text
				 N = the total number of letters

		reference: https://en.wikipedia.org/wiki/Index_of_coincidence

	Usage:
		- The IOC value is pivotal to cracking these ciphers
		- The higher the IOC value, the more likely something is "English"
		- If a key length of 3 tests as 0.14 and a key length of 9 tests as 0.67
		  then the key length of 9 is more likely to be correct than 3.
		- If a cipher string is shifted by the word "TURING" and the IOC value is 0.53
		  but another cipher string is shifted by the word "ENIGMA" and that IOC value
		  is 0.71, then ENIGMA is more likely to be the key as opposed to "TURING".
 */

struct CryptoMath
{
	std::string Alphabet;
	float Sigma;
	int BigN;
	int Stack_Size;
	int Frequency[26];

	CryptoMath() {
		Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		Sigma = 0;
		BigN = 0;
		Stack_Size = 0;
		
		for (int i = 0; i < 26; i++) {
			Frequency[i] = 0;
		}
	}

	friend class Vigenere;
	friend class Index_Of_Coincidence;
};



/*
***************************************************************************************************
 
  ██████╗██╗      █████╗ ███████╗███████╗                     
 ██╔════╝██║     ██╔══██╗██╔════╝██╔════╝                     
 ██║     ██║     ███████║███████╗███████╗                     
 ██║     ██║     ██╔══██║╚════██║╚════██║                     
 ╚██████╗███████╗██║  ██║███████║███████║                     
  ╚═════╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝                     
                                                              
 ███╗   ███╗███████╗████████╗██╗  ██╗ ██████╗ ██████╗ ███████╗
 ████╗ ████║██╔════╝╚══██╔══╝██║  ██║██╔═══██╗██╔══██╗██╔════╝
 ██╔████╔██║█████╗     ██║   ███████║██║   ██║██║  ██║███████╗
 ██║╚██╔╝██║██╔══╝     ██║   ██╔══██║██║   ██║██║  ██║╚════██║
 ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝██████╔╝███████║
 ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝


	Public Method void: openFiles

	Description:

		Requests the name of the file that holds the encrypted message
		and an outfile destination file to eventually write the result to.
 */

void Vigenere::openFiles(std::ifstream& infile, std::ofstream& outfile)
{
	char inFileName[40];
	char outFileName[40];

	std::cout << "Enter the input file name: ";
	std::cin >> inFileName;

	// open input file
	infile.open(inFileName);
	std::cout << "Enter the output file name: ";
	std::cin >> outFileName;

	// Open output file.
	outfile.open(outFileName);
}



/*
	Public Method void: SetCipherText

	Description:

		Setter method to set the Ciphertext variable that needs
		to be decrypted. 
 */

void Vigenere::SetCipherText(std::string CT)
{
	this->CipherText = CT;

	if (CT[CT.back()] != 32) {
		this->CipherText += "";
	}
}


/*
	Public Method void: Start_Cracking

	Description:

		This method is responsible for testing all of the different possible
		key lengths of the key that the cipher text was encrypted with. For this
		program, we are testing a key length of 2 all the way to a potential key
		length of 16. For each possible key length that is being tested, a new
		index of coincidence object is dynamically created to handle the testing 
		process. The testing calculates the I.O.C value of a key length whcih involves 
		splitting the cipher text into sequences according to the key length. If a key
		length is 2, we turn the cipher text into two sequences, alternating every other
		character and then these are stored in a vector and sent to the Calculate IOC
		method. After that method call is complete, the loop iterates, and the next
		possible key length is tested.
 */

void Vigenere::Start_Cracking()
{
	this->IOC_Order.resize(18);

	for (int z = 2; z < 17; z++)					// Looping through key lengths of 2 - 16
	{
		std::shared_ptr<Index_Of_Coincidence> Cracking (new Index_Of_Coincidence(z));
		int Text_Length = this->CipherText.length();

		std::string TCT;							// TCT = Temp Cipher Text

		int KL = Cracking->IOC;						// KL = Key Length


		for (int i = 0; i < Text_Length; i++)
		{
			// Ignoring spaces and leaving them in place
			if (int(this->CipherText[i]) > 64 && int(this->CipherText[i]) < 91)
			{
				TCT += this->CipherText[i];
			}
		}


		for (int j = 0; j < Cracking->IOC; j++)
		{
			int RT = j;								// Running Total
			std::string Temp = "";

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

/*
	Public Method void: Calculate_IOC

	Description:

		Method is directly called from the Start_Cracking method and receives a
		index of coincidence object pointer as well as an integer to reference which
		key length is being tested. A separate object is also dynamically created, a
		CryptoMath object, to assist with the math involved in calculating the IOC.
		This mainly involves counting the instances of letters occuring more than once
		in the Sequences vector that we created from the last method. This eventually
		results in an Index of Coincidence value such as something like: 0.048. Once 
		completed, the IOC value is written to the Vigenere Class and the helper objects
		are destroyed to free up the memory.

		For more information on the math involved in calculating the index of coincidence,
		please see the following references:

			- https://en.wikipedia.org/wiki/Index_of_coincidence
			- https://www.dcode.fr/index-coincidence
			- http://practicalcryptography.com/cryptanalysis/text-characterisation/index-coincidence/
 */

void Vigenere::Calculate_IOC(std::shared_ptr<Index_Of_Coincidence> C, int z)
{
	std::shared_ptr<CryptoMath> Summation (new CryptoMath());

	float Final_IOC = 0;

	Summation->Stack_Size = C->Sequences.size();

	for (int i = 0; i < Summation->Stack_Size; i++)
	{
		std::string Temp = C->Sequences[i];

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

	this->IOC_Order[z] = Final_IOC;
}


void Vigenere::Cipher_Substrings(std::string C)
{
	std::string Cipher_Substring;
	std::vector<std::string> Slices;
	int S_Count = 0;
	int E_Count = 0;

	for (int i = 0; i < C.length(); i++)
	{
		if (int(C[i]) > 64 && int(C[i]) < 91) {
			Cipher_Substring += C[i];
		}

		else {
			Slices.push_back(Cipher_Substring);
			Cipher_Substring = "";
		}

	}


	for (int j = 0; j < Slices.size(); j++)
	{
		std::string T = Slices[j];

		if (Slices[j] == "" || Slices[j] == " ") {
			Slices.erase(Slices.begin() + j);
		}
	}

	Slices.shrink_to_fit();

	for (int k = 0; k < Slices.size(); k++)
	{
		bool isEnglish = false;

		if (this->DictionaryWords.find(Slices[k]) != this->DictionaryWords.end())
		{
			isEnglish = true;
		}

		if (isEnglish) {
			E_Count++;
		}
	}

	S_Count = Slices.size();

	if (S_Count == E_Count)
	{
		Plaintext.push_back(C);
	}

}


/*
	Public Method void: Calculate_IOC (overloaded method)

	Description:

		Method is nearly identical to the other method of the same name except that
		this method accepts only a single string to check the IOC value of. This is 
		used to check how likely a string is to being the correct decrypted result
		during the dictionary attack process. Like the other method, a separate object
		is also dynamically created, a CryptoMath object, to assist with the math involved 
		in calculating the IOC.This mainly involves counting the instances of letters 
		occuring more than once in the Sequences vector that we created from the last method. 
		This eventually results in an Index of Coincidence value such as something like: 0.048. 
		Once completed, the IOC value is written to the Vigenere Class and the helper objects
		are destroyed to free up the memory.

		For more information on the math involved in calculating the index of coincidence,
		please see the following references:

			- https://en.wikipedia.org/wiki/Index_of_coincidence
			- https://www.dcode.fr/index-coincidence
			- http://practicalcryptography.com/cryptanalysis/text-characterisation/index-coincidence/
 */

void Vigenere::Calculate_IOC(std::string Encrypted)
{
	std::shared_ptr<CryptoMath> Summation (new CryptoMath());

	float Final_IOC = 0.0;

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

	if (Final_IOC > IOC_Value)
	{
		std::cout << "Pushing vector, IOC Value: " << std::setprecision(4) << Final_IOC << "\n";
		this->IOC_Value = Final_IOC;
		this->Plaintext.push_back(Encrypted);
	}
}



/*
	Public Method void: Sort_IOC

	Description:

		Finding the highest I.O.C value and its corresponding key length and
		loading them into a vector that we will use for testing. This will determine
		which key lengths are tested first as the highest value I.O.C is most likely
		the Key Length needed to crack the cipher.
 */

void Vigenere::Sort_IOC()
{
	for (int z = 0; z < this->IOC_Order.size(); z++)
	{
		float highest = this->IOC_Order[0];

		for (int j = 0; j < 18; j++)
		{
			if (IOC_Order[j] > highest)
			{
				highest = this->IOC_Order[j];

				this->Key_Length = j;
			}
		}

		this->Key_Order.push_back(Key_Length);
		this->IOC_Order[Key_Length] = 0;
	}

	std::cout << "\n\nBased on the IOC Freqency Analysis, the most likely key length is: " 
				<< this->Key_Order[0] << "\n\n";

	std::cout << "The test order of the keys is as follows: ";

	for (int k = 0; k < this->Key_Order.size(); k++)
	{
		std::cout << this->Key_Order[k] << " ";
	}

	std::cout << "\n";

	this->Key_Length = this->Key_Order[0];
}


/*
	Public Method void: Dictionary_Attack_IOC

	Description:

		Method is responsible for utilizing the results of the most likely key
		lengths, and eventually performing a dictionary attack on the cipher.
		This is of course assuming that the key that was used to encrypt the cipher
		is a dictionary word. The method will dynamically create a dictionary object
		and the vigenere key length variable is referenced as to what key length is
		being tested. A vector of words from the dictionary that are equal to the key
		length we are testing is created and this helps us eliminate the majority of
		the dictionary words and limit it to only words that are of the key length.
		Once this is completed, the method will brute force every shift combination
		of this narrowed list of dictionary words and pass the result to the overloaded
		Calculate_IOC method and determine the result. This process is handled by creating
		a dynamic Dictionary Attack object for each shift combination. Once the work is
		complete, the object is destroyed. There is more work that is performed in the
		Calculate IOC method to ensure we come up with the correct result. Once the process
		is finished, the objects are deleted to free up the stack memory.
 */

void Vigenere::Dictionary_Attack_IOC()
{

	for (auto word : DictionaryWords) {
		if (word.second == this->Key_Length) {
			Narrowed.push_back(word.first);
		}
	}

	std::cout << "Narrowed dictionary is size: " << Narrowed.size() << "\n";

	for (int k = 0; k < Narrowed.size(); k++)
	{
		std::shared_ptr<Dictionary_Attack> D (new Dictionary_Attack());

		D->Key = Narrowed[k];

		int j = 0;

		for (int l = 0; l < this->CipherText.length(); l++)
		{

			if (j == D->Key.length()) {
				j = 0;
			}

			if (int(this->CipherText[l]) != 32) {
				int Temp = this->CipherText[l] - D->Key[j];

				if (Temp < 0) {
					Temp += 26;
				}

				else {
					Temp %= 26;
				}

				Temp += 65;

				D->Decrypted += Temp;
				j++;
			}

			else {
				D->Decrypted += this->CipherText[l];
			}

		}

		Calculate_IOC(D->Decrypted);
	}
}



/*
	Public Method void: Get_Plaintext

	Description:

		Method returns the plaintext result of the dictionary attack process
		that we hope is the decrypted result. The method grabs the last result
		pushed to the vector which with the way it is formatted, the last result
		pushed to the vector should be the best IOC score and the most "English-like."
		Therefore this result should correspond to the decrypted result. There is also
		code available to cout other results if we want to give a top results.
 */

void Vigenere::GetPlaintext()
{
	int i = (this->Plaintext.size() - 1);
	std::cout << "\nEncrypted Text of: \n" << this->CipherText << "\n\nbecomes\n\n";
	std::cout << this->Plaintext[i] << "\n\n";
}