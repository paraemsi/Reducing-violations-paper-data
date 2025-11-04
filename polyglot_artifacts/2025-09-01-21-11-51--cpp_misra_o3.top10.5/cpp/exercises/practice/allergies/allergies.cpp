#include "allergies.h"

#include <unordered_map>
#include <unordered_set>

namespace allergies {

namespace
{

    const std::unordered_map<std::string, score_type> allergen_table{
        {"eggs", static_cast<score_type>(1u)},
        {"peanuts", static_cast<score_type>(2u)},
        {"shellfish", static_cast<score_type>(4u)},
        {"strawberries", static_cast<score_type>(8u)},
        {"tomatoes", static_cast<score_type>(16u)},
        {"chocolate", static_cast<score_type>(32u)},
        {"pollen", static_cast<score_type>(64u)},
        {"cats", static_cast<score_type>(128u)}
    };
} // unnamed namespace

Allergies::Allergies(score_type score) noexcept
    : m_score(score)
{
}

bool Allergies::is_allergic_to(const std::string& allergen) const noexcept
{
    const auto it = allergen_table.find(allergen);
    if (it == allergen_table.end())
    {
        return false;
    }
    const score_type mask = it->second;
    return ((m_score & mask) != 0u);
}

std::unordered_set<std::string> Allergies::get_allergies() const noexcept
{
    std::unordered_set<std::string> result{};
    for (const auto& pair : allergen_table)
    {
        if (((m_score & pair.second) != 0u))
        {
            (void)result.emplace(pair.first);
        }
    }
    return result;
}

[[nodiscard]] Allergies allergy_test(score_type score) noexcept
{
    return Allergies{score};
}

}  // namespace allergies
