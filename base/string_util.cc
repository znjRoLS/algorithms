//
// Created by Bojan Roško on 9/24/19.
//

#include "string_util.h"

#include <sstream>

namespace string_util {
std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  auto result = std::back_inserter(elems);
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    *(result++) = item;
  }
  return elems;
}
}