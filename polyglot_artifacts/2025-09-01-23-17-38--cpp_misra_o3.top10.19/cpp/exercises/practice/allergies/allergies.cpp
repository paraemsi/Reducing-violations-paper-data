#include "allergies.h"

#include <array>

namespace allergies {

allergy_test::allergy_test(score_type score) noexcept
: m_score(score)
{
}

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
  return ((m_score & static_cast<score_type>(item)) != static_cast<score_type>(0U));
}

std::unordered_set<allergen> allergy_test::get_allergies() const
{
  constexpr std::array<allergen, 8U> all_known
  {
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
  };

  std::unordered_set<allergen> result {};
  for (auto const item : all_known)
  {
    if (is_allergic_to(item))
    {
      (void)result.emplace(item);
    }
  }
  return result;
}

}  // namespace allergies
