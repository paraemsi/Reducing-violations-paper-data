#include "allergies.h"

#include <array>

namespace allergies {

namespace {
/* List of allergens covered by the test */
constexpr std::array<allergen, 8U> allergen_list{{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
}};
} // anonymous namespace

allergy_test::allergy_test(std::uint32_t score_in)
{
    for(const auto allergen_val : allergen_list) {
        const std::uint32_t value{static_cast<std::uint32_t>(allergen_val)};
        if(((score_in & value) != static_cast<std::uint32_t>(0U))) {
            (void)allergies_.emplace(allergen_val);
        }
    }
}

bool allergy_test::is_allergic_to(allergen item) const
{
    return (allergies_.find(item) != allergies_.end());
}

std::unordered_set<allergen, allergen_hash> allergy_test::get_allergies() const
{
    return allergies_;
}

}  // namespace allergies
