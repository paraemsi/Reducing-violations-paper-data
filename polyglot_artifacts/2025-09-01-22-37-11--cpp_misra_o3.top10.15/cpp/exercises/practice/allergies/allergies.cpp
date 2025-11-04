#include "allergies.h"

#include <array>
#include <vector>

namespace allergies {

namespace {

/*  Lookup table containing all allergens defined by the exercise.  */
constexpr std::array<allergen, 8U> allergen_table{{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
}};

}   // unnamed namespace

allergy_test::allergy_test(std::uint32_t score_in)
    : m_score{score_in},
      m_allergy_set{} {
    for (const auto& item : allergen_table) {
        if ((m_score & static_cast<std::uint32_t>(item)) != static_cast<std::uint32_t>(0U)) {
            (void)m_allergy_set.emplace(item);   /* discard bool part */
        }
    }
}

bool allergy_test::is_allergic_to(allergen allergen_key) const {
    return m_allergy_set.find(allergen_key) != m_allergy_set.end();
}

std::vector<allergen> allergy_test::get_allergies() const {
    std::vector<allergen> result{};
    for (const auto& item : allergen_table) {
        if (is_allergic_to(item)) {
            result.push_back(item);
        }
    }
    return result;
}

}  // namespace allergies
