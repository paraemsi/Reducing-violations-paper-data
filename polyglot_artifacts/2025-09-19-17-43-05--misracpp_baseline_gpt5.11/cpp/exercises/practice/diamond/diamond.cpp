#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

namespace {
char normalize_letter(char letter) {
  unsigned char uc = static_cast<unsigned char>(letter);
  if (std::isalpha(uc)) {
    letter = static_cast<char>(std::toupper(uc));
  }
  if (letter < 'A' || letter > 'Z') {
    throw std::invalid_argument("letter must be an alphabetic character A-Z");
  }
  return letter;
}

std::string make_line(int n, int row) {
  // n: number of rows in top half including middle (A..letter), i.e., letter - 'A' + 1
  // row: 0-based index into top half (0 for 'A', n-1 for widest)
  const int width = 2 * n - 1;
  const int lead = (n - 1) - row;
  const int middle = row == 0 ? 0 : (2 * row - 1);
  const char ch = static_cast<char>('A' + row);

  std::string line;
  line.reserve(width);
  line.append(lead, ' ');
  line.push_back(ch);
  if (row > 0) {
    line.append(middle, ' ');
    line.push_back(ch);
  }
  line.append(lead, ' ');
  return line;
}
}  // namespace

std::vector<std::string> lines(char letter) {
  letter = normalize_letter(letter);
  const int n = (letter - 'A') + 1;
  const int size = 2 * n - 1;

  std::vector<std::string> out;
  out.reserve(size);

  // Top half including middle line
  for (int row = 0; row < n; ++row) {
    out.emplace_back(make_line(n, row));
  }
  // Bottom half
  for (int row = n - 2; row >= 0; --row) {
    out.emplace_back(make_line(n, row));
  }

  return out;
}

std::vector<std::string> rows(char letter) {
  return lines(letter);
}

std::string make(char letter) {
  const auto ls = lines(letter);
  if (ls.empty()) return std::string();

  // Join with '\n' without trailing newline
  std::size_t total = 0;
  for (const auto& s : ls) total += s.size();
  total += ls.size() - 1;

  std::string result;
  result.reserve(total);

  for (std::size_t i = 0; i < ls.size(); ++i) {
    if (i > 0) result.push_back('\n');
    result += ls[i];
  }
  return result;
}

}  // namespace diamond
