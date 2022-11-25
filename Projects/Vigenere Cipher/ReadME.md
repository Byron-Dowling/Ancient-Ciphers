## Vigenere Cipher
### Byron Dowling
### Description:

The Vigenere Cipher is a method of encrypting alphabetic text. It uses a simple form of polyalphabetic substitution. A polyalphabetic cipher is any cipher based on substitution, using multiple substitution alphabets .The encryption of the original text is done using the Vigenère square or Vigenère table. The table consists of the alphabets written out 26 times in different rows, each alphabet shifted cyclically to the left compared to the previous alphabet, corresponding to the 26 possible Caesar Ciphers. At different points in the encryption process, the cipher uses a different alphabet from one of the rows. The alphabet used at each point depends on a repeating keyword.

### Files

|   #    | File                    | Description                                        |
| :---:  | ----------------------- | -------------------------------------------------- |
|   1    | Vigenere.cpp            | Main Driver of the Project                         |
|   2    | VigenereClass.hpp       | Header File with classes and implementation        |
|   3    | VCT1.txt                | Input file that was used to test                   |
|   4    | VCT2.txt                | Input file that was used to test                   |
|   5    | VCT3.txt                | Input file that was used to test                   |
|   6    | VCT4.txt                | Input file that was used to test                   |
|   7    | VCT5.txt                | Input file that was used to test                   |
|   8    | Words.txt               | Dictionary File of 134K English Words              |
|   9    | Dictionary.txt          | Larger Dictionary File of 466K English Words       |


### Approach:

The current approach is to perform an index of coincidence analysis on the encrypted text to determine the key length. Upon completion, the program will perform a dictionary attack on the key pulling words from the dictionary that are of the same length as the key length that scored the highest I.O.C value. Results of the dictionary attack are scored and theoretically the highest scoring result will be the plaintext result.

### Strengths
- Is bulletproof accurate on large texts
- Is very fast as average results are around 4 seconds

### Weaknesses
- Current approach fails on very short messages
- Assumes that the key is a dictionary word and not some scrambled nonsense

### Anticipated/Potential Revisions
- Attack shorter messages using CUDA for number crunching
- Perform other cryptanalysis techniques such as partial key breaking by decrypting shorter words and phrases.


![VC3](https://github.com/Byron-Dowling/Assets/blob/main/Images/Vigenere.jpg?raw=true)
