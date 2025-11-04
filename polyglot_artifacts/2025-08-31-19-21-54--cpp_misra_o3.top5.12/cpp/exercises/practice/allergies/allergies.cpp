#include "allergies.h"

#include <array>
#include <vector>
#include <string>
#include <algorithm>  // (std::find, std::all_of – may be used by future extensions)

namespace allergies {

namespace
{
// List of all defined allergens for easy iteration
constexpr std::array<allergies::allergen, 8U> k_allergens{
    allergies::allergen::eggs,
    allergies::allergen::peanuts,
    allergies::allergen::shellfish,
    allergies::allergen::strawberries,
    allergies::allergen::tomatoes,
    allergies::allergen::chocolate,
    allergies::allergen::pollen,
    allergies::allergen::cats
};

constexpr const char* to_string(allergies::allergen item) noexcept
{
    switch (item)
    {
        case allergies::allergen::eggs: return "eggs";
        case allergies::allergen::peanuts: return "peanuts";
        case allergies::allergen::shellfish: return "shellfish";
        case allergies::allergen::strawberries: return "strawberries";
        case allergies::allergen::tomatoes: return "tomatoes";
        case allergies::allergen::chocolate: return "chocolate";
        case allergies::allergen::pollen: return "pollen";
        case allergies::allergen::cats: return "cats";
        default: return "";
    }
}

} // unnamed namespace

allergy_test::allergy_test(score_type score) noexcept
    : m_score(score)
{
}

bool allergy_test::is_allergic_to(const std::string& item) const
{
    for (const auto allergen_item : k_allergens)
    {
        if (item == to_string(allergen_item))
        {
            const score_type allergen_value{ static_cast<score_type>(allergen_item) };
            return ((m_score & allergen_value) != static_cast<score_type>(0U));
        }
    }
    return false;
}

std::vector<std::string> allergy_test::get_allergies() const
{
    std::vector<std::string> results;
    for (const auto allergen_item : k_allergens)
    {
        if (((m_score & static_cast<score_type>(allergen_item)) != static_cast<score_type>(0U)))
        {
            results.emplace_back(to_string(allergen_item));
        }
    }
    return results;
}

}  // namespace allergies
