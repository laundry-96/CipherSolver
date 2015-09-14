/**********************************************
** File:    CipherMessage.cpp
** Project: CMSC 202 Project 2, Spring 2015
** Author:  Austin DeLauney
** Date:    3/17/2015
** Section: 06
** E-mail:  adelau1@umbc.edu
**
** This file has all of the definitions to the methods in CipherMessage.h.
** The main part of this is the CaeserDecipher() and VigenereDecipher()
** methods because they are the main methods that run the program.
** Other methods in this are getters and setters or helpers
***********************************************/

/*
 * Template CipherMessage.cpp
 *
 * Students may NOT modify the provided constructors or LoadFromFile()
 * function.  Functions may be added AFTER LoadFromFile().
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>
#include <vector>
#include "Date.h"
#include "CipherMessage.h"

using namespace std;

CipherMessage::CipherMessage() 
  : m_text(""), m_from(""), m_to(""), m_sentDate(Date(1,1,1970))
{ /* Empty function body */ }

CipherMessage::CipherMessage(string from, string to, Date sentDate, string text) 
  : m_from(from), m_to(to), m_sentDate(sentDate)
{ 
  m_text = "";

  /* Only copy uppercase letters to m_text */

  for (int i = 0; i < text.length(); i++)
    if (text[i] >= 'A' && text[i] <= 'Z')
      m_text += text[i];
}

bool CipherMessage::LoadFromFile(string fileName) {
  ifstream dataFile;
  string from;
  string to;
  int month, day, year;
  char text_cstr[MAX_CIPHERLEN];
  string text;

  /* Set exception flags for file input stream */ 

  dataFile.exceptions(ios::failbit | ios::badbit);

  try {

    dataFile.open(fileName.c_str());

    /* Read from, to, month, day, year */

    dataFile >> from;
    dataFile >> to;
    dataFile >> month >> day >> year;

    /* Read text.  First getline() clears previous newline */

    dataFile.getline(text_cstr, MAX_CIPHERLEN);
    dataFile.getline(text_cstr, MAX_CIPHERLEN);

    /* Only copy uppercase letters to string */
    
    for (int i = 0; i < strlen(text_cstr); i++)
      if (text_cstr[i] >= 'A' && text_cstr[i] <= 'Z')
  text += text_cstr[i];

    dataFile.close();
  } 
  catch (exception e) {
    return false;
  }

  /* Made it through file read; assign to class variables. */

  m_from = from;
  m_to = to;
  m_sentDate = Date(month, day, year);
  m_text = text;

  return true;
}

string CipherMessage::Decipher()
{
  //Use vigenere cipher because it includes the 1 key caeser cipher
  return VigenereCipher(m_text);
}

string CipherMessage::Decipher(string key)
{
  if(key.length() == 1)
   return CaeserCipher(m_text, key[0]);

  else
    return VigenereCipher(m_text, key);
}

string CipherMessage::CaeserCipher(string text, char key) const
{
  string toReturn = "";

  for(int i = 0; i < text.length(); i++)
  {
    toReturn += CaeserCipherSingle(text[i], key);  //Add a deciphered character to toReturn
  }

  return toReturn;
}

string CipherMessage::VigenereCipher(string text)
{
  //Logs of all probable answers
  double logAnswers[MAX_KEYLEN];
  //All possible keys
  string keys[MAX_KEYLEN];
  //All deciphered texts
  string decipheredTexts[MAX_KEYLEN];

  //For each key length
  for(int keyLen = 1; keyLen <= MAX_KEYLEN; keyLen++)
  {
    //Splits text into manageble caeser ciphers
    string *vigenereCipherBreaks = new string[keyLen];
    SplitText(text, keyLen, vigenereCipherBreaks);

    //The to be viginere key
    string vigenereKey = ""; 

    //Letter frequencies for each caeser ciphers
    double letterFrequency[keyLen][ALPHALEN]; 

    //Find letter frequency then find key
    for(int i = 0; i < keyLen; i++)
    {
      InitializeLetterFrequency(letterFrequency[i], vigenereCipherBreaks[i]);
      vigenereKey += FindKey(vigenereCipherBreaks[i], letterFrequency[i]);
    }

    //Assigns key
    keys[keyLen-1] = vigenereKey;

    //Assings deciphered text
    decipheredTexts[keyLen-1] = VigenereStringContactinator(vigenereKey, vigenereCipherBreaks);

    //Assigns log of the deciphered text
    logAnswers[keyLen-1] = ProbableDecipher(decipheredTexts[keyLen-1]);
  }

  //Find the first vigenere key with logodds greater than 1 and return it
  for(int i = 0; i < MAX_KEYLEN; i++)
  {
    if(logAnswers[i] > 1)
    {
      return decipheredTexts[i];
    }
  }

  //If no key is found, dig our heads into the ground and 
  //return the first key and hope for the best
  return keys[0];
}

string CipherMessage::VigenereCipher(string text, string key)
{
  //Starts by breaking up the viginere cipher into ceaser cipher based on key length
  string *vigenereCipherBreaks = new string[(int)ceil(text.length() / key.length())];
  SplitText(text, key.length(), vigenereCipherBreaks);

  string toReturn = "";

  //Contactinates the string breaks together and deciphers it
  toReturn = VigenereStringContactinator(key, vigenereCipherBreaks);

  delete [] vigenereCipherBreaks;
  
  return toReturn;
}

