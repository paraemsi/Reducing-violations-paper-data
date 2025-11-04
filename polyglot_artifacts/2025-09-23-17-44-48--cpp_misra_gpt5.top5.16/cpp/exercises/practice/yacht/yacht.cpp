#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <initializer_list>

namespace yacht {

namespace {
using counts_t = std::array<std::uint8_t, 7U>;

auto parse_category(std::string_view name, category& out) noexcept -> bool
{
  if ((name == std::string_view{"ones"})) {
    out = category::ones;
    return true;
  } else if ((name == std::string_view{"twos"})) {
    out = category::twos;
    return true;
  } else if ((name == std::string_view{"threes"})) {
    out = category::threes;
    return true;
  } else if ((name == std::string_view{"fours"})) {
    out = category::fours;
    return true;
  } else if ((name == std::string_view{"fives"})) {
    out = category::fives;
    return true;
  } else if ((name == std::string_view{"sixes"})) {
    out = category::sixes;
    return true;
  } else if ((name == std::string_view{"full house"})) {
    out = category::full_house;
    return true;
  } else if ((name == std::string_view{"four of a kind"})) {
    out = category::four_of_a_kind;
    return true;
  } else if ((name == std::string_view{"little straight"})) {
    out = category::little_straight;
    return true;
  } else if ((name == std::string_view{"big straight"})) {
    out = category::big_straight;
    return true;
  } else if ((name == std::string_view{"choice"})) {
    out = category::choice;
    return true;
  } else if ((name == std::string_view{"yacht"})) {
    out = category::yacht;
    return true;
  } else {
    return false;
  }
}

auto make_counts(const dice_roll& dice) noexcept -> counts_t
{
  counts_t counts{};
  for (std::size_t i = static_cast<std::size_t>(0U); i < counts.size(); ++i) {
    counts[i] = static_cast<std::uint8_t>(0U);
  }

  for (std::size_t i = static_cast<std::size_t>(0U); i < dice.size(); ++i) {
    const die_t v = dice[i];
    const std::size_t idx = static_cast<std::size_t>(v);
    counts[idx] = static_cast<std::uint8_t>(counts[idx] + static_cast<std::uint8_t>(1U));
  }
  return counts;
}

auto sum_dice(const dice_roll& dice) noexcept -> score_t
{
  score_t s = static_cast<score_t>(0U);
  for (std::size_t i = static_cast<std::size_t>(0U); i < dice.size(); ++i) {
    s = (s + static_cast<score_t>(dice[i]));
  }
  return s;
}
}  // namespace

[[nodiscard]] auto score(const dice_roll& dice, std::string_view cat) noexcept -> score_t
{
  category cat_enum{};
  if (!parse_category(cat, cat_enum)) {
    return static_cast<score_t>(0U);
  }

  const counts_t counts = make_counts(dice);

  switch (cat_enum) {
    case category::ones:
    case category::twos:
    case category::threes:
    case category::fours:
    case category::fives:
    case category::sixes: {
      score_t face_value = static_cast<score_t>(0U);
      std::uint8_t count8 = static_cast<std::uint8_t>(0U);
      switch (cat_enum) {
        case category::ones: { face_value = static_cast<score_t>(1U); count8 = counts[static_cast<std::size_t>(1U)]; break; }
        case category::twos: { face_value = static_cast<score_t>(2U); count8 = counts[static_cast<std::size_t>(2U)]; break; }
        case category::threes: { face_value = static_cast<score_t>(3U); count8 = counts[static_cast<std::size_t>(3U)]; break; }
        case category::fours: { face_value = static_cast<score_t>(4U); count8 = counts[static_cast<std::size_t>(4U)]; break; }
        case category::fives: { face_value = static_cast<score_t>(5U); count8 = counts[static_cast<std::size_t>(5U)]; break; }
        case category::sixes: { face_value = static_cast<score_t>(6U); count8 = counts[static_cast<std::size_t>(6U)]; break; }
        default: { face_value = static_cast<score_t>(0U); count8 = static_cast<std::uint8_t>(0U); break; }
      }
      const score_t count = static_cast<score_t>(count8);
      return (face_value * count);
    }

    case category::full_house: {
      bool has_three = false;
      bool has_two = false;
      for (std::size_t face = static_cast<std::size_t>(1U); face <= static_cast<std::size_t>(6U); ++face) {
        if ((counts[face] == static_cast<std::uint8_t>(3U))) {
          has_three = true;
        }
        if ((counts[face] == static_cast<std::uint8_t>(2U))) {
          has_two = true;
        }
      }
      if ((has_three) && (has_two)) {
        return sum_dice(dice);
      } else {
        return static_cast<score_t>(0U);
      }
    }

    case category::four_of_a_kind: {
      for (std::size_t face = static_cast<std::size_t>(1U); face <= static_cast<std::size_t>(6U); ++face) {
        if ((counts[face] >= static_cast<std::uint8_t>(4U))) {
          const score_t face_value = static_cast<score_t>(face);
          return (face_value * static_cast<score_t>(4U));
        }
      }
      return static_cast<score_t>(0U);
    }

    case category::little_straight: {
      bool ok = true;
      for (std::size_t face = static_cast<std::size_t>(1U); face <= static_cast<std::size_t>(5U); ++face) {
        if ((counts[face] != static_cast<std::uint8_t>(1U))) {
          ok = false;
        }
      }
      if ((ok) && (counts[static_cast<std::size_t>(6U)] == static_cast<std::uint8_t>(0U))) {
        return static_cast<score_t>(30U);
      } else {
        return static_cast<score_t>(0U);
      }
    }

    case category::big_straight: {
      bool ok = true;
      for (std::size_t face = static_cast<std::size_t>(2U); face <= static_cast<std::size_t>(6U); ++face) {
        if ((counts[face] != static_cast<std::uint8_t>(1U))) {
          ok = false;
        }
      }
      if ((ok) && (counts[static_cast<std::size_t>(1U)] == static_cast<std::uint8_t>(0U))) {
        return static_cast<score_t>(30U);
      } else {
        return static_cast<score_t>(0U);
      }
    }

    case category::choice: {
      return sum_dice(dice);
    }

    case category::yacht: {
      for (std::size_t face = static_cast<std::size_t>(1U); face <= static_cast<std::size_t>(6U); ++face) {
        if ((counts[face] == static_cast<std::uint8_t>(5U))) {
          return static_cast<score_t>(50U);
        }
      }
      return static_cast<score_t>(0U);
    }

    default: {
      return static_cast<score_t>(0U);
    }
  }
}

[[nodiscard]] auto score(std::initializer_list<std::uint32_t> dice, std::string_view cat) noexcept -> score_t
{
  if ((dice.size() != static_cast<std::size_t>(5U))) {
    return static_cast<score_t>(0U);
  }

  dice_roll roll{};
  std::size_t i = static_cast<std::size_t>(0U);
  for (std::initializer_list<std::uint32_t>::const_iterator it = dice.begin(); it != dice.end(); ++it) {
    const std::uint32_t v32 = *it;
    if (((v32 < static_cast<std::uint32_t>(1U))) || ((v32 > static_cast<std::uint32_t>(6U)))) {
      return static_cast<score_t>(0U);
    }
    roll[i] = static_cast<die_t>(v32);
    i = (i + static_cast<std::size_t>(1U));
  }

  return score(roll, cat);
}

}  // namespace yacht
