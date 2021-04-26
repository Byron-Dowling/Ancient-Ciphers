## Vigenere Cipher
### Byron Dowling
### Description:

The Vigenere Cipher is a method of encrypting alphabetic text. It uses a simple form of polyalphabetic substitution. A polyalphabetic cipher is any cipher based on substitution, using multiple substitution alphabets .The encryption of the original text is done using the Vigenère square or Vigenère table. The table consists of the alphabets written out 26 times in different rows, each alphabet shifted cyclically to the left compared to the previous alphabet, corresponding to the 26 possible Caesar Ciphers. At different points in the encryption process, the cipher uses a different alphabet from one of the rows. The alphabet used at each point depends on a repeating keyword.

### Files

|   #    | File                    | Description                                        |
| :---:  | ----------------------- | -------------------------------------------------- |
|   1    | Crypto5.cpp             | Main Driver of the Project                         |
|   2    | Crypto5 Classes.h       | Header File with Several Class Definitions         |
|   3    | Crypto5 Methods.cpp     | Class Methods and Implementation                   |
|   4    | Hash.hpp                | Helper Class to Implement Hash Table               |
|   5    | Tabula Recta.hpp        | Helper Class to Implement Tabula Recta Table       |
|   6    | Timer Clock.hpp         | Helper Class for Timing Processes                  |
|   7    | VCT1.txt                | Input file that was used to test                   |
|   8    | VCT2.txt                | Input file that was used to test                   |
|   9    | VCT3.txt                | Input file that was used to test                   |
|   10   | VCT4.txt                | Input file that was used to test                   |
|   11   | VCT5.txt                | Input file that was used to test                   |
|   12   | Words.txt               | Dictionary File of 134K English Words              |
|   13   | Dictionary.txt          | Larger Dictionary File of 466K English Words       |


### Approach:

The end goal of this program is to allow the user to select the method of how they want to solve the cipher. For now, the current approach is to perform an index of coincidence analysis on the encrypted text to determine the key length. Upon completion, the program will perform a dictionary attack on the key pulling words from the dictionary that are of the same length as the key length that scored the highest I.O.C value. Another approach is to also calculate the I.O.C value of the most likely key length and attempt to crack a single sequence of the message and narrow down the shift possibilities. From here, all the narrowed down shifts will be attempted and then the words will be looked up in a Hash Table to see if they are english matches. 

### Current Working Approach
- Give the program a large encrypted text. The larger the text, the more likely the Index of Coincidence will accurately find the key length.
- Assuming the key is a dictionary word and the I.O.C was calculated correctly, the program will dictionary attack the key and then check sort the results in order of I.O.C value. The result with the highest I.O.C value will most likely be the one that is english and the proper decrypted text.
- Currently the Program should work for larger examples as seen below

![VC3](https://github.com/Byron-Dowling/Ancient-Ciphers/blob/main/Projects/Vigenere%20Cipher/Vigenere%20Snippet%203.JPG?raw=true)
