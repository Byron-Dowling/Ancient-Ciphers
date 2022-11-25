# Affine Cipher
![AC](https://media.geeksforgeeks.org/wp-content/uploads/affin-cipher.png)

## Wiki
https://en.wikipedia.org/wiki/Affine_cipher

### Brief Synopsis
An Affine cipher is a type of substitution cipher that utilizes two integer values, A and B, as well as the alphabetical index "X" of the letter to be encrypted where A = 0, B = 1, ... Z = 25. The formula is A(X) + B % 26, therefore if A = 3, B = 17, and we are encrypting the letter "A", then the formula is: fx = 3(0) + 17 % 26 where fx is the alphabetical index of the new letter that "A" has been encrypted to. IF proper A and B values are picked, this should result in a 1:1 correspondence function-wise and should uniquely encrypt each alphabetical letter to a unique cipher letter.

### Shortcomings
- The cipher is not secure at all as it is susceptible to frequency analysis
- If spaces are preserved, then it is vulnerable to short letter bruteforce attacks
  - If two letters are successfully decrypted, the formula can be derived and then the entire message can be cracked.
  
### Extras
- [Windows Forms Cipher GUI Project](https://github.com/Byron-Dowling/5113-APLC-Dowling/tree/main/Assignments/Windows%20Forms%20C%23)
