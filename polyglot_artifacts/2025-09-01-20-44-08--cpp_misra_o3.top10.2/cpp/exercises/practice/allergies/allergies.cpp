#include "allergies.h"

#include <array>
#include <string>
#include <unordered_map>

namespace allergies {

Allergies::Allergies(std::uint32_t allergy_score) noexcept
    : m_score(allergy_score) { }

bool Allergies::is_allergic_to(Allergen allergen) const noexcept
{
    return ((m_score & static_cast<std::uint32_t>(allergen))
            != static_cast<std::uint32_t>(0u));
}

bool Allergies::is_allergic_to(const std::string& allergen) const noexcept
{
    static const std::unordered_map<std::string, Allergen> string_to_allergen_map = {
        {"eggs", Allergen::eggs},
        {"peanuts", Allergen::peanuts},
        {"shellfish", Allergen::shellfish},
        {"strawberries", Allergen::strawberries},
        {"tomatoes", Allergen::tomatoes},
        {"chocolate", Allergen::chocolate},
        {"pollen", Allergen::pollen},
        {"cats", Allergen::cats}
    };

    const auto it = string_to_allergen_map.find(allergen);
    if (it == string_to_allergen_map.end()) {
        return false;
    }
    return is_allergic_to(it->second);
}

std::unordered_set<std::string> Allergies::get_allergies() const
{
    static const std::unordered_map<Allergen, std::string> allergen_to_string_map = {
        {Allergen::eggs, "eggs"},
        {Allergen::peanuts, "peanuts"},
        {Allergen::shellfish, "shellfish"},
        {Allergen::strawberries, "strawberries"},
        {Allergen::tomatoes, "tomatoes"},
        {Allergen::chocolate, "chocolate"},
        {Allergen::pollen, "pollen"},
        {Allergen::cats, "cats"}
    };

    std::unordered_set<std::string> result{};
    for (const auto& pair : allergen_to_string_map) {
        if (is_allergic_to(pair.first)) {
            result.emplace(pair.second);
        }
    }
    return result;
}

Allergies allergy_test(std::uint32_t allergy_score) noexcept
{
    return Allergies(allergy_score);
}

}  // namespace allergies
