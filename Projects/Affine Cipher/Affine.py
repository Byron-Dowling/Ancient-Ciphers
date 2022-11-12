"""
    Affine:
        Epsilon(B) = Epsilon(Z) = a^2 + b (mod 26)


    ex:) a = 3, b = 17

        f(x) = aX + b => f(x) % 26
             
             where a = some arbitrary value
             where b = some arbitrary value
             and X = the numerical index of the letter being encrypted

             A B C D E F G H I J K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
             0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

        Sample Message:
             PORK AND BEANS

             P = 17     A = 0      B = 1
             O = 14     N = 13     E = 4
             R = 17     D = 3      A = 0
             K = 10                N = 13
                                   S = 18

            ex:) 
                P = 15, a = 3, b = 17

                f(x) = (3 * 15) + 17
                f(x) = 62
                f(x) = 62 % 26 = 10

                10 => 'K'

        Cipher Text:
            KHQV REA UDRET
"""

import copy
from collections import Counter

class Affine:

    def __init__ (self, A = 1, B = 1):

        self.alphabet = [chr(x+65) for x in range(26)]
        self.letterFrequencyOrder = []
        self.letterPairs = {}
        self.valueA = A
        self.valueB = B
        self.decryptA = 0
        self.decryptB = 0
        self.plaintext = ""
        self.ciphertext = ""
        self.key_list = []
        self.val_list = []
        self.common = ""
        

        with open("common.txt","r") as f:
            self.common = f.read()

        for i in range(26):
            self.letterPairs[self.alphabet[i]] = i

        frequency = "ETAOINSRHLDCUMFGPWYBVKJXZQ"

        for letter in frequency:
            self.letterFrequencyOrder.append(letter)

        self.key_list = list(self.letterPairs.keys())
        self.val_list = list(self.letterPairs.values())

        if self.valueA == 1:
            print("Enter a value for A.")
            self.valueA = int(input())

        if self.valueB == 1:
            print("Enter a value for B.")
            self.valueB = int(input())


    # Sanity Check
    def showPairs(self):

        for key in self.letterPairs:
            print(key, self.letterPairs[key])


    """
        Formula is f(x) = aX + b => f(x) % 26

        Best results occur when a and b are relatively prime.
    
    """
    def affineFormula(self, letter):
        
        val = int(self.letterPairs[letter])
        FofX = (self.valueA * val) + self.valueB
        FofX = FofX % 26

        position = self.val_list.index(FofX)
        return self.key_list[position]
    

    def encrypt(self):
        
        print("Type your message to encrypt.")
        self.plaintext = input()
        self.plaintext = self.plaintext.upper()


        for letter in self.plaintext:
            if letter != ' ':
                self.ciphertext += self.affineFormula(letter)
            else:
                self.ciphertext += ' '

        print()
        print(self.plaintext)
        print(self.ciphertext)


    """
        Possible attacks:

            - if we know that the equation is: f(x) = aX + b => f(x) % 26
                - Can try to attack a and b
            
            - can try to break letter pairs such as common letters like e, t, etc.

            - can look for double letters like 'ss' or 'll' or 'ee' or 'oo'

            - Letter Frequency order: ETAOINSRHLDCUMFGPWYBVKJXZQ

    """

    def decrypt(self):
        pass


    def frequencyAnalysis(self):

        subStrings = self.ciphertext.split()
        freqCount = Counter(self.ciphertext)

        singles = []
        doubles = []
        triples = []

        for substring in subStrings:

            if len(substring) == 1:
                singles.append(substring)

            elif len(substring) == 2:
                doubles.append(substring)

            elif len(substring) == 3:
                triples.append(substring)

        if len(singles) != 0:
            singlesSet = set(singles)
            shiftedIndexes = []

            for char in singlesSet:
                singleShifted = []
                for word in self.common:
                    if len(word) == 1:
                        diff = (ord(word) - ord(char)) % 26
                        singleShifted.append(diff)

                shiftedIndexes.append(singleShifted)

            for shiftedList in singleShifted:
                for diff in shiftedList:
                    self.decryptB

        if len(doubles) != 0:
            doublesSet = set(doubles)

            for pair in doublesSet:
                for word in self.common:
                    if len(word) == 2:
                        diff = (ord(word) - ord(char)) % 26

        if len(triples) != 0:
            triplesSet = set(triples)





    def CryptoMath(self, tempShifted):
    
        print("In CryptoMath")

        Temp_IOC = float()
        Final_IOC = float()
        Result = float()
        
        letters = []
        frequency = [0] * 26

        letters = list(tempShifted)

        index = 0

        for char in self.alphabet:

            for letter in letters:

                if char == letter:

                    frequency[index] += 1

            index += 1


        for num in frequency:

            Sigma_Big_N = len(tempShifted)
            Sigma_Small_n = float(num)
            Numerator = (Sigma_Small_n * (Sigma_Small_n - 1))
            Denominator = float()
            Denominator = (Sigma_Big_N * (Sigma_Big_N - 1))

            Temp_IOC = Numerator / Denominator

            Result += Temp_IOC


        Final_IOC = Result
        print("Final IOC is:", Final_IOC)
        return Final_IOC


if __name__=='__main__':

    app = Affine()
    app.encrypt()
    ## app.frequencyAnalysis()