import sys
import os
import pprint
from Polybius import AdfgxLookup
import math

"""
run = "python3 adfgx.py input_file=encrypted.txt output_file=decrypted.txt operation=Decrypt keyword1=turing keyword2=enigma"
run = "python3 adfgx.py input_file=plaintext.txt output_file=encrypted.txt operation=Encrypt keyword1=turing keyword2=enigma"
"""

os.system('clear')

def print_matrix(matrix,rows,key,in_order=False):

    pprint.pprint(matrix)

    if in_order:
        key = sorted(key)

    for k in key:
        print(k,end=' ')

    print("")
    for k in key:
        print('-',end=' ')

    print("")                                   # range return a list from 0 to rows - 1
    for r in range(rows):                       # [0,1,2,3,4,...,rows-1]    
        for k in key:                           # k = 1 letter in key per loop
            if r < len(matrix[k]):
                print(matrix[k][r],end=" ")
            else:
                print(" ",end=' ')
        print("")


def mykwargs(argv):
    '''
    Processes argv list into plain args (list) and kwargs (dict).
    Just easier than using a library like argparse for small things.
    Example:
        python file.py arg1 arg2 arg3=val1 arg4=val2 -arg5 -arg6 --arg7
        Would create:
            args[arg1, arg2, -arg5, -arg6, --arg7]
            kargs{arg3 : val1, arg4 : val2}

        Params with dashes (flags) can now be processed seperately
    Shortfalls:
        spaces between k=v would result in bad params
        Flags aren't handled at all. Maybe in the future but this function
            is meant to be simple.
    Returns:
        tuple  (args,kargs)
    '''
    args = []
    kargs = {}

    for arg in argv:
        if '=' in arg:
            key,val = arg.split('=')
            kargs[key] = val
        else:
            args.append(arg)
    return args,kargs


# Function to begin the encryption process
# receives the args/kwargs via **params
def encrypt(**params):
    """ Encrypt a message
    Params:
        input_file <string> 
        keyword1 <string>
        keyword2 <string>
    """
    print("We are ENCRYPTING")

    # Retrieving the params
    input_file = params.get('input_file',None)
    keyword1 = params.get('keyword1',None)
    keyword2 = params.get('keyword2',None)

    # Confirming our data that we're working with
    print(f"Input File = {input_file}")
    print(f"Keyword 1 = {keyword1}")
    print(f"Keyword 2 = {keyword2}")

    # Building an instance of our polybius class
    # using the first keyword
    Run1 = AdfgxLookup(keyword1)


    # Building the actual polybius square using key1
    # and creating its corresponding lookup table
    # printing table for verification
    lookup1 = Run1.build_polybius_lookup()
    print(lookup1)

    # Reading in the message to be encrypted from the
    # specified input file
    with open(input_file,'r') as f:
        message = f.read()

    # Getting rid of spaces
    message = message.replace(' ','')

    # Starting with an empty string and looping through
    # the letters of our plaintext message and sending each
    # to the lookup table to be encrypted and saved to digraph
    digraph_message = ""
    for m in message:
        digraph_message += lookup1[m] + ' '

    # Sending the digraphed message and key2 to next function
    # for the column transformations
    discombobulate(digraph_message,keyword2)    


# Function to perform column shifts on the encrypted polybius text
def discombobulate(message,keyword,**params):
  print(message)
  # Declaring new dictionary to assist with the column transformation
  matrix = {}
  key = keyword.upper()
  key_length = len(key)
  message_length = len(message)


  rows = math.ceil(float(message_length)/float(key_length))

  #   with open(input_file,'r') as f:
  #         message = f.read()

  message = message.replace(' ','')
  
  for k in key:
    matrix[k] = []
    

  i = 0
  for m in message:
      matrix[key[i]].append(m)
      i += 1
      i = i % len(key)
  
  print_matrix(matrix,rows,key)
  print_matrix(matrix,rows,key,True)

  sorted_key = sorted(key)

  for k in sorted_key:          # first loop = A
      for letter in matrix[k]:  # one letter in column A
        print(letter,end="")

  f = open("cipher.txt", "w") # Sending our encrypted text to an outfile
  for k in sorted_key:          # first loop = A
      for letter in matrix[k]:  # one letter in column A
        f.write(letter)
  f.close()


