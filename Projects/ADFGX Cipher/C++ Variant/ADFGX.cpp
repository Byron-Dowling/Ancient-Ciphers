#include <iostream>
#include <fstream>
#include "ADFGX.h"

using namespace std;

int main()
{
	//string Key1 = "hurry";
	//string Key2 = "quickly";
	//string plaintext = "get out now before its too late john";
	string Key1 = "winter";
	string Key2 = "soldier";
	string plaintext = "mission report december sixteenth nineteen ninety one";
	string cipher = "DGXAGADAFAXAGXAFDXDFAFAFADGDGGAXXXAXAFGADAADFAXFFADXXAAADXDXAGAXAGAGFGXGAAFAGAXAGXDDAAGGADAFAF";

	AdfgxLookup PS1;
	PS1.Build_PS();
	PS1.Set_KW1_PS(Key1);
	PS1.Set_KW2_PS(Key2);

	PS1.Print_PS();
	cout << endl;
	PS1.Encode_PS_KW1();

	PS1.Print_PS();

	PS1.Encrypt_String(plaintext);
	PS1.Encode_PS_KW2();


	PS1.Discombobulate();
	PS1.Print_Message();


	return 0;
}
