#include "diamond.h"

#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> make(char const letter) {
  const std::string upper{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  const std::string lower{"abcdefghijklmnopqrstuvwxyz"};

  std::size_t idx = upper.find(letter);
  if ((idx == std::string::npos)) {
    idx = lower.find(letter);
    if ((idx == std::string::npos)) {
      return std::vector<std::string>{};
    }
  }

  const std::size_t zero = static_cast<std::size_t>(0U);
  const std::size_t one = static_cast<std::size_t>(1U);
  const std::size_t two = static_cast<std::size_t>(2U);

  const std::size_t width = ((idx * two) + one);
  const std::size_t mid = idx;

  std::vector<std::string> lines;
  lines.reserve(width);

  for (std::size_t row = zero; (row < width); ++row) {
    std::size_t k = zero;
    if ((row <= mid)) {
      k = row;
    } else {
      k = ((two * mid) - row);
    }

    std::string line(width, ' ');

    const char ch = upper[static_cast<std::size_t>(k)];

    const std::size_t left = (mid - k);
    const std::size_t right = (mid + k);

    line[left] = ch;
    if ((k != zero)) {
      line[right] = ch;
    }

    lines.push_back(line);
  }

  return lines;
}

std::vector<std::string> rows(char const letter) {
  return make(letter);
}

}  // namespace diamond
