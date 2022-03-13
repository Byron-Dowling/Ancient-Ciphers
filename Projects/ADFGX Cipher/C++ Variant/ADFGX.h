#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Typedef for a Vector of String Vectors
typedef vector<string> VectString;


/*

  $$$$$$\  $$$$$$$\  $$$$$$$$\  $$$$$$\  $$\   $$\       $$\                          $$\
 $$  __$$\ $$  __$$\ $$  _____|$$  __$$\ $$ |  $$ |      $$ |                         $$ |
 $$ /  $$ |$$ |  $$ |$$ |      $$ /  \__|\$$\ $$  |      $$ |      $$$$$$\   $$$$$$\  $$ |  $$\ $$\   $$\  $$$$$$\
 $$$$$$$$ |$$ |  $$ |$$$$$\    $$ |$$$$\  \$$$$  /       $$ |     $$  __$$\ $$  __$$\ $$ | $$  |$$ |  $$ |$$  __$$\
 $$  __$$ |$$ |  $$ |$$  __|   $$ |\_$$ | $$  $$<        $$ |     $$ /  $$ |$$ /  $$ |$$$$$$  / $$ |  $$ |$$ /  $$ |
 $$ |  $$ |$$ |  $$ |$$ |      $$ |  $$ |$$  /\$$\       $$ |     $$ |  $$ |$$ |  $$ |$$  _$$<  $$ |  $$ |$$ |  $$ |
 $$ |  $$ |$$$$$$$  |$$ |      \$$$$$$  |$$ /  $$ |      $$$$$$$$\\$$$$$$  |\$$$$$$  |$$ | \$$\ \$$$$$$  |$$$$$$$  |
 \__|  \__|\_______/ \__|       \______/ \__|  \__|      \________|\______/  \______/ \__|  \__| \______/ $$  ____/
                                                                                                          $$ |
                                                                                                          $$ |
                                                                                                          \__|
*/
class AdfgxLookup
{
protected:
	int row = 6;
	int col = 6;
	int longest_column;
	string PS[6][6];
	vector<VectString> CT_Matrix;
	vector<VectString> Dis_Matrix;
	string KeyWord1;
	string KeyWord2;
	string Message;
	string PS_Encrypt;
	string Encrypted;
	string Decrypted;
	string Operation;

public:
	void Encode_PS_KW1();
	void Build_PS();
	void Set_KW1_PS(string KW1);
	void Set_KW2_PS(string KW2);
	void Encrypt_String(string M);
	void Encode_PS_KW2();
	void Discombobulate();
	void Print_PS();
	void Print_Message();
};


/*
	Public Method void: Set_KW1_PS

	Description:
		Setter method that receives a string and updates the first keyword that
		is used to encrypt the plaintext message.

	Params:
		- string KW1

	Returns:
		- None
 */

void AdfgxLookup::Set_KW1_PS(string KW1)
{
	KeyWord1 = KW1;
}



/*
	Public Method void: Set_KW2_PS

	Description:
		Setter method that receives a string and updates the second keyword that
		is used to encrypt the plaintext message.

	Params:
		- string KW2

	Returns:
		- None
 */

void AdfgxLookup::Set_KW2_PS(string KW2)
{
	KeyWord2 = KW2;
}



/*
	Public Method void: Build_PS

	Description:
		This method will build the polybius square that is key to encrypting the
		plaintext message using the standard alphabet. Further updates will occur
		afterwards.

	Params:
		- None

	Returns:
		- None
 */

void AdfgxLookup::Build_PS()
{
	char alphabet[] = "abcdefghiklmnopqrstuvwxyz"; // Omitting J for ADFGX Cipher/ Polybius Square


	int k = 0;

	PS[0][0] = "_";
	PS[0][1] = PS[1][0] = "A";
	PS[0][2] = PS[2][0] = "D";
	PS[0][3] = PS[3][0] = "F";
	PS[0][4] = PS[4][0] = "G";
	PS[0][5] = PS[5][0] = "X";

	for (int i = 1; i < col; i++)
	{
		for (int j = 1; j < row; j++)
		{
			PS[i][j] = alphabet[k];
			k++;
		}
	}

}



/*
	Public Method void: Encode_PS_KW1

	Description:
		This method builds the string that is read into the updated Polybius Square.
		It will take Keyword 1 and remove any duplicate letters from KW1 and then
		eliminate those letters from the alphabet string (excluding J which is already
		ommitted). Once we arrive at our simplified KW1 and reduced alphabet, the results
		are joined into one string which is then read back into the Polybius Sqare. This is
		important as it is the basis for how the plaintext message will be encrypted.

	Params:
		- None

	Returns:
		- None
 */

