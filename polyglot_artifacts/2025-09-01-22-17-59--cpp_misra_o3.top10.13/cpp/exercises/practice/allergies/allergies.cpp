#include "allergies.h"

#include <array>
#include <string>
#include <utility>        // for std::pair
#include <unordered_set>

namespace allergies {

namespace
{
    using allergen_pair = std::pair<const char*, std::uint32_t>;

    static constexpr std::array<allergen_pair, 8U> allergen_table{{
        {"eggs", static_cast<std::uint32_t>(1U)},
        {"peanuts", static_cast<std::uint32_t>(2U)},
        {"shellfish", static_cast<std::uint32_t>(4U)},
        {"strawberries", static_cast<std::uint32_t>(8U)},
        {"tomatoes", static_cast<std::uint32_t>(16U)},
        {"chocolate", static_cast<std::uint32_t>(32U)},
        {"pollen", static_cast<std::uint32_t>(64U)},
        {"cats", static_cast<std::uint32_t>(128U)}
    }};
} // unnamed namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score{score}
{
}

bool allergy_test::is_allergic_to(const std::string& allergen) const
{
    for (const auto& entry : allergen_table)
    {
        if (allergen == entry.first)
        {
            return ((m_score & entry.second) != static_cast<std::uint32_t>(0U));
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};
    for (const auto& entry : allergen_table)
    {
        if ((m_score & entry.second) != static_cast<std::uint32_t>(0U))
        {
            (void)result.emplace(entry.first);
        }
    }
    return result;
}

}  // namespace allergies
