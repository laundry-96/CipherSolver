#include <iostream>
#include "CipherMessage.h"
#include "Date.h"
// #include "../gtest-1.7.0/include/gtest/gtest.h"
#include "/afs/umbc.edu/users/c/m/cmarron/pub//gtest-1.7.0/include/gtest/gtest.h"

using namespace std;

TEST(Project2_BASIC, Date_DefaultConstructor_Accessor) {
  Date date;
  EXPECT_EQ(1, date.GetMonth());
  EXPECT_EQ(1, date.GetDay());
  EXPECT_EQ(1970, date.GetYear());
}

TEST(Project2_BASIC, Date_NonDefaultConstructor_Accessor) {

  Date date1(8, 13, 1988);
  EXPECT_EQ(8, date1.GetMonth());
  EXPECT_EQ(13, date1.GetDay());
  EXPECT_EQ(1988, date1.GetYear());

  Date date2(2, 30, MAX_YEAR + 10);
  EXPECT_EQ(2, date2.GetMonth());
  EXPECT_EQ(1, date2.GetDay());
  EXPECT_EQ(1970, date2.GetYear());

  Date date3(0, 32, 1983);
  EXPECT_EQ(1, date3.GetMonth());
  EXPECT_EQ(1, date3.GetDay());
  EXPECT_EQ(1983, date3.GetYear());
}  

TEST(Project2_BASIC, Date_Mutator) {
  Date date;

  date.SetMonth(2);
  date.SetYear(2004);
  date.SetDay(29);
  EXPECT_EQ(2, date.GetMonth());
  EXPECT_EQ(29, date.GetDay());
  EXPECT_EQ(2004, date.GetYear());

  date.SetYear(2100); // not a leap year
  date.SetDay(29);
  EXPECT_EQ(2100, date.GetYear());
  EXPECT_EQ(1, date.GetDay());

  date.SetYear(MIN_YEAR - 10);
  EXPECT_EQ(MIN_YEAR, date.GetYear());

  date.SetMonth(-1);
  EXPECT_EQ(1, date.GetMonth());
}

TEST(Project2_BASIC, CipherMessage_DefaultConstructor_Accessor) {
  CipherMessage cip;
  EXPECT_EQ("", cip.GetFrom());
  EXPECT_EQ("", cip.GetTo());
  EXPECT_EQ(1, cip.GetSentDate().GetMonth());
  EXPECT_EQ(1, cip.GetSentDate().GetDay());
  EXPECT_EQ(1970, cip.GetSentDate().GetYear());
  EXPECT_EQ("", cip.GetText());
}

TEST(Project2_BASIC, CipherMessage_NonDefaultConstructor_Accessor) {
  string from = "ALICE";
  string to   = "BOB";
  Date sDate(5, 3, 1989);
  string text = "THERAININSPAIN";
    
  CipherMessage cip(from, to, sDate, text);
  EXPECT_EQ(from, cip.GetFrom());
  EXPECT_EQ(to, cip.GetTo());
  EXPECT_EQ(5, cip.GetSentDate().GetMonth());
  EXPECT_EQ(3, cip.GetSentDate().GetDay());
  EXPECT_EQ(1989, cip.GetSentDate().GetYear());
  EXPECT_EQ(text, cip.GetText());
}

TEST(Project2_BASIC, CipherMessage_DefaultConstructor_Mutator) {
  CipherMessage cip;

  string from = "ALICE";
  cip.SetFrom(from);
  EXPECT_EQ(from, cip.GetFrom());

  string to   = "BOB";
  cip.SetTo(to);
  EXPECT_EQ(to, cip.GetTo());

  Date sDate(5, 2, 1992);
  cip.SetSentDate(sDate);
  EXPECT_EQ(5, cip.GetSentDate().GetMonth());
  EXPECT_EQ(2, cip.GetSentDate().GetDay());
  EXPECT_EQ(1992, cip.GetSentDate().GetYear());

  string text1 = "FALLSMAINLYONTHEPLAIN";
  cip.SetText(text1);
  EXPECT_EQ(text1, cip.GetText());

  string text2a = "THERE.IS invalid STUff HERE!";
  string text2b = "THEREISSTUHERE";
  cip.SetText(text2a);
  EXPECT_EQ(text2b, cip.GetText());
}

TEST(Project2_BASIC, CipherMessage_DecipherWithKey) {

  CipherMessage cip;

  cip.LoadFromFile("data/msg1.cip");
  string plain1 = "ISTAYUPTOOLATEGOTNOTHINGINMYBRAIN";
  EXPECT_EQ(plain1, cip.Decipher("Q"));

  cip.LoadFromFile("data/msg2.cip");
  string plain2 = "WORKITMAKEITDOITMAKESUSHARDERBETTERFASTERSTRONGER";
  EXPECT_EQ(plain2, cip.Decipher("DAFT"));
}


TEST(Project2_INTERMEDIATE, CipherMessage_Decipher) {

  CipherMessage cip;

  cip.LoadFromFile("data/msg1.cip");
  string plain1 = "ISTAYUPTOOLATEGOTNOTHINGINMYBRAIN";
  EXPECT_EQ(plain1, cip.Decipher());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
