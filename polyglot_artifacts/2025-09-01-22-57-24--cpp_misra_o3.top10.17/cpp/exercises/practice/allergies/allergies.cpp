#include "allergies.h"
#include <unordered_set>

namespace allergies {

/* static */ auto allergy_test::allergen_map() noexcept
    -> const std::array<std::pair<std::string, std::uint32_t>, 8>&
{
    /*  The array is defined once and returned by reference to
        avoid multiple constructions.  */
    static const std::array<std::pair<std::string, std::uint32_t>, 8> map{
        {
            {"eggs", std::uint32_t{1U}},
            {"peanuts", std::uint32_t{2U}},
            {"shellfish", std::uint32_t{4U}},
            {"strawberries", std::uint32_t{8U}},
            {"tomatoes", std::uint32_t{16U}},
            {"chocolate", std::uint32_t{32U}},
            {"pollen", std::uint32_t{64U}},
            {"cats", std::uint32_t{128U}}
        }
    };
    return map;
}

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_allergies_set{}
{
    for (const auto& entry : allergen_map())
    {
        const std::uint32_t value{entry.second};
        if (((score & value) != std::uint32_t{0U}))
        {
            /*  Only insert when the corresponding bit is set.  */
            (void)m_allergies_set.emplace(entry.first);
        }
    }
}

auto allergy_test::is_allergic_to(const std::string& item) const noexcept -> bool
{
    return (m_allergies_set.find(item) != m_allergies_set.end());
}

auto allergy_test::get_allergies() const -> std::unordered_set<std::string>
{
    return m_allergies_set; /* return by value – caller receives its own copy */
}

}  // namespace allergies