void AdfgxLookup::Encode_PS_KW1()
{
	string Alphabet_PS = "abcdefghiklmnopqrstuvwxyz"; // Omitting J for ADFGX Cipher/ Polybius Square
	int i = 1; int j = 1;

	string KW1 = "";
	bool Duplicate = false;


	for (int l = 0; l < KeyWord1.length(); l++)
	{
		if (KW1.length() == 0)
		{
			KW1 += KeyWord1[l];
		}

		else
		{
			for (int m = 0; m < KW1.length(); m++)
			{
				if (KeyWord1[l] == KW1[m])
				{
					Duplicate = true;
				}
			}

			if (Duplicate == false)
			{
				KW1 += KeyWord1[l];
			}
		}

		Duplicate = false;
	}

	Duplicate = false;
	string Letters = "";
	string Joined = "";

	for (int q = 0; q < Alphabet_PS.length(); q++)
	{

		for (int r = 0; r < KW1.length(); r++)
		{
			if (Alphabet_PS[q] == KW1[r])
			{
				Duplicate = true;
			}
		}

		if (Duplicate == false)
		{
			Letters += Alphabet_PS[q];
		}

		Duplicate = false;
	}

	Joined = KW1 + Letters;

	cout << "Keyword 1 is: " << KeyWord1 << endl;
	cout << "Simplified KW1 is: " << KW1 << endl;
	cout << "Reduced Alphabet is: " << Letters << endl;
	cout << "The joined result is: " << Joined << endl << endl;

	for (int k = 0; k < Joined.length(); k++)
	{
		if (j > 5)
		{
			i++;
			j = 1;
		}

		if (j < 6)
		{

			PS[i][j] = Joined[k];
			j++;
		}
	}
}



/*
	Public Method void: Set_KW1_PS

	Description:
		This method will take our plaintext message and utilize the Polybius Square that
		has been updated with keyword 1 and will make a temporary encryption string by replacing
		the plaintext letter with the corresponding Row and Column letter from the ADFGX Polybius Square.
		This is stored in a class variable to be accessed and utilized later for further message scrambling
		and discombobulation.

	Params:
		- string M

	Returns:
		- None
 */

void AdfgxLookup::Encrypt_String(string M)
{
	string message = M;
	string Temp = "";
	string Temp_String = "";
	string entry = "";
	bool found = false;

	for (int i = 0; i < message.size(); i++)
	{
		if (message[i] == 'j')							// i and j map to the same index
		{
			message[i] = 'i';
		}

		while (found == false)
		{
			for (int j = 1; j < col; j++)
			{
				for (int k = 1; k < row; k++)
				{
					entry = PS[j][k];

					if (message[i] == entry[0])
					{
						found = true;
						Temp = (PS[j][0] + PS[0][k]);
						Temp_String += Temp;
					}

					if (!found && j == col-1 && k == row-1)
					{
						found = true;
						Temp_String += message[i];
					}
				}
			}
		}

		found = false;
	}

	cout << endl << "Message is: " << M << endl;
	cout << "Temp encrypted string is: " << Temp_String << endl << endl;

	for (int i = 0; i < Temp_String.size(); i++)
	{
		if (Temp_String[i] == 32)
		{
			Temp_String.erase(Temp_String.begin() + i);
		}
	}

	cout << "Temp encrypted string is: " << Temp_String << endl << endl;
	PS_Encrypt = Temp_String;
}



/*
	Public Method void: Print_PS

	Description:
		This method will print out the Polybius Square. It's main use is largely
		as a sanity check for debugging. Essentially to make sure that the square
		is built correctly and that character pairs are syncing up correctly.

	Params:
		- None

	Returns:
		- None
 */

void AdfgxLookup::Print_PS()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << PS[i][j] << " ";
		}

		cout << endl;
	}

	cout << endl;
}



/*
	Public Method void: Encode_PS_KW2

	Description:
		This method builds the columnar transformation matrix that will encode the 
		second keyword that is used to further scramble and discombobulate the message.
		It includes some extra rows for visual effect that eases in the debugging process.

	Params:
		- None

	Returns:
		- None
 */

