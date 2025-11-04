#include "diamond.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

static inline char normalize_letter(char letter) {
  unsigned char u = static_cast<unsigned char>(letter);
  char up = static_cast<char>(std::toupper(u));
  if (up < 'A' || up > 'Z') {
    throw std::invalid_argument("letter must be in range A..Z (case-insensitive)");
  }
  return up;
}

std::vector<std::string> rows(char letter) {
  char L = normalize_letter(letter);
  int n = L - 'A';
  int size = 2 * n + 1;

  std::vector<std::string> out;
  out.reserve(size);

  for (int i = 0; i < size; ++i) {
    int j = (i <= n) ? i : (2 * n - i);
    char ch = static_cast<char>('A' + j);

    std::string line(size, ' ');
    int left = n - j;
    int right = n + j;
    line[left] = ch;
    if (left != right) {
      line[right] = ch;
    }
    out.push_back(std::move(line));
  }

  return out;
}

std::string make(char letter) {
  auto lines = rows(letter);
  if (lines.empty()) return std::string();
  std::string s;
  // Precompute total size: sum lengths + (lines-1) newlines
  size_t total = 0;
  for (const auto& line : lines) total += line.size();
  total += lines.size() - 1;
  s.reserve(total);
  for (size_t i = 0; i < lines.size(); ++i) {
    if (i) s.push_back('\n');
    s += lines[i];
  }
  return s;
}

}  // namespace diamond
