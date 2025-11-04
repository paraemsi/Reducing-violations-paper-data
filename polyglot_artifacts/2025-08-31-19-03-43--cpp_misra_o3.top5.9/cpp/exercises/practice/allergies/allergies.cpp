#include "allergies.h"

namespace allergies {

const std::unordered_map<std::string, std::uint32_t> Allergies::s_allergen_values =
{
    {"eggs",         static_cast<std::uint32_t>(1)},
    {"peanuts",      static_cast<std::uint32_t>(2)},
    {"shellfish",    static_cast<std::uint32_t>(4)},
    {"strawberries", static_cast<std::uint32_t>(8)},
    {"tomatoes",     static_cast<std::uint32_t>(16)},
    {"chocolate",    static_cast<std::uint32_t>(32)},
    {"pollen",       static_cast<std::uint32_t>(64)},
    {"cats",         static_cast<std::uint32_t>(128)}
};

Allergies::Allergies(std::uint32_t score) noexcept
    : m_score(score)
{
}

bool Allergies::is_allergic_to(const std::string& allergen) const noexcept
{
    auto const itr = s_allergen_values.find(allergen);
    if (itr == s_allergen_values.end())
    {
        return false;
    }
    return ((m_score & itr->second) != static_cast<std::uint32_t>(0U));
}

std::unordered_set<std::string> Allergies::get_allergies() const noexcept
{
    std::unordered_set<std::string> result {};
    for (auto const& pair : s_allergen_values)
    {
        if ((m_score & pair.second) != static_cast<std::uint32_t>(0U))
        {
            (void)result.emplace(pair.first);
        }
    }
    return result;
}

Allergies allergy_test(std::uint32_t score) noexcept
{
    return Allergies(score);
}

}  // namespace allergies
