//
// Created by Bojan Roško on 9/25/19.
//
#include "grey_code.h"

uint64_t GreyCode(uint64_t n) {
  uint64_t val = 0;
  uint64_t mask = 1;
  while (mask <= n) {
    if (((n & mask) ^ ((n & (mask << 1u)) >> 1u)) != 0) val += mask;
    mask <<= 1u;
  }
  return val;
}

uint64_t GreyDecode(uint64_t n) {
  uint64_t mask = 1;
  while (mask <= n) mask <<= 1u;
  mask >>= 1u;

  uint64_t val = n & mask;
  mask >>= 1u;
  while (mask > 0) {
    if (((n & mask) ^ ((val & (mask << 1u)) >> 1u)) != 0) val += mask;
    mask >>= 1u;
  }
  return val;
}
