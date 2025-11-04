#include "allergies.h"

#include <array>
#include <vector>
#include <string>

namespace allergies {

namespace {
/*  Array holding the list of allergens we know about.
 *  Using an array enables iteration in a fixed order without
 *  the overhead of dynamic allocation.
 */
constexpr std::array<allergen, 8U> k_known_allergens{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
};
} // unnamed namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) { }

bool allergy_test::is_allergic_to(allergen item) const noexcept
{
    /*  Promote the enum value to uint32_t so that the bitwise
     *  AND operates on operands of identical type and size.
     */
    return ((static_cast<std::uint32_t>(item) & m_score) != 0U);
}

bool allergy_test::is_allergic_to(const std::string& item) const noexcept
{
    for (allergen a : k_known_allergens) {
        std::string name{};
        switch (a) {
            case allergen::eggs:         name = "eggs"; break;
            case allergen::peanuts:      name = "peanuts"; break;
            case allergen::shellfish:    name = "shellfish"; break;
            case allergen::strawberries: name = "strawberries"; break;
            case allergen::tomatoes:     name = "tomatoes"; break;
            case allergen::chocolate:    name = "chocolate"; break;
            case allergen::pollen:       name = "pollen"; break;
            case allergen::cats:         name = "cats"; break;
            default:                     name.clear(); break;
        }
        if (item == name) {
            return is_allergic_to(a);
        }
    }
    return false;
}

std::vector<std::string> allergy_test::get_allergies() const noexcept
{
    std::vector<std::string> result{};
    for (allergen item : k_known_allergens) {
        if (is_allergic_to(item)) {
            switch (item) {
                case allergen::eggs:         result.emplace_back("eggs"); break;
                case allergen::peanuts:      result.emplace_back("peanuts"); break;
                case allergen::shellfish:    result.emplace_back("shellfish"); break;
                case allergen::strawberries: result.emplace_back("strawberries"); break;
                case allergen::tomatoes:     result.emplace_back("tomatoes"); break;
                case allergen::chocolate:    result.emplace_back("chocolate"); break;
                case allergen::pollen:       result.emplace_back("pollen"); break;
                case allergen::cats:         result.emplace_back("cats"); break;
                default:                     break;
            }
        }
    }
    return result;
}

}  // namespace allergies
