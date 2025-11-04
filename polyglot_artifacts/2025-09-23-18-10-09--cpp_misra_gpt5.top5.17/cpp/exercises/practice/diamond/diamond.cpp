#include "diamond.h"

#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

namespace {
constexpr std::uint32_t kAlphabetLength = static_cast<std::uint32_t>(26);
const char kUppercaseAlphabet[static_cast<std::size_t>(kAlphabetLength) + static_cast<std::size_t>(1U)] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char kLowercaseAlphabet[static_cast<std::size_t>(kAlphabetLength) + static_cast<std::size_t>(1U)] =
    "abcdefghijklmnopqrstuvwxyz";
}  // namespace

std::string make_diamond(const char letter) {
  // Determine index of the supplied letter within the alphabet (case-insensitive).
  std::uint32_t letter_index = static_cast<std::uint32_t>(0);
  bool found = false;

  for (std::uint32_t i = static_cast<std::uint32_t>(0); (i < kAlphabetLength); ++i) {
    if (letter == kUppercaseAlphabet[static_cast<std::size_t>(i)]) {
      letter_index = i;
      found = true;
      break;
    } else {
      if (letter == kLowercaseAlphabet[static_cast<std::size_t>(i)]) {
        letter_index = i;
        found = true;
        break;
      } else {
        // continue
      }
    }
  }

  if (!found) {
    // Not an ASCII alphabet character.
    return std::string();
  }

  const std::uint32_t max_offset = letter_index;
  const std::uint32_t width = (static_cast<std::uint32_t>(2) * max_offset) + static_cast<std::uint32_t>(1);
  const std::uint32_t last_index = width - static_cast<std::uint32_t>(1);

  std::string result;

  for (std::uint32_t row = static_cast<std::uint32_t>(0); (row < width); ++row) {
    const std::uint32_t asc_index = (row <= max_offset) ? row : (last_index - row);
    const std::uint32_t left_pos = max_offset - asc_index;
    const std::uint32_t right_pos = max_offset + asc_index;

    std::string line(static_cast<std::size_t>(width), ' ');
    const char ch = kUppercaseAlphabet[static_cast<std::size_t>(asc_index)];
    line[static_cast<std::size_t>(left_pos)] = ch;
    line[static_cast<std::size_t>(right_pos)] = ch;

    result += line;
    if (((row + static_cast<std::uint32_t>(1)) < width)) {
      result += '\n';
    } else {
      // No trailing newline on the last line.
    }
  }

  return result;
}

std::vector<std::string> rows(const char letter) {
  const std::string combined = make_diamond(letter);
  std::vector<std::string> out;
  if (combined.empty()) {
    return out;
  }

  std::size_t start = static_cast<std::size_t>(0);
  for (std::size_t i = static_cast<std::size_t>(0); (i < combined.size()); ++i) {
    if (combined[static_cast<std::size_t>(i)] == '\n') {
      out.emplace_back(combined.substr(start, i - start));
      start = i + static_cast<std::size_t>(1U);
    } else {
      // continue scanning
    }
  }
  // Add the last line after the final newline (or the only line when no newline)
  out.emplace_back(combined.substr(start));
  return out;
}

}  // namespace diamond
