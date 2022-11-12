/*

    Name: Byron Dowling
    Program: ADFGVX Cipher


    How does the Cipher work?

    ADFGVX Example: 
                Message: I solemnly swear that I am up to no good
                Key 1: horcrux
                Key 2: lumos

                Blank Polybius Square:

                              A D F G V X 
                            A a b c d e f
                            D g h i j k l 
                            F m n o p q r
                            G s t u v w x
                            V y z 0 1 2 3
                            X 4 5 6 7 8 9

                Polybius with first key: 'horcrux'

                              A D F G V X 
                            A H O R C U X 
                            D A B D E F G 
                            F I J K L M N 
                            G P Q S T V W 
                            V Y Z 0 1 2 3 
                            X 4 5 6 7 8 9 
                
                *Use the Polybius square to encrypt the message
                *For example, the letter 'D' translates to 'DF'

                Message: I solemnly swear that I am up to no good
                Temp String: FA GFADFGDGFVFXFGVA GFGXDGDAAF GGAADAGG 
                             FA DAFV AVGA GGAD FXAD DXADADDF

                Columnar Transformation:
                Key 2: lumons

                            L U M O S
                            ---------
                            F A G F A
                            D F G D G
                            F V F X F
                            G V A G F
                            G X D G D
                            A A F G G
                            A A D A G
                            G F A D A
                            F V A V G
                            A G G A D
                            F X A D D
                            X A D A D
                            D F 

                Alphabetize the columns:

                            L M O S U
                            ---------
                            F G F A A
                            D G D G F
                            F F X F V
                            G A G F V
                            G D G D X
                            A F G G A
                            A D A G A
                            G A D A F
                            F A V G V
                            A G A D G
                            F A D D X
                            X D A D A
                            D       F

                Final Encrypted String:
                    FDFGGAAGFAFXDAFVVXAAFVGXAFGGFADFDAAGADFDXGGGADVADAAGFFDGGAGDDD

*/

using System;
using System.Collections.Generic;

class Program 
{
  public class ADFGVX
  {
    private string plaintext;
    private string ciphertext;
    private string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";   // A-Z and 0-9
    private string key1;
    private string key2;
    private string polybiusstring;
    private string tempcipherstring;
    private char[,] PolybiusSquare = new char[7,7];
    private string header = "ADFGVX";
    private Dictionary <char, string> ADFGVX_Lookup = new Dictionary <char, string> ();
    private Dictionary <char, int> Column_Lookup = new Dictionary<char, int> ();
    private List<string> CT = new List<string>();


    // Overloaded Constructor
    public ADFGVX(string k1, string k2, string pt) {
        // Making everything uppercase
        this.key1 = k1.ToUpper();
        this.key2 = k2.ToUpper();
        this.plaintext = pt.ToUpper();

        // Initializing strings to empty strings
        this.ciphertext = "";
        this.tempcipherstring = "";
        this.polybiusstring = "";
        this.PolybiusSquare[0,0] = ' ';

        // Setting the ADFGVX Border in the Polybius Square
        for (int i = 1; i < 7; i++) {
            this.PolybiusSquare[0, i] = this.header[i-1];
            this.PolybiusSquare[i, 0] = this.header[i-1];
        }
    }


