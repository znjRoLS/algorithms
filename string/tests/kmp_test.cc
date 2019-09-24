//
// Created by Bojan Roško on 9/24/19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "kmp.h"

TEST(kmp, kmp_simple_find
) {

  string haystack = "abcdloremipsum";
  string needle = "lorem";

  EXPECT_EQ(kmp(haystack, needle), 4);
}