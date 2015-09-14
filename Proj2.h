/**********************************************
** File:    Proj2.h
** Project: CMSC 202 Project 2, Spring 2015
** Author:  Austin DeLauney
** Date:    3/17/2015
** Section: 06
** E-mail:  adelau1@umbc.edu
**
** This file contains methods that are used to help keep the cleanness of the code in main().
** Has helper methods so the main program doesn't need to be convoluted
***********************************************/
#ifndef PROJ2_H
#define  PROJ2_H
//Proj2.hpp
//Made by Austin DeLauney
//Date: Tuesday, March 17, 2015
//Header file for Proj2.cpp

#include <cstdio>
#include <iostream>
#include <string>
#include "CipherMessage.h"

using namespace std;

/*
  Start of the program
  Pre:  None
  Post: Complete execution of program
 */
int main();

/*
  Prints option that the program can do
  Pre:  None
  Post: Options displayed to screen
 */
void printOptions();

/*
  Gets user input from user regarding which action they want
  Pre:  Options displayed to screen
  Post: None
  @return: Returns a valid selection for an acrtion
 */
char takeSelection();

/*
  Loads a file into the CioherMessage pointer, prints out if there is any file loaded, 
  Pre:  User must've selected to load file
  Post: Attempt to load file into message
 */
void loadFile(CipherMessage* message, string* fileName, bool loadedFromSwitch);

/*
  Prints header from message
  Pre:  Message must have a loaded file
  Post: Prints out header of cipher file to command line
 */
void printHeader(CipherMessage* message);

/*
  Prints out ciphered text from message
  Pre:  Loaded file in message
  Post: Prints out the ciphered text to command line
 */
void printCipheredMessage(CipherMessage* message);

/*
  Prints decrypted message, and will take a key if wanted
  Pre:  Loaded file in message 
  Post: Prints out decrypted text of the message
 */
void printTextDeciphered(CipherMessage* message, char key = '\0');
#endif