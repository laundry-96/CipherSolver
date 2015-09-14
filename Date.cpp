/**********************************************
** File:    Date.cpp
** Project: CMSC 202 Project 2, Spring 2015
** Author:  Austin DeLauney
** Date:    3/17/2015
** Section: 06
** E-mail:  adelau1@umbc.edu
**
** This file has all of the definitions to the methods in Date.h.
** The main part of this is the SetYear(), SetMonth(), and SetDay
** because in each of those methods you have to check for leap years
** and make sure that m_day, m_month, and m_year are always valid
***********************************************/

/*
 * Template Date.cpp
 *
 * Students must implement the entire class, including full handling
 * of leap years.
 */


#include <iostream>
#include <cstdio>
#include "Date.h"

using namespace std;

int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 29}; //Days of each month

Date::Date()
{
  //Set each parameter to lowest value
  m_month = 1;
  m_day = 1;
  m_year = 1970;
}

Date::Date(int month, int day, int year)
{
  //Set each parameter to lowest value so no errors get thrown while assigning actual values
  m_month = 1;
  m_day = 1;
  m_year = 1970;

  //Set each paramter to the one given
  SetMonth(month);
  SetYear(year);
  SetDay(day);
}

int Date::GetMonth() const
{
  return m_month;
}

int Date::GetDay() const
{
  return m_day;
}

int Date::GetYear() const
{
  return m_year;
}


void Date::SetMonth(int month)
{
  //It's February
  if(month == 2)
  {

    m_month = month;  //Set month

    //If it's a leap year
    if((GetYear() % 100 != 0 && GetYear() % 4 == 0) || (GetYear() % 100 == 0 && GetYear() % 400 == 0))
    {
      //If the day is within range of 29 because leap year
      if(1 <= GetDay() && GetDay() <= days[12]) //Using the amount of days in the leap year
      {
        //Do nothing because it's valid
      }

      //Day is not in range, set to 1
      else
      {
        printf("Day is invalid while setting month. setting m_day to 1\n");
        m_day = 1;
      }
    }

    //Not a leap year
    else
    {
      //If day is within range of normal days
      if(1 <= GetDay() && GetDay() <= days[GetMonth()-1]) //Using the amount of days in the leap year
      {
        //Nothing because it's valid
      }

      //Day is not valid, set to one
      else
      {
        printf("Day is invalid while setting month. setting m_day to 1\n");
        m_day = 1;
      }
    }
  }

  //If the month is any other month, February will be ignored
  else if(1 <= month && month <= 12)
  {

    m_month = month;  //Set month

    //If day is valid
    if(1 <= GetDay() && GetDay() <= days[GetMonth()-1])
    {
      //Nothing because it's valid
    }

    //If it's not a valid day
    else
    {
      printf("Day is invalid while setting month. setting m_day to 1\n");
      m_day = 1;
    }
  }

  //Not a valid month
  else
  {
    //Set month to one because it's not vaild and print error
    m_month = 1;
    printf("Month is invalid, setting to 1");

    //Check if day is valid
    if(1 <= GetDay() && GetDay() <= days[GetMonth()-1]) //Using the amount of days in the leap year
    {
      //Nothing because it's valid
    }

    //Set to day to one because it's not valid
    else
    {
      printf("Day is invalid while setting month. setting m_day to 1\n");
      m_day = 1;
    }
  }
}

void Date::SetDay(int day)
{
  if(GetMonth() == 2) //If the month is February, check if it's a leap year
  {
    //If it's a leap year
    if((GetYear() % 100 != 0 && GetYear() % 4 == 0) || (GetYear() % 100 == 0 && GetYear() % 400 == 0))
    {
      //Using the amount of days in the leap year
      if(1 <= day && day <= days[12]) 
      {
        m_day = day;
      }

      //Day is not valid, set to one
      else
      {
        printf("Day is invalid while setting month. setting m_day to 1\n");
        m_day = 1;
      }
    }

    //Not a leap year
    else
    {
      if(1 <= day && day <= days[GetMonth()-1]) 
      {
        m_day = day;
      }

      //Day is not valid, set to one
      else
      {
        printf("Day is invalid while setting month. setting m_day to 1\n");
        m_day = 1;
      }
    }
  }

  //If days are valid, won't work for February because that's already checked
  else if(1 <= day && day <=days[GetMonth() - 1]) //If the day is valid
  {
    m_day = day;
  }

  //Day is not valid
  else
  {
    printf("Day is invalid while setting month. setting m_day to 1\n");
    m_day = 1;
  }
}

void Date::SetYear(int year)
{
  //If year is within range
  if(MIN_YEAR <= year && year <= MAX_YEAR)
  {
    //Set year
    m_year = year;

    //If the month is February
    if(GetMonth() == 2)
    {
      //Check if it's a valid leap year
      if((GetYear() % 100 != 0 && GetYear() % 4 == 0) || (GetYear() % 100 == 0 && GetYear() % 400 == 0))
      {
        //If the day is valid
        if(1 <= GetDay() && GetDay() <= days[12])
        {
          //Do nothing because it's valid
        }

        //Day is not valid
        else
        {
          printf("Day is invalid while setting month. setting m_day to 1\n");
          m_day = 1;
        }
      }

      //Not a leap year
      else
      {
        //If day is valid
        if(1 <= GetDay() && GetDay() <= days[GetMonth()-1]) //Using the amount of regular days
        {
          //Nothing because it's valid
        }

        //Day is invalid
        else
        {
          printf("Day is invalid while setting month. setting m_day to 1\n");
          m_day = 1;
        }
      }
    }

    else
    {
      //If day is valid
      if(1 <= GetDay() && GetDay() <= days[GetMonth()-1]) //Using the amount of days for regular months
      {
        //Nothing because it's valid
      }

      //Day is invalid
      else 
      {
        printf("Day is invalid while setting month. setting m_day to 1\n");
        m_day = 1;
      }
    }
  }

  //Parameter year is invalid so set to min year
  else
  {
    printf("Year is not valid, setting to default year\n");
    m_year = MIN_YEAR;
  }
}


void Date::PrintDate() const
{
  //Print out date in month day year format
  printf("%d %d %d\n", GetMonth(), GetDay(), GetYear());
}
