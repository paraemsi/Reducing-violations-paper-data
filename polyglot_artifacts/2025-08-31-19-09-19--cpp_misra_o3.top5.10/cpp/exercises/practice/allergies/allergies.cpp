#include "allergies.h"

#include <array>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <cstddef>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) {}

bool allergy_test::is_allergic_to(std::string_view item) const noexcept
{
    static const std::unordered_map<std::string_view, allergen> item_map{
        {"eggs", allergen::eggs},
        {"peanuts", allergen::peanuts},
        {"shellfish", allergen::shellfish},
        {"strawberries", allergen::strawberries},
        {"tomatoes", allergen::tomatoes},
        {"chocolate", allergen::chocolate},
        {"pollen", allergen::pollen},
        {"cats", allergen::cats}
    };

    const auto it{item_map.find(item)};
    if (it == item_map.end())
    {
        return false;
    }

    return ((m_score & static_cast<std::uint32_t>(it->second)) != static_cast<std::uint32_t>(0U));
}

std::unordered_set<std::string> allergy_test::get_allergies() const noexcept
{
    static const std::array<std::pair<std::string_view, allergen>, 8U> all_items{{
        {"eggs", allergen::eggs},
        {"peanuts", allergen::peanuts},
        {"shellfish", allergen::shellfish},
        {"strawberries", allergen::strawberries},
        {"tomatoes", allergen::tomatoes},
        {"chocolate", allergen::chocolate},
        {"pollen", allergen::pollen},
        {"cats", allergen::cats}
    }};

    std::unordered_set<std::string> result{};
    for (const auto& pair : all_items)
    {
        if (is_allergic_to(pair.first))
        {
            result.emplace(std::string(pair.first));
        }
    }

    return result;
}

}  // namespace allergies

//------------------------------------------------------------------------------
// std::hash specialisation for allergies::allergen
//------------------------------------------------------------------------------

namespace std {
template <>
struct hash<allergies::allergen>
{
    std::size_t operator()(const allergies::allergen& item) const noexcept
    {
        return static_cast<std::size_t>(item);
    }
};
} // namespace std
