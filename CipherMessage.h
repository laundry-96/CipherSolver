/**********************************************
** File:    CipherMessage.h
** Project: CMSC 202 Project 2, Spring 2015
** Author:  Austin DeLauney
** Date:    3/17/2015
** Section: 06
** E-mail:  adelau1@umbc.edu
**
** This file has all of the declarations of the methods defined in CipherMessage.cpp
***********************************************/

#ifndef CIPHERMESSAGE_H
#define CIPHERMESSAGE_H

/* 
 * Template CipherMessage.h
 *
 * Students may NOT modify the defined constants, provided class 
 * variables, or public portion of the class declaration.  You may 
 * add constants, if needed, and add functions or variables to the 
 * private section of the class declaration.
 */

#include <string>
#include <cmath>
#include "Date.h"
#include <vector>

using namespace std;

/* Constants for alphabet and letter frequencies 
   ALPHABET - allowed cipher and plain characters
   ALPHALEN - number of characters in alphabet
   EN_FREQ - frequencies of letters in English.
             EN_FREQ[0] - frequency of 'A'
       EN_FREQ[1] - frequency of 'B'
       etc.                                    */

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int ALPHALEN = 26;
const double EN_FREQ[ALPHALEN] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
          0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
          0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
          0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
          0.02758, 0.00978, 0.02361, 0.00150, 0.01974,
          0.00074};

/* Constants for cipher and keys
   MAX_KEYLEN - maximum length of Vigenere key
   MAX_CIPHERLEN - maximum length of cipher message  */

const int MAX_KEYLEN = 6;
const int MAX_CIPHERLEN = 1000;

class CipherMessage {

 public:

  /* CipherMessage() - default constructor
     Preconditions - None
     Postconditions - new CipherMessage object with m_to, m_from, m_text
       set to "" and m_sentDate set to 1/1/1970                          */
 
  CipherMessage();

  /* CipherMessage() - non-default constructor
     Preconditions - None
     Postconditions - new CipherMessage object with m_to, m_from, set to 
       user supplied strings, m_sentDate set to user supplied date.
       m_text set to uppercase letters from text (all other characters
       deleted).                                                         */

  CipherMessage(string from, string to, Date sentDate, string text);

  /* LoadFromFile() - load object data from a file
     Preconditions - specified data file contains four lines
       line 1 - FROM information, no whitespace
       line 2 - TO information, no whitespace
       line 3 - SENTDATE information, mm dd yyyy (3 integers separated
         by spaces)
       line 4 - CIPHER data
     Postconditions - m_from, m_to, m_sentDate set to values in file.
       Only uppercase letters from cipher data are copied to m_text.
       If there is an error reading the file or if the date info
       is invalid, the class variables are unchanged.                    */

  bool LoadFromFile(string fileName);

  /* Decipher() - decipher the message 
     Preconditions - valid cipher in m_text
     Postconditions - best attempt at decryption OR failure message
       returned.                                                         */

  string Decipher();

  /* Decipher() - decipher the message with the given key
     Preconditions - valid cipher in m_text and correct key passed.
     Postconditions - decryption of m_text with key is returned.         */

  string Decipher(string key);

  /* GetText(), GetFrom(), GetTo(), GetSentDate() - standard accessors 
     Precondtions - none
     Postconditinos - returns value of class variable                    */

  string GetText() const;
  string GetFrom() const;
  string GetTo() const;
  Date GetSentDate() const;

  /* SetText() - standard mutator
     Preconditions - valid cipher passed as argument
     Postcondition - uppercase letters of text are copied to m_text    */

  void SetText(string text);

  /* SetFrom(), SetTo(), SetSentDate() - standard mutators
     Preconditions - valid data passed as argument
     Postconditions - class variable set to argument value              */

  void SetFrom(string from);
  void SetTo(string to);
  void SetSentDate(const Date& sentDate);

 private:
  string m_text;      // Contains cipher text
  string m_from;      // Contains sender info
  string m_to;        // Contains recipient info
  Date m_sentDate;    // Contains message sent date


