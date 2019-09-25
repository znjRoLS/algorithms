//
// Created by Bojan Roško on 9/25/19.
//
#include "gtest/gtest.h"
#include "grey_code.h"

TEST(GreyCode, SimpleTest) {
  ASSERT_EQ(GreyCode(0), 0);
  ASSERT_EQ(GreyCode(1), 1);
  ASSERT_EQ(GreyCode(2), 3);
  ASSERT_EQ(GreyCode(3), 2);
  ASSERT_EQ(GreyCode(4), 6);
  ASSERT_EQ(GreyCode(5), 7);
  ASSERT_EQ(GreyCode(6), 5);
  ASSERT_EQ(GreyCode(7), 4);
  ASSERT_EQ(GreyCode(8), 12);
  ASSERT_EQ(GreyCode(9), 13);
  ASSERT_EQ(GreyCode(10), 15);
  ASSERT_EQ(GreyCode(11), 14);
  ASSERT_EQ(GreyCode(12), 10);
  ASSERT_EQ(GreyCode(13), 11);
  ASSERT_EQ(GreyCode(14), 9);
  ASSERT_EQ(GreyCode(15), 8);

  for (int i = 0; i < 100; i++) {
    ASSERT_EQ(i, GreyDecode(GreyCode(i)));
  }

}