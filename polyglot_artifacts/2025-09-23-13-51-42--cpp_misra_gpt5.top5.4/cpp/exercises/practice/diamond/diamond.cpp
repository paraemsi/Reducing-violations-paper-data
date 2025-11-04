#include "diamond.h"

#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

auto rows(char letter) -> std::vector<std::string> {
  using index_t = std::int32_t;
  using traits = std::char_traits<char>;

  if (letter == 'A') {
    return std::vector<std::string>{std::string("A")};
  }

  const traits::int_type ia = traits::to_int_type('A');
  const traits::int_type il = traits::to_int_type(letter);

  // Compute zero-based distance from 'A' in a signed, fixed-width domain.
  const index_t offset = static_cast<index_t>(static_cast<std::int32_t>(il) - static_cast<std::int32_t>(ia));

  // Height and width of the square diamond.
  const index_t height = (static_cast<index_t>(2) * offset) + static_cast<index_t>(1);

  std::vector<std::string> v;
  v.reserve(static_cast<std::size_t>(height));

  for (index_t r = static_cast<index_t>(0); r < height; ++r) {
    const index_t top_level = (r <= offset) ? r : (height - static_cast<index_t>(1) - r);
    const index_t padding = offset - top_level;
    const index_t inner = (top_level == static_cast<index_t>(0)) ? static_cast<index_t>(0)
                                                                 : ((static_cast<std::int32_t>(2) * top_level) - static_cast<std::int32_t>(1));

    // Compute the character for this row: 'A' + top_level (via traits).
    const std::int32_t base_code = static_cast<std::int32_t>(ia);
    const std::int32_t ch_code32 = base_code + top_level;
    const traits::int_type ch_code = static_cast<traits::int_type>(ch_code32);
    const char ch = traits::to_char_type(ch_code);

    std::string row;
    row.reserve(static_cast<std::size_t>(height));

    row.append(static_cast<std::size_t>(padding), ' ');
    if (inner == static_cast<index_t>(0)) {
      row.push_back(ch);
    } else {
      row.push_back(ch);
      row.append(static_cast<std::size_t>(inner), ' ');
      row.push_back(ch);
    }
    row.append(static_cast<std::size_t>(padding), ' ');

    v.emplace_back(row);
  }

  return v;
}

auto make_diamond(char letter) -> std::string {
  // Fast path for the trivial diamond.
  if (letter == 'A') {
    return std::string("A");
  }

  using index_t = std::int32_t;
  using traits = std::char_traits<char>;

  const traits::int_type ia = traits::to_int_type('A');
  const traits::int_type il = traits::to_int_type(letter);

  // Compute zero-based distance from 'A' in a signed, fixed-width domain.
  const index_t offset = static_cast<index_t>(static_cast<std::int32_t>(il) - static_cast<std::int32_t>(ia));

  // Height and width of the square diamond.
  const index_t height = (static_cast<index_t>(2) * offset) + static_cast<index_t>(1);

  std::string out;
  // Reserve enough space: height rows of width 'height' plus (height - 1) newlines.
  out.reserve(static_cast<std::size_t>((static_cast<index_t>(2) * height) - static_cast<index_t>(1)));

  for (index_t r = static_cast<index_t>(0); r < height; ++r) {
    const index_t top_level = (r <= offset) ? r : (height - static_cast<index_t>(1) - r);
    const index_t padding = offset - top_level;
    const index_t inner = (top_level == static_cast<index_t>(0)) ? static_cast<index_t>(0)
                                                                 : ((static_cast<index_t>(2) * top_level) - static_cast<index_t>(1));

    // Compute the character for this row: 'A' + top_level (via traits).
    const std::int32_t base_code = static_cast<std::int32_t>(ia);
    const std::int32_t ch_code32 = base_code + top_level;
    const traits::int_type ch_code = static_cast<traits::int_type>(ch_code32);
    const char ch = traits::to_char_type(ch_code);

    std::string row;
    row.reserve(static_cast<std::size_t>(height));

    row.append(static_cast<std::size_t>(padding), ' ');
    if (inner == static_cast<index_t>(0)) {
      row.push_back(ch);
    } else {
      row.push_back(ch);
      row.append(static_cast<std::size_t>(inner), ' ');
      row.push_back(ch);
    }
    row.append(static_cast<std::size_t>(padding), ' ');

    out.append(row);
    if (r < (height - static_cast<index_t>(1))) {
      out.push_back('\n');
    }
  }

  return out;
}

}  // namespace diamond
