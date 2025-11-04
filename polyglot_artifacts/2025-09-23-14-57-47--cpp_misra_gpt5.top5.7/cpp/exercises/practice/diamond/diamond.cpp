#include "diamond.h"

#include <array>
#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> make_diamond(letter_t letter) {
  static constexpr std::array<char, 26U> UPPER = {
      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  static constexpr std::array<char, 26U> LOWER = {
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

  std::size_t idx = 0U;
  bool found = false;

  for (std::size_t i = 0U; i < UPPER.size(); ++i) {
    if (letter == UPPER[i]) {
      idx = i;
      found = true;
      break;
    } else if (letter == LOWER[i]) {
      idx = i;
      found = true;
      break;
    } else {
      // continue
    }
  }

  if (!found) {
    return std::vector<std::string>();
  }

  const std::size_t size = (idx * 2U) + 1U;
  const std::size_t mid = idx;

  std::vector<std::string> lines;
  lines.reserve(size);

  auto make_row = [size, mid, idx, &UPPER](std::size_t r) -> std::string {
    std::string s(size, ' ');
    const char ch = UPPER[r];
    const std::size_t offset = r;
    const std::size_t left = (mid - offset);
    const std::size_t right = (mid + offset);

    s[left] = ch;
    if (left != right) {
      s[right] = ch;
    }

    return s;
  };

  for (std::size_t r = 0U; r <= idx; ++r) {
    lines.push_back(make_row(r));
  }
  for (std::size_t r = idx; r > 0U; --r) {
    lines.push_back(make_row(r - 1U));
  }

  return lines;
}

std::vector<std::string> rows(letter_t letter) {
  return make_diamond(letter);
}

}  // namespace diamond
