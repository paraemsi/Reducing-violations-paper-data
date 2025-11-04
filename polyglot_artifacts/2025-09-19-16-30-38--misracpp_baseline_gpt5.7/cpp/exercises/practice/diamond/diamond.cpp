#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
  // Normalize to uppercase if alphabetic.
  unsigned char u = static_cast<unsigned char>(letter);
  if (std::isalpha(u)) {
    letter = static_cast<char>(std::toupper(u));
  }
  if (letter < 'A' || letter > 'Z') {
    throw std::invalid_argument("letter must be between 'A' and 'Z'");
  }

  const int n = letter - 'A';
  const int size = 2 * n + 1;  // width == height

  auto make_line = [&](int i) -> std::string {
    // i indicates which letter row (0 for 'A', n for input letter)
    std::string line(static_cast<size_t>(size), ' ');
    const int center = n;
    const char c = static_cast<char>('A' + i);

    if (i == 0) {
      line[center] = 'A';
    } else {
      line[center - i] = c;
      line[center + i] = c;
    }
    return line;
  };

  std::vector<std::string> lines;
  lines.reserve(static_cast<size_t>(size));

  // Top half including middle.
  for (int i = 0; i <= n; ++i) {
    lines.push_back(make_line(i));
  }
  // Bottom half excluding middle.
  for (int i = n - 1; i >= 0; --i) {
    lines.push_back(make_line(i));
  }

  return lines;
}

std::string make_diamond(char letter) {
  const auto lines = rows(letter);
  // Join with '\n' without a trailing newline.
  std::string out;
  if (!lines.empty()) {
    const std::size_t size = lines.size();
    out.reserve(size * (lines[0].size() + 1));
  }
  for (std::size_t i = 0; i < lines.size(); ++i) {
    out += lines[i];
    if (i + 1 < lines.size()) out.push_back('\n');
  }
  return out;
}

}  // namespace diamond
