#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> (rows)(char letter) {
  unsigned char uc = static_cast<unsigned char>(letter);
  char upper = static_cast<char>(std::toupper(uc));
  if (upper < 'A' || upper > 'Z') {
    throw std::invalid_argument("diamond::rows expects a letter in [A-Z] or [a-z]");
  }

  int n = upper - 'A' + 1;
  int width = 2 * n - 1;

  std::vector<std::string> lines;
  lines.reserve(static_cast<std::size_t>(width));

  for (int i = 0; i < n; ++i) {
    int pad = n - 1 - i;
    char ch = static_cast<char>('A' + i);

    std::string line(static_cast<std::size_t>(width), ' ');
    // Place the left character
    line[static_cast<std::size_t>(pad)] = ch;

    if (i != 0) {
      // Place the right character symmetrically
      line[static_cast<std::size_t>(width - pad - 1)] = ch;
    }

    lines.push_back(std::move(line));
  }

  // Mirror the top half (excluding the center line) to form the bottom half.
  for (int i = n - 2; i >= 0; --i) {
    lines.push_back(lines[static_cast<std::size_t>(i)]);
  }

  return lines;
}

std::string (str)(char letter) {
  const auto v = rows(letter);
  if (v.empty()) return std::string();

  // Pre-reserve an approximate capacity: width + newline per line (except last).
  std::size_t approx = 0;
  approx += v[0].size() * v.size();
  approx += v.size() - 1;
  std::string out;
  out.reserve(approx);

  for (std::size_t i = 0; i < v.size(); ++i) {
    out += v[i];
    if (i + 1 < v.size()) out += '\n';
  }
  return out;
}

}  // namespace diamond