void AdfgxLookup::Encode_PS_KW2()
{
	int R = KeyWord2.length();
	int C = PS_Encrypt.length();

	int Len = ((C / R) + 3);				// + 1 allows for proper column height, + 3 is to display KW2 and "-" as column headers

	CT_Matrix.resize(Len);

	for (int i = 0; i < Len; i++)
	{
		CT_Matrix[i].resize(R);
	}

	for (int j = 0; j < R; j++)
	{
		char Temp = '-';
		CT_Matrix[0][j].push_back(KeyWord2[j]);
		CT_Matrix[1][j].push_back(Temp);
	}

	int y = 2;
	int z = 0;

	for (int k = 0; k < C; k++)
	{
		if (z < R)
		{
			CT_Matrix[y][z] = PS_Encrypt[k];
			z++;
		}

		else
		{
			y++;
			z = 0;
			CT_Matrix[y][z] = PS_Encrypt[k];
			z++;
		}
	}

	for (int i = 0; i < CT_Matrix.size(); i++)
	{
		for (int j = 0; j < CT_Matrix[i].size(); j++)
		{
			cout << CT_Matrix[i][j] << " ";
		}

		cout << endl;
	}
}



/*
	Public Method void: Discombobulate

	Description:
		This method is what will further scramble up the encrypted text by performing a 
		columnar transformation utilizing the matrix built using keyword 2. The Final encryoted
		message is read through the columns once the transformation process is complete.

	Params:
		- None

	Returns:
		- None
 */

void AdfgxLookup::Discombobulate()
{
	struct Properties
	{
		char letter;
		int Col_num;
		vector<string> Entries;

		Properties()
		{
			letter = Col_num = 0;
		}
	};

	vector<Properties> CTTM;

	string Sorted = KeyWord2;
	sort(Sorted.begin(), Sorted.end());		// Built-in function from #include<algorithm> file
	longest_column = ((PS_Encrypt.length() / KeyWord2.length() + 3));


	for (int i = 0; i < KeyWord2.length(); i++)
	{
		Properties Temp;

		Temp.letter = KeyWord2[i];
		Temp.Col_num = i;

		for (int j = 2; j < longest_column; j++)
		{
			if (CT_Matrix[j][i] != "")
			{
				Temp.Entries.push_back(CT_Matrix[j][i]);
			}

			else
			{
				Temp.Entries.push_back(" ");
			}
			
		}

		CTTM.push_back(Temp);
	}


	//cout << endl << CTTM[5].letter << endl;
	//for (int k = 0; k < CTTM[5].Entries.size(); k++)
	//{
	//	cout << CTTM[5].Entries[k] << " ";
	//}

	cout << endl << endl;

	int R = KeyWord2.length();
	int C = PS_Encrypt.length();


	Dis_Matrix.resize(longest_column);

	for (int i = 0; i < longest_column; i++)
	{
		Dis_Matrix[i].resize(R);
	}

	for (int j = 0; j < R; j++)
	{
		char Temp = '-';
		Dis_Matrix[0][j].push_back(Sorted[j]);
		Dis_Matrix[1][j].push_back(Temp);
	}

	for (int i = 0; i < Sorted.length(); i++)
	{
		for (int j = 0; j < CTTM.size(); j++)
		{
			if (Sorted[i] == CTTM[j].letter)
			{
				for (int k = 0; k < CTTM[j].Entries.size(); k++)
				{
					int q = k + 2;
					Dis_Matrix[q][i] = CTTM[j].Entries[k];
				}
			}
		}
	}


	for (int i = 0; i < Dis_Matrix.size(); i++)
	{
		for (int j = 0; j < Dis_Matrix[i].size(); j++)
		{
			cout << Dis_Matrix[i][j] << " ";
		}

		cout << endl;
	}
}



/*
	Public Method void: Print_Message

	Description:
		This method is straighforward as it will print the final result of encrypting the
		message. Future version will likely factor in the operation and print the desired
		result, encrypted or decrypted.

	Params:
		- None

	Returns:
		- None
 */

void AdfgxLookup::Print_Message()
{
	string Temp = "";

	for (int i = 0; i < KeyWord2.length(); i++)
	{
		for (int j = 2; j < longest_column; j++)
		{
			if (Dis_Matrix[j][i] != " ")
			{
				Temp += Dis_Matrix[j][i];
			}
		}
	}

	Encrypted = Temp;
	cout << endl << "Final Encrypted Message is: " << Encrypted << endl;
}