  /* ADD VARIABLES HERE, IF NEEDED */

  /* ADD FUNCTIONS HERE, IF NEEDED */

  /*
   * CaserCipher(string text, char key) const
   * Deciphers text with the key
   * Pre  :Text is all uppercase letters, key is an uppercase letter
   * Post :None
   * @return :Deciphered string with given key 
   */
  string CaeserCipher(string text, char key) const;

  /*
   * string VigenereCipher(string text, string key)
   * Decipher text with the key
   * Pre  :Text all uppercase letters, key is uppercase letters aswell
   * Post :None
   * @return :Deciphered text with the given key
   */
  string VigenereCipher(string text, string key);

  /*
   * CaeserCipherSingle(char character, char key) const
   * Decipher a single character with the given key
   * Pre  :Character and key is uppercase
   * Post :None
   * @return :Returns the character deciphered with the given key
   */
  char CaeserCipherSingle(char character, char key) const;

  /*
   * int BiggestArraySize(string array[MAX_KEYLEN], int size) const
   * Finds the biggest string in array and returns it
   * Pre  :Array must have a max size of MAX_KEYLEN
   * Post :None
   * @return :Returns the size of the biggest string in array
   */
  int BiggestArraySize(string array[MAX_KEYLEN], int size) const;

  /* 
   * string CaeserCipher(string text)
   * Finds the key and deciphers text with it
   * Pre  :Text is all uppercase characters
   * Post :None
   * @return :Returns text deciphered with (hopefully) the proper key
   */
  string CaeserCipher(string text);

  /*
   * string VigenereCipher(string text)
   * Decipheres a vigenere cipher with no key
   * Pre  :Text is all uppercase, and text is big enough to have a key guessed propperly
   */
  string VigenereCipher(string text);

  /*
   * char FindKey(string text, double letterFreq[])
   * Finds the best match at a key (single character) for text using letterFreq
   * Pre  :Text must be all uppercase and letterFreq must be filled with the letter frequencies in text
   * Post :None
   * @return :Returns the key for the given string
   */
  char FindKey(string text, double letterFreq[]);

  /*
   * double ProbableDecipher(string text) const
   * It takes the string and multiplies the frequencies together, and then takes the log
   * Pre  :Text must be all uppercase and correspond to the frequencies in letterFreq.
   * Post :None
   * @return :Returns the log of the multiplied frequencies
   */
  double ProbableDecipher(string text) const;

  /*
   * void InitializeLetterFrequency(double letterFreq[], string text)
   * Tallies up each letter in text and sets it to letterFreq[], then calls CalculateFrequency(letterFreq[], text.size())
   * Pre  :LetterFreq must be empty with a size of ALPHALEN, and text must be all uppercase
   * Post :LetterFreq will have proper frequencies for the given text
   */
  void InitializeLetterFrequency(double letterFreq[], string text);

  /*
   * void CalculateFrequency(double letterFreq[], int stringSize)
   * Divides the tally of letters in letterFreq[] by stringSize
   * Pre  :LetterFreq[] must have the number of occurences of letters in alphabetical order
   * Post :LetterFreq[] will have decimals of the frequency
   */
  void CalculateFrequency(double letterFreq[], int stringSize);

  /*
   * void SplitText(string text, int keyLen, string stringBreaks[])
   * Splits text into a string array size of keyLen
   * Pre  :Text must be all uppercase, keyLen must be 1 <= MAX_KEYLEN, stringBreaks[] must be initalized (not filled)
   * Post :Each string in StringBreaks will be filled with text at every keyLen
   */
  void SplitText(string text, int keyLen, string stringBreaks[]);

  /*
   * string VigenereStringContactinator(string key, string vigenereCipherBreaks[])
   * Adds the strings from vigenereCipherBreaks[] together. Adds rows first, then moves down column
   * Pre  :Key must be greater than 0, and vigenereCipherBreaks must not be empty
   * Post :None
   * @return :A properly deciphered vigenere text based on the key
   */
  string VigenereStringContactinator(string key, string vigenereCipherBreaks[]) const;
};

#endif