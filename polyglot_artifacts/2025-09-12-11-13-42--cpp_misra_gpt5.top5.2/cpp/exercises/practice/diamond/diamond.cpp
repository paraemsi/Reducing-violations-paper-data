#include "diamond.h"

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace diamond {

namespace {

constexpr char space_ch = ' ';
constexpr char newline_ch = '\n';
constexpr std::string_view alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

}  // namespace

std::vector<std::string> rows(char letter) noexcept {
  const std::size_t pos = alphabet.find(letter);
  if ((pos == std::string_view::npos)) {
    return std::vector<std::string>();
  }

  const std::size_t n = (pos + static_cast<std::size_t>(1));
  const std::size_t width = ((static_cast<std::size_t>(2) * n) - static_cast<std::size_t>(1));
  const std::size_t center = (n - static_cast<std::size_t>(1));

  std::vector<std::string> result;
  result.reserve(((n * static_cast<std::size_t>(2)) - static_cast<std::size_t>(1)));

  for (std::size_t i = static_cast<std::size_t>(0); i < n; ++i) {
    std::string line(width, space_ch);

    const char row_ch = alphabet[i];

    const std::size_t left = (center - i);
    const std::size_t right = (center + i);

    line[left] = row_ch;
    line[right] = row_ch;

    result.push_back(line);
  }

  // Mirror the top half (excluding the middle line) to form the bottom half
  if ((n > static_cast<std::size_t>(1))) {
    for (std::size_t i = (n - static_cast<std::size_t>(2)); /*loop*/; --i) {
      result.push_back(result[i]);
      if ((i == static_cast<std::size_t>(0))) {
        break;
      }
    }
  }

  return result;
}

std::string make(char letter) noexcept {
  const std::vector<std::string> lines = rows(letter);

  const std::size_t count = lines.size();
  if ((count == static_cast<std::size_t>(0))) {
    return std::string();
  }

  const std::size_t width = lines[static_cast<std::size_t>(0)].size();
  const std::size_t total_chars = (((count * width) + (count - static_cast<std::size_t>(1))));

  std::string out;
  out.reserve(total_chars);

  for (std::size_t idx = static_cast<std::size_t>(0); idx < count; ++idx) {
    out += lines[idx];
    if (((idx + static_cast<std::size_t>(1)) < count)) {
      out.push_back(newline_ch);
    }
  }

  return out;
}

}  // namespace diamond
