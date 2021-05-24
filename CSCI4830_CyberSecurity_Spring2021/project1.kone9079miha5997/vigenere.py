# Michael V. Hasenkamp IDENTIKEY: MIHA5997
#Kolin Newby IDENTIKEY: KONE9079
import sys
from collections import Counter
# Reference: https://github.com/drewp41/Vigenere-Cipher-Breaker/blob/master/Vigenere_cipher.py


alphabet = 'abcdefghijklmnopqrstuvwxyz'


letter_freqs = [0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
              0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
              0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
              0.00978, 0.02360, 0.00150, 0.01974, 0.00074]


# This equation was found https://alexbarter.com/statistics/index-of-coincidence/ and it finds the probability that two letters from a text are the same. Each letter will have a 1 in 26 chance or a 1 in the len of alphabet used. It is the sum from i equals A to Z of (F_i)^(2). F is frequency. 
def Colision_index(cipher):

    M = float(len(cipher))
    frequency_sum = 0.0
    for letter in alphabet:
        frequency_sum+= cipher.count(letter) * (cipher.count(letter)-1)
    ic_val = frequency_sum/(M*(M-1))
    return ic_val

# This takes in the ciphertext passed in from main and creates a coincidence array to track the number of coincidences in the ciphertext. In the for loop we split the ciphertext into a sequence of length between the guessed key length and the Max_Key_Length variable. We spit the cipher by the quess length and the largest coincidence index which is most likely the key length. 
def key_length_finder(cipher):
    MAX_LENGTH_GUESS_FOR_KEY = 21
    icArray=[]
    for guess_length in range(MAX_LENGTH_GUESS_FOR_KEY):
        sum_IC=0.0
        ic_AVG=0.0
        for i in range(guess_length):
            sequence=""
            for j in range(0, len(cipher[i:]), guess_length):
                sequence += cipher[i+j]
                # print("sequence: ", sequence)
            sum_IC+=Colision_index(sequence)
        if not guess_length ==0:
            ic_AVG=sum_IC/guess_length
        icArray.append(ic_AVG)
    B_GUESS = icArray.index(sorted(icArray, reverse = True)[0]) #Best Guess is B_Guess
    S_B_GUESS = icArray.index(sorted(icArray, reverse = True)[1]) #Second Best Guess is S_B_GUES
    if B_GUESS % S_B_GUESS != 0:
        return B_GUESS
    else:
        return S_B_GUESS


#This function analysis the frequency atwhich letters in our cipher coincided, thus making it possible to determine the appropriate value in the index of the key. First we find the key length and then we find the letter in the index of the key by using this function. We know that letters appear with a certian frequency in the english language thus applying this fequency for a given letter in our cipher squared devided by that same letter frequency of that letter we get the likelyhood that it will appear by using the chi squared statistic we can get the likelyhood two probablity distributions are. Here is a source to what the chi squared statistic does. https://www.statisticshowto.com/probability-and-statistics/chi-square/
# In Short it stakes the sum of the observed value minus the expected value squered devided by the expected value and that results in the difference between the observed and expected frequencies. 
def Analysis_frequence(sequence):
    all_chi_squareds = [0] * 26 #makes and array to hold the statistic measurement at each index
    i=0
    while i in range(26):
    
        chiSquaredSum = 0.0
        offset_Sequence = [chr(((ord(sequence[j])-97-i)%26)+97) for j in range(len(sequence))]
        v = [0] * 26
        
        for l in offset_Sequence:
            v[ord(l) - ord('a')] += 1
        for j in range(26):
            v[j] *= (1.0/float(len(sequence)))
        for j in range(26):
            chiSquaredSum+=((v[j] - float(letter_freqs[j]))**2)/float(letter_freqs[j])
        all_chi_squareds[i] = chiSquaredSum
        i+=1
    shift = all_chi_squareds.index(min(all_chi_squareds))
    return chr(shift+97)

# Takes in the ciphertext and our key length which was found in the key_length function. 
#passes it into a for loop that has an empty string sequence that will be populated by the ciphertext split apart by the length of the key and the key is then determend by the frequency analysis of the sequence as that will return the most likely letter to be in that spot of the key.
def Likely_key_algo(cipher, key_length):
    Likely_key = '' #creats empty string 
    i=0
    while i in range(key_length): # runs the length of the key length 
        sequence="" # creats empy string
        for j in range(0,len(cipher[i:]), key_length): #runs the length of 0 to cipher index, and skips by size key length
            sequence+=cipher[i+j]
        Likely_key+=Analysis_frequence(sequence) # calls frequency analysis function to find the individual letters in the given index of the key.
        i+=1
        #print("sequence: ", sequence) This was just used to test that it was doing what I wanted it to do and as a sanity check 
    return Likely_key # return the most likely key

# decrypt function takes in the key and the cipher text and changes the cipher text and the key into ascii chars creates an array to hold the plaintext in ascii. The for loop runs for length of the ciphertext and what it does is it appends the plaintext array with values it calulates by subtracting and moding with the key langth and alphabet size the key ascii value from the cipher ascii value this shifting it back to its plain text form. Then it changes the plain text ascii array back into chars and sets plaintext variable equal to that and retruns that. 
def decrypt_algo(cipher, Likely_key):
    c_ascii = [ord(letter) for letter in cipher] #This is the cipher in ascii
    k_ascii = [ord(letter) for letter in Likely_key] #This is the key in ascii
    p_ascii = [] #This is the array that will hold the ascii values of what the decrypted message is, which will then be converted back into plain chars. in the line that reads plain.
    i=0
    while i in range(len(c_ascii)):
   
        p_ascii.append(((c_ascii[i]-k_ascii[i % len(Likely_key)]) % 26) +97)
        i+=1
    plain = ''.join(chr(i) for i in p_ascii) #plain text converted back into chars from ascii representation
    return plain
#Our main works by creating a input string for our cipher then in it takes int he file being passed in from terminal. 
#Then we set a variable for the un filtered ciphertext equal to the cipher text string we created. This will serve as the length of our forloop for assigning the ciphertext var. 
def main():
    input_cipher = ""
#This code was provided by the poject to read in the file
    for line in sys.stdin:
        input_cipher = input_cipher + line
    input_cipher = input_cipher.replace(" ", "").replace("\n", "").upper()    
##############################################################################################
    ciphertext_unfiltered = input_cipher # this is used to run our for loop the length of the ciphertext
    ciphertext = ''.join(x.lower() for x in ciphertext_unfiltered if x.isalpha())	
    key_length=key_length_finder(ciphertext)
    key = Likely_key_algo(ciphertext, key_length)
    plaintext = decrypt_algo(ciphertext, key)
    print(key)
##############################################################################################
if __name__ == '__main__':
    main()