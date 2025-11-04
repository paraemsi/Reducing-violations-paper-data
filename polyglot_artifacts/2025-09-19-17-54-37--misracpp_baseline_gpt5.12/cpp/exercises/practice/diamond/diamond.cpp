#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
  unsigned char uc = static_cast<unsigned char>(letter);
  char upper = static_cast<char>(std::toupper(uc));
  if (upper < 'A' || upper > 'Z') {
    throw std::invalid_argument("letter must be in range A-Z (case-insensitive)");
  }

  int n = upper - 'A';
  std::size_t size = static_cast<std::size_t>(2 * n + 1);

  auto make_row = [&](int i) -> std::string {
    char ch = static_cast<char>('A' + i);
    std::size_t lead = static_cast<std::size_t>(n - i);
    std::size_t inner = (i == 0) ? 0u : static_cast<std::size_t>(2 * i - 1);

    std::string row;
    row.reserve(size);
    row.append(lead, ' ');
    row.push_back(ch);
    if (i > 0) {
      row.append(inner, ' ');
      row.push_back(ch);
    }
    row.append(lead, ' ');
    return row;
  };

  std::vector<std::string> out;
  out.reserve(size);
  for (int i = 0; i <= n; ++i) {
    out.push_back(make_row(i));
  }
  for (int i = n - 1; i >= 0; --i) {
    out.push_back(make_row(i));
  }
  return out;
}

std::string make_diamond(char letter) {
  std::vector<std::string> r = rows(letter);
  std::string out;
  if (r.empty()) return out;
  std::size_t size = r.size();
  out.reserve(size * size + (size - 1));
  for (std::size_t i = 0; i < r.size(); ++i) {
    if (i > 0) out.push_back('\n');
    out += r[i];
  }
  return out;
}

}  // namespace diamond
