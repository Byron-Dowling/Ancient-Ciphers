using System;

class Program 
{
  public class Affine
  {
    private int A;
    private int B;
    private string plaintext;
    private string ciphertext;
    private string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    public Affine(int a, int b, string pt) {
        A = a;
        B = b;
        plaintext = pt.ToUpper();
    }

    public string getAlphabet()
    {
      return Alphabet;
    }

    public string getCiphertext() {
      return ciphertext;
    }

    /*
        Formula:

          f(x) = aX + b % 26

            where x is the letter index of the letter being encrypted
    */
    public void encryptMessage() {

      Console.WriteLine(this.plaintext);

      foreach(char letter in this.plaintext) {

        int xVal = (int)letter - 65;

        if (xVal >= 0) {

          int FofX = (this.A * xVal + this.B) % 26;
          
          this.ciphertext += this.Alphabet[FofX];
        }

        else {
          this.ciphertext += " ";
        }
      }
    }
  }

  public static void Main (string[] args) 
  {
    Affine C1 = new Affine(3, 17, "Oh Reginald I disagree");

    string a = C1.getAlphabet();

    C1.encryptMessage();
    Console.WriteLine(C1.getCiphertext());
  }
}