#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

static char normalize_letter(char letter) {
  unsigned char uc = static_cast<unsigned char>(letter);
  char up = static_cast<char>(std::toupper(uc));
  if (up < 'A' || up > 'Z') {
    throw std::invalid_argument("letter must be in range 'A'..'Z'");
  }
  return up;
}

std::vector<std::string> make(char letter) {
  char L = normalize_letter(letter);
  int n = L - 'A';
  int size = 2 * n + 1;

  std::vector<std::string> lines;
  lines.reserve(size);

  auto make_row = [&](int i) {
    std::string row(size, ' ');
    int lead = n - i;
    char ch = static_cast<char>('A' + i);
    int left = lead;
    int right = size - lead - 1;
    if (i == 0) {
      row[left] = 'A';
    } else {
      row[left] = ch;
      row[right] = ch;
    }
    return row;
  };

  for (int i = 0; i <= n; ++i) {
    lines.push_back(make_row(i));
  }
  for (int i = n - 1; i >= 0; --i) {
    lines.push_back(make_row(i));
  }

  return lines;
}

std::vector<std::string> rows(char letter) {
  return make(letter);
}

std::string make_string(char letter) {
  auto rows = make(letter);
  std::string out;
  // Precompute size to reduce reallocations
  if (!rows.empty()) {
    size_t total = 0;
    for (size_t i = 0; i < rows.size(); ++i) {
      total += rows[i].size();
      if (i + 1 != rows.size()) total += 1; // for newline
    }
    out.reserve(total);
    for (size_t i = 0; i < rows.size(); ++i) {
      out += rows[i];
      if (i + 1 != rows.size()) out += '\n';
    }
  }
  return out;
}

}  // namespace diamond
