#pragma once
#include <vector>
#include <string>

namespace yacht {

enum class category {
  ones,
  twos,
  threes,
  fours,
  fives,
  sixes,
  full_house,
  four_of_a_kind,
  little_straight,
  big_straight,
  choice,
  yacht
};

int score(std::vector<int> const& dice, std::string const& cat);
int score(std::vector<int> const& dice, const char* cat);

}  // namespace yacht
