#include "yacht.h"

#include <cstddef>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) noexcept -> std::uint32_t
{
  std::array<std::uint32_t, 7U> counts{};  // index 1..6 used

  for (const std::uint8_t die : dice) {
    const std::size_t idx = static_cast<std::size_t>(die);
    if ((idx > static_cast<std::size_t>(0U)) && (idx < static_cast<std::size_t>(counts.size()))) {
      counts[idx] = (counts[idx] + static_cast<std::uint32_t>(1U));
    } else {
      // Out-of-range die values are not expected per problem statement.
    }
  }

  const auto sum_all = [&dice]() -> std::uint32_t {
    std::uint32_t total = static_cast<std::uint32_t>(0U);
    for (const std::uint8_t d : dice) {
      total = (total + static_cast<std::uint32_t>(d));
    }
    return total;
  };

  const auto score_face = [&counts](std::uint32_t face) -> std::uint32_t {
    return (counts[static_cast<std::size_t>(face)] * face);
  };

  bool known = true;
  category mapped = category::choice;
  if ((cat == std::string_view{"ones"})) {
    mapped = category::ones;
  } else if ((cat == std::string_view{"twos"})) {
    mapped = category::twos;
  } else if ((cat == std::string_view{"threes"})) {
    mapped = category::threes;
  } else if ((cat == std::string_view{"fours"})) {
    mapped = category::fours;
  } else if ((cat == std::string_view{"fives"})) {
    mapped = category::fives;
  } else if ((cat == std::string_view{"sixes"})) {
    mapped = category::sixes;
  } else if ((cat == std::string_view{"full house"})) {
    mapped = category::full_house;
  } else if ((cat == std::string_view{"four of a kind"})) {
    mapped = category::four_of_a_kind;
  } else if ((cat == std::string_view{"little straight"})) {
    mapped = category::little_straight;
  } else if ((cat == std::string_view{"big straight"})) {
    mapped = category::big_straight;
  } else if ((cat == std::string_view{"choice"})) {
    mapped = category::choice;
  } else if ((cat == std::string_view{"yacht"})) {
    mapped = category::yacht;
  } else {
    known = false;
  }

  if (!known) {
    return static_cast<std::uint32_t>(0U);
  }

  switch (mapped) {
    case category::ones: {
      return score_face(static_cast<std::uint32_t>(1U));
    }
    case category::twos: {
      return score_face(static_cast<std::uint32_t>(2U));
    }
    case category::threes: {
      return score_face(static_cast<std::uint32_t>(3U));
    }
    case category::fours: {
      return score_face(static_cast<std::uint32_t>(4U));
    }
    case category::fives: {
      return score_face(static_cast<std::uint32_t>(5U));
    }
    case category::sixes: {
      return score_face(static_cast<std::uint32_t>(6U));
    }
    case category::full_house: {
      bool has_three = false;
      bool has_two = false;

      for (std::uint32_t face = static_cast<std::uint32_t>(1U); face <= static_cast<std::uint32_t>(6U); face = (face + static_cast<std::uint32_t>(1U))) {
        const std::uint32_t c = counts[static_cast<std::size_t>(face)];
        if (c == static_cast<std::uint32_t>(3U)) {
          has_three = true;
        } else if (c == static_cast<std::uint32_t>(2U)) {
          has_two = true;
        }
      }

      if ((has_three) && (has_two)) {
        return sum_all();
      } else {
        return static_cast<std::uint32_t>(0U);
      }
    }
    case category::four_of_a_kind: {
      for (std::uint32_t face = static_cast<std::uint32_t>(1U); face <= static_cast<std::uint32_t>(6U); face = (face + static_cast<std::uint32_t>(1U))) {
        const std::uint32_t c = counts[static_cast<std::size_t>(face)];
        if (c >= static_cast<std::uint32_t>(4U)) {
          return (static_cast<std::uint32_t>(4U) * face);
        }
      }
      return static_cast<std::uint32_t>(0U);
    }
    case category::little_straight: {
      const bool pattern =
          (counts[static_cast<std::size_t>(1U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(2U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(3U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(4U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(5U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(6U)] == static_cast<std::uint32_t>(0U));

      if (pattern) {
        return static_cast<std::uint32_t>(30U);
      } else {
        return static_cast<std::uint32_t>(0U);
      }
    }
    case category::big_straight: {
      const bool pattern =
          (counts[static_cast<std::size_t>(1U)] == static_cast<std::uint32_t>(0U)) &&
          (counts[static_cast<std::size_t>(2U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(3U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(4U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(5U)] == static_cast<std::uint32_t>(1U)) &&
          (counts[static_cast<std::size_t>(6U)] == static_cast<std::uint32_t>(1U));

      if (pattern) {
        return static_cast<std::uint32_t>(30U);
      } else {
        return static_cast<std::uint32_t>(0U);
      }
    }
    case category::choice: {
      return sum_all();
    }
    case category::yacht: {
      for (std::uint32_t face = static_cast<std::uint32_t>(1U); face <= static_cast<std::uint32_t>(6U); face = (face + static_cast<std::uint32_t>(1U))) {
        if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint32_t>(5U)) {
          return static_cast<std::uint32_t>(50U);
        }
      }
      return static_cast<std::uint32_t>(0U);
    }
    default: {
      return static_cast<std::uint32_t>(0U);
    }
  }
}

}  // namespace yacht