    // We build the polybius string by concatenating the reduced key1 with the 
    // alphabet variable keping in mind to remove/ignore duplicates
    public void buildPolybiusString()
    {
        // Looping through key1
        for (int i = 0; i < this.key1.Length; i++) {

            // If length is zero, concatenate key to polybius string
            if (this.polybiusstring.Length == 0) {
                this.polybiusstring += this.key1[i];
            }

            // If polybius string is not empty, we need to check if the letter
            // of the key is in the polybius string before we concatenate it
            else {
                Boolean found = false;

                // Loop through the string, if it's found, update bool and break early
                for (int j = 0; j < this.polybiusstring.Length; j++) {
                    if (this.polybiusstring[j] == this.key1[i]) {
                        found = true;
                        break;
                    }
                }

                // If the letter wasn't found, concatenate it to polybius string
                if (!found) {
                    this.polybiusstring += this.key1[i];
                }
            }
        }

        // Adding the remaining alphabet
        // Repeat of the same style of process
        for (int i = 0; i < Alphabet.Length; i++) {

            Boolean found = false;

            for (int j = 0; j < this.polybiusstring.Length; j++) {
                if (this.polybiusstring[j] == this.Alphabet[i]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                this.polybiusstring += this.Alphabet[i];
            }
        }

        // Building the Polybius Square with the string
        int x = 0;
        int y = 0;

        // For each letter in the polybius string
        // This is a weird way to build the square without having to
        // use nested loops since we know what the dimensions of the square are
        foreach(char letter in this.polybiusstring) {
            
            if (y > 5) {
                y = 0;
                x++;
            }
          
            this.PolybiusSquare[x+1, y+1] = letter;
            y++;
        }
    }

    // Printing the Polybius Square to make sure it looks right
    public void SanityCheck() 
    {
         for (int i1 = 0; i1 < 7; i1++) {
            for (int i2 = 0; i2 < 7; i2++) {
                Console.Write(PolybiusSquare[i1, i2]);
                Console.Write(" ");
            }

            Console.WriteLine();
        }
    }

    // Building the lookup table by creating a dictionary lookup of the plaintext chars
    // mapped to their cipher text, i.e i >> AA or e >> AX etc.
    public void buildLookupTable() 
    {
         for (int i1 = 1; i1 < 7; i1++) {
            for (int i2 = 1; i2 < 7; i2++) {

                /*
                    Dictionary is char to string, so we are converting the characters in the 
                    Polybius square explicitly to strings and concatenating them together.

                    Ex:)
                        character 'A' is converted to "A" 
                        character 'X' is converted to "X"

                        temp = "A" + "X" = "AX"
                */
                string temp = PolybiusSquare[i1, 0].ToString() + PolybiusSquare[0, i2].ToString();

                // Insert into Dictionary
                ADFGVX_Lookup.Add(PolybiusSquare[i1, i2], temp);
            }
        }

        // Sanity Check that Dictionary is built correctly
        foreach(KeyValuePair<char, string> kvp in ADFGVX_Lookup)
          {
              Console.WriteLine("{0} and {1}", 
                          kvp.Key, kvp.Value);
          }
          Console.WriteLine();
    }


    /*
        Here's where we are doing the columnar transformation
        utilizing key#2
    */
    public void discombobulate() {

      Console.WriteLine("Temp Cipher String:");
      Console.WriteLine(this.tempcipherstring);
      Console.WriteLine();

        string temp = "";
        foreach(char letter in this.tempcipherstring) {
            if (temp.Length < this.key2.Length) {
                temp += letter;
            }

            else
            {
                CT.Add(temp);
                temp = "";
                temp += letter;
            }
        }

        while(temp.Length < this.key2.Length) {
          temp += ' ';
        }

        CT.Add(temp);

      Console.WriteLine(this.key2);
      Console.WriteLine("-----");
      
      foreach(string word in this.CT) {
        Console.WriteLine(word);
      }

      /*
            Need to create a dictionary lookup of the key2

            Ex:) LUMOS <-> LMOSU
                 01234 <-> 02341

                 Extract the numerical column and concatenate to final encrypted string
      */

      Dictionary <char, int> KW2 = new Dictionary<char, int> ();

      dynamic sortedString = SortString(this.key2);

      for (int i = 0; i < sortedString.Length; i++) {
        KW2.Add(sortedString[i], i);
      }

    
      for (int i = 0; i < sortedString.Length; i++) {

        foreach(string word in this.CT) {

          dynamic index = KW2[sortedString[i]];
            if (word[index] != ' ') {
                this.ciphertext += word[index];
            }
        }
      }
    }


    // Alphabetize a string 
    static string SortString(string input)
    {
        char[] characters = input.ToCharArray();
        Array.Sort(characters);
        return new string(characters);
    }


    public string getCiphertext() {
      return ciphertext;
    }


    public void encryptMessage() {

        foreach(char letter in this.plaintext) {

          if (letter != ' ')
          {
            dynamic fetch = ADFGVX_Lookup[letter];
            this.tempcipherstring += fetch;
          }
        }
    }

    public void setKeys(string k1, string k2) {
        this.key1 = k1;
        this.key2 = k2;
    }

    public void setMessage(string message = "") {
        if (message == "") {
            string input;
            Console.WriteLine("Enter your message to be encrypted.");
            input = Console.ReadLine();

            this.plaintext = input;
        }
    }
  }

  public static void Main (string[] args) 
  {
    ADFGVX C1 = new ADFGVX("horcrux", "lumos", "I solemnly swear that I am up to no good");

    C1.buildPolybiusString();
    C1.SanityCheck();
    C1.buildLookupTable();
    C1.encryptMessage();
    C1.discombobulate();

    Console.WriteLine();
    Console.WriteLine("Final Encrypted String:");
    Console.WriteLine(C1.getCiphertext());
  }
}
