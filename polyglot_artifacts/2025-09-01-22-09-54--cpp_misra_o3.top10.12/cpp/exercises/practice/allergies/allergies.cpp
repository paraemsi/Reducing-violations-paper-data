#include "allergies.h"

#include <array>

namespace {

/*  Mapping between allergen names and their bit-mask value.
 *  Kept in an array to preserve the canonical order required by the tests.
 */
constexpr std::array<std::pair<const char*, std::uint32_t>, 8U> k_allergen_map{{
    {"eggs",        1U},
    {"peanuts",     2U},
    {"shellfish",   4U},
    {"strawberries",8U},
    {"tomatoes",    16U},
    {"chocolate",   32U},
    {"pollen",      64U},
    {"cats",        128U}
}};

} // unnamed namespace

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score{score},
      m_allergens_present{}
{
    for (const auto& entry : k_allergen_map) {
        const std::uint32_t mask{entry.second};
        if (((m_score & mask) != 0U)) {
            (void)m_allergens_present.emplace(entry.first);
        }
    }
}

bool allergy_test::is_allergic_to(const std::string& allergen) const
{
    return (m_allergens_present.find(allergen) != m_allergens_present.end());
}


std::vector<std::string> allergy_test::get_allergies() const
{
    std::vector<std::string> result{};
    result.reserve(m_allergens_present.size());

    for (const auto& entry : k_allergen_map) {
        if (m_allergens_present.find(entry.first) != m_allergens_present.end()) {
            result.emplace_back(entry.first);
        }
    }

    return result;   /*  caller shall use the returned value per MISRA rule  */
}

}  // namespace allergies
