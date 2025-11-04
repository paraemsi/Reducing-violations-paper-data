#include "diamond.h"

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(const char letter) {
  using Traits = std::char_traits<char>;

  const std::int32_t letter_i32 = static_cast<std::int32_t>(Traits::to_int_type(letter));
  const std::int32_t baseA_i32 = static_cast<std::int32_t>(Traits::to_int_type('A'));

  std::int32_t diff_i32 = (letter_i32 - baseA_i32);
  if (diff_i32 < 0) {
    diff_i32 = 0;
  } else {
    // no-op
  }

  const std::uint32_t n = static_cast<std::uint32_t>(diff_i32);
  const std::uint32_t height = ((n * 2U) + 1U);

  std::vector<std::string> out;
  out.reserve(static_cast<std::size_t>(height));

  for (std::uint32_t r = 0U; (r < height); ++r) {
    const std::uint32_t idx = ((r <= n) ? r : ((height - 1U) - r));
    const std::uint32_t outer = (n - idx);
    const std::uint32_t inner = ((idx == 0U) ? 0U : (((idx * 2U)) - 1U));

    std::string line;
    line.reserve(static_cast<std::size_t>(height));

    if (outer != 0U) {
      line.append(static_cast<std::size_t>(outer), ' ');
    } else {
      // no-op
    }

    const std::int32_t code_i32 = (baseA_i32 + static_cast<std::int32_t>(idx));
    const Traits::int_type ch_code = static_cast<Traits::int_type>(code_i32);
    const char ch = Traits::to_char_type(ch_code);

    line.push_back(ch);

    if (idx != 0U) {
      if (inner != 0U) {
        line.append(static_cast<std::size_t>(inner), ' ');
      } else {
        // no-op
      }
      line.push_back(ch);
    } else {
      // no-op
    }

    if (outer != 0U) {
      line.append(static_cast<std::size_t>(outer), ' ');
    } else {
      // no-op
    }

    out.emplace_back(line);
  }

  return out;
}

std::string make_diamond(const char letter) {
  const std::vector<std::string> lines = rows(letter);

  std::size_t total = 0U;
  for (std::size_t i = 0U; (i < lines.size()); ++i) {
    total = (total + lines[i].size());
  }
  if (lines.size() != 0U) {
    total = (total + (lines.size() - 1U));
  } else {
    // no-op
  }

  std::string result;
  result.reserve(total);

  for (std::size_t i = 0U; (i < lines.size()); ++i) {
    result += lines[i];
    if ((i + 1U) < lines.size()) {
      result.push_back('\n');
    } else {
      // no-op
    }
  }

  return result;
}

}  // namespace diamond
