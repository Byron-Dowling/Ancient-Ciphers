#include<iostream>

using namespace std;

/*

 $$$$$$$$\        $$\                 $$\                   $$$$$$$\                        $$\
 \__$$  __|       $$ |                $$ |                  $$  __$$\                       $$ |
	$$ | $$$$$$\  $$$$$$$\  $$\   $$\ $$ | $$$$$$\          $$ |  $$ | $$$$$$\   $$$$$$$\ $$$$$$\    $$$$$$\
	$$ | \____$$\ $$  __$$\ $$ |  $$ |$$ | \____$$\ $$$$$$\ $$$$$$$  |$$  __$$\ $$  _____|\_$$  _|   \____$$\
	$$ | $$$$$$$ |$$ |  $$ |$$ |  $$ |$$ | $$$$$$$ |\______|$$  __$$< $$$$$$$$ |$$ /        $$ |     $$$$$$$ |
	$$ |$$  __$$ |$$ |  $$ |$$ |  $$ |$$ |$$  __$$ |        $$ |  $$ |$$   ____|$$ |        $$ |$$\ $$  __$$ |
	$$ |\$$$$$$$ |$$$$$$$  |\$$$$$$  |$$ |\$$$$$$$ |        $$ |  $$ |\$$$$$$$\ \$$$$$$$\   \$$$$  |\$$$$$$$ |
	\__| \_______|\_______/  \______/ \__| \_______|        \__|  \__| \_______| \_______|   \____/  \_______|


		A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
	   ____________________________________________________
	A | A B C D E F G H I J K L M N O P Q R S T U V Q X Y Z
	B | B C D E F G H I J K L M N O P Q R S T U V W X Y Z A
	C | C D E F G H I J K L M N O P Q R S T U V W X Y Z A B
	D | D E F G H I J K L M N O P Q R S T U V W X Y Z A B C
	E | E F G H I J K L M N O P Q R S T U V W X Y Z A B C D
	F | F G H I J K L M N O P Q R S T U V W X Y Z A B C D E
	G | G H I J K L M N O P Q R S T U V W X Y Z A B C D E F
	H | H I J K L M N O P Q R S T U V W X Y Z A B C D E F G
	I | I J K L M N O P Q R S T U V W X Y Z A B C D E F G H
	J | J K L M N O P Q R S T U V W X Y Z A B C D E F G H I
	K | K L M N O P Q R S T U V W X Y Z A B C D E F G H I J
	L | L M N O P Q R S T U V W X Y Z A B C D E F G H I J K
	M | M N O P Q R S T U V W X Y Z A B C D E F G H I J K L
	N | N O P Q R S T U V W X Y Z A B C D E F G H I J K L M
	O | O P Q R S T U V W X Y Z A B C D E F G H I J K L M N
	P | P Q R S T U V W X Y Z A B C D E F G H I J K L M N O
	Q | Q R S T U V W X Y Z A B C D E F G H I J K L M N O P
	R | R S T U V W X Y Z A B C D E F G H I J K L M N O P Q
	S | S T U V W X Y Z A B C D E F G H I J K L M N O P Q R
	T | T U V W X Y Z A B C D E F G H I J K L M N O P Q R S
	U | U V W X Y Z A B C D E F G H I J K L M N O P Q R S T
	V | V W X Y Z A B C D E F G H I J K L M N O P Q R S T U
	W | W X Y Z A B C D E F G H I J K L M N O P Q R S T U V
	X | X Y Z A B C D E F G H I J K L M N O P Q R S T U V W
	Y | Y Z A B C D E F G H I J K L M N O P Q R S T U V W X
	Z | Z A B C D E F G H I J K L M N O P Q R S T U V W X Y

*/

class Tabula_Recta
{
protected:
	string Lookup_Table[27][27];
	string Alphabet_Row;
	string Alphabet_Column;

public:

	Tabula_Recta();
	void Build_Lookup_Table();
	friend class Vigenere;
};





Tabula_Recta::Tabula_Recta()
{
	Alphabet_Row = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	Alphabet_Column = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	Lookup_Table[0][0] = "-";

	for (int i = 1; i < 27; ++i)
	{
		int q = i - 1;
		Lookup_Table[i][0] = Alphabet_Row[q];
		Lookup_Table[0][i] = Alphabet_Row[q];
	}

	for (int j = 1; j < 27; j++)
	{
		int l = 0;

		for (int k = 1; k < 27; k++)
		{
			Lookup_Table[j][k] = Alphabet_Column[l];
			l++;
		}

		char temp;
		temp = Alphabet_Column[0];
		Alphabet_Column.push_back(temp);
		Alphabet_Column.erase(0, 1);
	}
}


void Tabula_Recta::Build_Lookup_Table()
{
	cout << endl;

	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			cout << Lookup_Table[i][j] << " ";
		}

		cout << endl;
	}

	cout << endl;
}