char CipherMessage::CaeserCipherSingle(char character, char key) const
{
  int keyIndex = -1;           //Index of the key in ALPHABET
  int currentLetterIndex = -1; //Index of the character in ALPHABET

  //For every character in ALPHABET
  for(int j = 0; j < ALPHABET.length(); j++)
  {
    if(ALPHABET[j] == character)
    {
      currentLetterIndex = j;
    }

    if(ALPHABET[j] == key)
    {
      keyIndex = j;
    }
  }

  //Once the current letter index and the key index is found, 
  //we shift the letter over as much as the key and if it's
  //less than 0, we add 26

  int total = currentLetterIndex - keyIndex;

  if(total < 0)
    total += 26;

  //return the deciphered character
  return ALPHABET[total];
}

int CipherMessage::BiggestArraySize(string array[MAX_KEYLEN], int size) const
{
  int toReturn = 0;

  //For each string in array
  for(int i = 0; i < size; i++)
  {
    //If the string size is greater than the previous string
    if(array[i].length() > toReturn)
    {
      toReturn = array[i].length();
    }
  }

  return toReturn;
}

void CipherMessage::InitializeLetterFrequency(double letterFreq[], string text)
{
  //For each character in text
  for(int i = 0; i < text.length(); i++)
  {
    //Each letter will increase every time it hits that character
    letterFreq[text[i] - 65]++;
  }

  CalculateFrequency(letterFreq, text.length());
}

void CipherMessage::CalculateFrequency(double letterFreq[], int stringSize)
{
  for(int i = 0; i < ALPHALEN; i++)
  {
    //Divide the total count of a certain letter by the total string size
    letterFreq[i] = letterFreq[i] / stringSize;
  }
}

char CipherMessage::FindKey(string text, double letterFreq[])
{
  //Find all possible deciphered texts with all keys
  string offsettedTexts[ALPHALEN];
  for(int offset = 0; offset < ALPHALEN; offset++)
  {
    offsettedTexts[offset] = CaeserCipher(text, char(offset+65));
  }

  //Log odd probabilities of each ceaser cipher
  double textProbabilities[ALPHALEN];

  //Calculate each log odd
  for(int i = 0; i < ALPHALEN; i++)
  {
    textProbabilities[i] = ProbableDecipher(offsettedTexts[i]);
  }

  int highestProbKey = 0;

  //For each possible key
  for(int i = 0; i < ALPHALEN; i++)
  {
    //Get the highest text probability 
    if(textProbabilities[i] > textProbabilities[highestProbKey])
    {
      //And assign the key of that
      highestProbKey = i;
    }
  }

  //Return the key that had the highest probability
  return ALPHABET[highestProbKey];
}

void CipherMessage::SplitText(string text, int keyLen, string stringBreaks[])
{
  //Used ceil because text length will not always 
  //be divisible by keyLen, so we want to use the highest
  //Number in case of overflow
  int biggestStringSize = ceil(text.length() / keyLen);

  for(int column = 0; column <= biggestStringSize; column++)
  {
    for(int row = 0; row < keyLen; row++)
    {
      //If there is enough text to get
      if(column * keyLen + row < text.size())
      {
        //Add it to the row
        stringBreaks[row] += text[column * keyLen + row];
      }
    }
  }
}

double CipherMessage::ProbableDecipher(string text) const
{
  //toReturn is equal to 1 so when you multiply logs together it doesn't equal some other answer
  double toReturn = 1.0;

  for(int character = 0; character < text.length(); character++)
  {
    //Compare frequencies and multiply it to toReturn
    toReturn *= ALPHALEN * EN_FREQ[text[character] - 65];
  }
  //Return log of toReturn for a number that is pheasable
  return log10(toReturn);
}

string CipherMessage::VigenereStringContactinator(string key, string vigenereCipherBreaks[]) const
{
  string toReturn = "";

  int biggestStringSize = BiggestArraySize(vigenereCipherBreaks, key.length());

  //For each column, used <= because you want to include every character
  for(int col = 0; col <= biggestStringSize; col++)
  {
    //For each row
    for(int row = 0; row < key.length(); row++)
    {
      //If trying to access a column in the string of a row and it doesn't have it
      if(vigenereCipherBreaks[row].length() > col) //Stops out of bounds
      {
        //contactinates toReturn with a single character deciphered
        toReturn += CaeserCipherSingle(vigenereCipherBreaks[row][col], key[row]);
      }
    }
  }

  return toReturn;
}

string CipherMessage::GetText() const
{
  return m_text;
}

string CipherMessage::GetFrom() const
{
  return m_from;
}

string CipherMessage::GetTo() const
{
  return m_to;
}

Date CipherMessage::GetSentDate() const
{
  return m_sentDate;
}

void CipherMessage::SetText(string text)
{
  //Creates a string, and goes through text to find only capital letters to set
  string toSet = "";

  //For each character in text
  for(int i = 0; i < text.length(); i++)
  {
    //If uppercase
    if(65 <= text[i] && text[i] <= 90)
    {
      toSet += text[i];
    }
  }

  m_text = toSet;
}

void CipherMessage::SetFrom(string from)
{
  m_from = from;
}

void CipherMessage::SetTo(string to)
{
  m_to = to;
}

void CipherMessage::SetSentDate(const Date& sentDate)
{
  m_sentDate = sentDate;
}