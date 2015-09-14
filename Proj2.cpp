/**********************************************
** File:    Proj2.cpp
** Project: CMSC 202 Project 2, Spring 2015
** Author:  Austin DeLauney
** Date:    3/17/2015
** Section: 06
** E-mail:  adelau1@umbc.edu
**
** This file is the main driver of the Caeser and Vigenere Cipher program.
** It prints out if a file is loaded or not, and proceeds to take commands
** from the user. 
***********************************************/

#include <cstdio>
#include <iostream>
#include <string>
#include "CipherMessage.h"
#include "Proj2.h"

using namespace std;

int main()
{
  string fileName = ""; //Name of the file
  char selection = '\0'; //Current selection is null
  CipherMessage message; //Create a CipherMessage object

  //While user wants to keep going
  while(selection != 'q') 
  {
    printf("\n");
    loadFile(&message, &fileName, false);
    printf("\n");

    //Print the options and take user input
    printOptions();
    selection = takeSelection();

    //Switch through the users selection
    switch(selection)
    {
      //Load file
      case('l'): 
        printf("Enter the file name: ");
        cin >> fileName;
        loadFile(&message, &fileName, true);
        break;

      //Print header
      case('h'):
        printHeader(&message);
        break;

      //Print ciphered text
      case('t'):
        printf("%s\n", message.GetText().c_str());
        break;

      //Print deciphered text with certain key
      case('d'):
      {
        printf("Please give me the encryption key: ");
        string key = "";
        cin >> key;
        printf("%s\n", message.Decipher(key).c_str());
        break;
      }

      //Guess key and print message
      case('u'):
        printf("%s\n", message.Decipher().c_str());
        break;

      //Quit program
      case('q'):
        printf("Goodbye!\n");
    }
  }

  //Return with no errors
  return 0;
}

void printOptions()
{
  //Print all options possible
  printf("Choose an action from the following menu: \n\n");
  printf(" l - load a cipher file\n");
  printf(" h - display cipher file header\n");
  printf(" t - display cipher file text\n");
  printf(" d - decipher file with known key\n");
  printf(" u - decipher file with unknown key\n");
  printf(" q - quit\n");
}

char takeSelection()
{
  char selection = '\0';      //Selection
  bool properSelection = false;  //Current selection is '\0', so not valid

  //While we don't have a proper selection
  while(!properSelection)
  {
    //Get selection
    printf("Selection: ");
    cin >> selection;

    switch(selection)
    {
      //If proper selection set properSelection true to break loop
      case('l'): case('h'): case('t'):
      case('d'): case('u'): case('q'):
        properSelection = true;
        break;

      //Not a proper selection, keep it false and print error
      default: 
        printf("ERROR! Please select again!\n");
        break;
    }
  }

  return selection;
}

void loadFile(CipherMessage* message, string* fileName, bool calledFromSwitch)
{
  if("" == *fileName)
  {
    printf("There is no cipher file loaded\n");
  }

  //If able to load file
  else if(message -> LoadFromFile(*fileName))
  {
    //If it's not called from the switch statement, write the loaded file
    if(!calledFromSwitch)
      printf("The cipher file %s is currently loaded.\n", fileName -> c_str());
  }

  //Error in loading file
  else
  {
    printf("Error loading the cipher file (%s)\n", fileName -> c_str());
  }
}

void printHeader(CipherMessage* message)
{
  //Prints header of message
  printf("From: %s\n", message -> GetFrom().c_str());
  printf("To: %s\n", message -> GetTo().c_str());
  printf("Date: "); message -> GetSentDate().PrintDate();
}