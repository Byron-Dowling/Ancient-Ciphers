## ADFGX Cipher
### Byron Dowling
### Description:

The intent of this program is to implement an ADFGX cipher that will both encrypt a plaintext message using the cipher and decrypt cipher text that was encrypted using the ADFGX cipher. The ADFGX cipher was a field cipher used by the German Army during World War I. It is closely related to the ADFGVX cipher. ADFGX is a fractionating transposition cipher which combined a modified Polybius square with a single columnar transposition. The cipher is named after the five possible letters used in the ciphertext: A, D, F, G and X. These letters were chosen deliberately because they sound very different from each other when transmitted via morse code. The intention was to reduce the possibility of operator error. To properly implement an ADFGX cipher, one will need two keys with non-repeating characters as well as preferred plaintext or previously encrypted cipher text.

### Files

|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | adfgx.py        | Main driver of my project                          |
|   2   | polybius.py     | Helper class that builds the polybius square       |
|   3   | encrypted.txt   | Output file for final encrypted text               |
|   4   | plaintext.txt   | Input file for beginning the encryption process    |
|   5   | cipher.txt      | Input file for beginning the decryption process    |
|   6   | decrypted.txt   | Output file for final decrypted text               |

### Instructions

- The program can be run from your machine's console or from this replit project: https://replit.com/@ByronDowling/ADFGX-Cipher-2#ADFGX.py
- The program expects an input file and output file destination, a command, either Encrypt or Decrypt, and a keyword 1 and keyword 2 with non-repeating characters

### Example Parameters:
    - `language = "python3"`
    - `run = "python3 adfgx.py input_file=encrypted.txt output_file=decrypted.txt operation=Decrypt keyword1=turing keyword2=enigma"`

### Example Encryption:

![image of SS1](https://github.com/Byron-Dowling/Ancient-Ciphers/blob/main/Projects/ADFGX%20Cipher/ADFGX%20Snippet.JPG?raw=true)
![Image of SS2](https://github.com/Byron-Dowling/Ancient-Ciphers/blob/main/Projects/ADFGX%20Cipher/ADFGX%20Snippet%202.JPG?raw=true)

### Example Decryption:

![Image of SS3](https://github.com/Byron-Dowling/Ancient-Ciphers/blob/main/Projects/ADFGX%20Cipher/ADFGX%20Snippet%203.JPG?raw=true)
