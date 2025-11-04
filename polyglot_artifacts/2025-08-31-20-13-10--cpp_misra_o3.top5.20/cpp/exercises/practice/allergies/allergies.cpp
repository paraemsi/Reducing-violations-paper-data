#include "allergies.h"

#include <array>

namespace
{

using allergies_map_type = std::array<std::pair<const char*, std::uint32_t>, 8U>;

constexpr allergies_map_type k_allergy_map{{
    {"eggs", 1U},
    {"peanuts", 2U},
    {"shellfish", 4U},
    {"strawberries", 8U},
    {"tomatoes", 16U},
    {"chocolate", 32U},
    {"pollen", 64U},
    {"cats", 128U}
}};

} // unnamed namespace

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score{score}
{
}

bool allergy_test::is_allergic_to(const std::string& item) const
{
    for (const auto& entry : k_allergy_map)
    {
        if (item == entry.first)
        {
            return ((m_score & entry.second) != static_cast<std::uint32_t>(0));
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};
    for (const auto& entry : k_allergy_map)
    {
        if ((m_score & entry.second) != static_cast<std::uint32_t>(0))
        {
            (void)result.emplace(entry.first);
        }
    }
    return result;
}

}  // namespace allergies