# Function to begin the decryption process
# receives the args/kwargs via **params
def decrypt(**params):
    """ Decrypt a message
    Params:
        input_file <string> 
        keyword1 <string>
        keyword2 <string>
    """
    print("We are DECRYPTING")
    input_file = params.get('input_file',None)
    keyword1 = params.get('keyword1',None)
    keyword2 = params.get('keyword2',None)

    print(f"Input File = {input_file}")
    print(f"Keyword 1 = {keyword1}")
    print(f"Keyword 2 = {keyword2}")
    

    # reads in the beginning encrypted message
    with open(input_file,'r') as f:
        message = f.read()
    

    # sends the message to reassemble function
    # to deconstruct the columnar shifting
    Reassemble(message, **params)


# function that receives the input message and begins
# to undo the columnar changes
def Reassemble(message,**params):
  print("Starting with our encrypted cipher text")
  print(message)
  keyword1 = params.get('keyword1',None)
  keyword2 = params.get('keyword2',None)


  # getting int values for length of the message
  # as well as length of key2
  En_message_length = len(message)
  Key2_length = len(keyword2)


  # The number of columns longer than normal can be 
  # determined by Modulo-ing the length of the message
  # with the length of keyword two. The remainder is the
  # amount of columns that are longer than normal.
  # We also know these start from the front of our key2
  Long_Column_Amount = En_message_length % Key2_length
  Col_Length = En_message_length / Key2_length


  # This gives us the length of our extra long columns
  Long_Col_Length = Col_Length + 1


  # Chopping off the decimals
  Col_Length = math.floor(Col_Length)
  Long_Col_Length = math.floor(Long_Col_Length)

  # Teclaring new dictionary necessary for understanding
  # the slice lengths of our message
  collengths = {}

  i = 0
  for c in keyword2:
    if i < Long_Column_Amount:
      collengths[c] = Long_Col_Length
    else:
      collengths[c] = Col_Length
    i = i + 1


  # Alphabetizing our key
  # Ex: ENIGMA becomes AEIGMN
  Sorted_Key = sorted(keyword2)

  # Declaring new dictionary to capture message slices
  R_Matrix = {}

  start = 0
  for k in Sorted_Key:
      end = collengths[k]
      R_Matrix[k] = list(message[start:end+start])
      start += end

  # Declaring a new list to capture our columnar sorted cipher text
  # Once the text is sorted into the correct order, we can begin to 
  # decrypt the message taking 2 characters at a time.
  Temp_Message_String = []

  for i in range(Long_Col_Length):
    for l in keyword2:
      if i == Long_Col_Length - 1:
        if len(R_Matrix[l]) < Long_Col_Length:
          continue
      Temp_Message_String += R_Matrix[l][i]

  # Declaring a new instance of polybius class
  Run2 = AdfgxLookup(keyword1)

  # Declaring a new polybius square using key1
  lookup2 = Run2.build_polybius_lookup()

  # Inverting the lookup table so the values read from Temp Message String
  # will correctly map to the designated decrypted letter
  # For example 'DD' mapping to 'a'
  inv_lookup2 = dict([(value, key) for key, value in lookup2.items()]) 

  # New string to capture the decrypted message
  decrypted_message = ""

  # Looping through the range of Temp Message String but with int values
  for j in range(0,len(Temp_Message_String),2):
    # '', join turns a list into a string
    decrypted_message += inv_lookup2[''.join(Temp_Message_String[j:j+2])]

  # Printing final decrypted message
  print(decrypted_message)

  # Writing result to the output file
  f = open("decrypted.txt", "w") # Sending our encrypted text to an outfile
  for k in decrypted_message:
        f.write(k)
  f.close()

# Function to alert user of how to use the program if incorrect values are used
# in the launching of the program
def usage(message=None):
    if message:
        print(message)
    print("Usage: python skeleton.py [key1=string] [key2=int] [key3=int] [keyX=sometype]")
    print("Example:\n\t python skeleton.py arg1 arg2 var1='Param 1' path=./some_path a=25 b=50\n")
    sys.exit()


if __name__=='__main__':
    """
    Main block
    """

    argv = sys.argv[1:] # strip file name (main.py) out of args

    # print usage if not called correctly
    # if len(argv) < required_params:
    #     usage()

    # get processed command line args
    args,program_params = mykwargs(argv)

    print(args)

    print(program_params)

    # Setting path based off of command in .replit file
    # incorrect/incomplete parameters receive a reminder
    # with a print out of the usage instructions
    if program_params['operation'] == 'Encrypt':
        encrypt(**program_params)
    else:
        decrypt(**program_params)
  


    