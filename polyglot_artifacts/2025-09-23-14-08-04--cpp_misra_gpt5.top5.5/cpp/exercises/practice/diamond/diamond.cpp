#include "diamond.h"

#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
  // Validate input range using character traits to avoid direct char arithmetic.
  const std::int32_t code_c = static_cast<std::int32_t>(std::char_traits<char>::to_int_type(letter));
  const std::int32_t code_a = static_cast<std::int32_t>(std::char_traits<char>::to_int_type('A'));
  const std::int32_t code_z = static_cast<std::int32_t>(std::char_traits<char>::to_int_type('Z'));

  std::vector<std::string> lines;

  if ((code_c < code_a) || (code_c > code_z)) {
    return lines;
  } else {
    // continue
  }

  const std::uint32_t n = static_cast<std::uint32_t>(code_c - code_a);
  const std::uint32_t width = ((static_cast<std::uint32_t>(2U) * n) + static_cast<std::uint32_t>(1U));

  // Alphabet lookup avoids arithmetic on character types.
  static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  lines.reserve(static_cast<std::size_t>(width));

  // Top (including middle) lines
  for (std::uint32_t i = static_cast<std::uint32_t>(0U); (i <= n); ++i) {
    std::string line(static_cast<std::size_t>(width), ' ');

    const std::uint32_t left = (n - i);
    const std::uint32_t right = (n + i);
    const char ch = alphabet[static_cast<std::size_t>(i)];

    line[static_cast<std::size_t>(left)] = ch;
    line[static_cast<std::size_t>(right)] = ch;

    lines.emplace_back(line);
  }

  // Bottom lines (excluding middle)
  if (n != static_cast<std::uint32_t>(0U)) {
    for (std::uint32_t i = (n - static_cast<std::uint32_t>(1U)); ; --i) {
      std::string line(static_cast<std::size_t>(width), ' ');

      const std::uint32_t left = (n - i);
      const std::uint32_t right = (n + i);
      const char ch = alphabet[static_cast<std::size_t>(i)];

      line[static_cast<std::size_t>(left)] = ch;
      line[static_cast<std::size_t>(right)] = ch;

      lines.emplace_back(line);

      if (i == static_cast<std::uint32_t>(0U)) {
        break;
      } else {
        // continue
      }
    }
  } else {
    // Single-line diamond (A)
  }

  return lines;
}

std::string make(char letter) {
  const std::vector<std::string> lines = rows(letter);

  if (lines.empty()) {
    return std::string();
  } else {
    // continue
  }

  // Join lines with '\n' but no trailing newline.
  std::string result;

  const std::size_t line_count = lines.size();

  std::size_t capacity = static_cast<std::size_t>(0U);
  for (std::size_t idx = static_cast<std::size_t>(0U); (idx < line_count); ++idx) {
    capacity = capacity + lines[idx].size();
  }
  if (line_count > static_cast<std::size_t>(1U)) {
    capacity = capacity + (line_count - static_cast<std::size_t>(1U));
  } else {
    // no extra capacity for newlines
  }

  result.reserve(capacity);

  for (std::size_t idx = static_cast<std::size_t>(0U); (idx < line_count); ++idx) {
    result += lines[idx];
    if (((idx + static_cast<std::size_t>(1U)) < line_count)) {
      result.push_back('\n');
    } else {
      // last line: no trailing newline
    }
  }

  return result;
}

}  // namespace diamond
