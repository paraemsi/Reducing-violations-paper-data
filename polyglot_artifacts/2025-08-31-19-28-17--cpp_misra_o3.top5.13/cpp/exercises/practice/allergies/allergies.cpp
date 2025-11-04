#include "allergies.h"
#include <utility>

namespace allergies {

static constexpr std::array<std::pair<const char*, Allergen>, 8U> allergen_table{{
    {"eggs", Allergen::eggs},
    {"peanuts", Allergen::peanuts},
    {"shellfish", Allergen::shellfish},
    {"strawberries", Allergen::strawberries},
    {"tomatoes", Allergen::tomatoes},
    {"chocolate", Allergen::chocolate},
    {"pollen", Allergen::pollen},
    {"cats", Allergen::cats}
}};

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score)
{
}

bool allergy_test::is_allergic_to(const std::string& allergen) const noexcept
{
    for (const auto& entry : allergen_table) {
        if (allergen == entry.first) {
            return ((static_cast<std::uint32_t>(entry.second) & m_score) != static_cast<std::uint32_t>(0));
        }
    }
    return false;
}

std::vector<std::string> allergy_test::get_allergies() const
{
    std::vector<std::string> result{};
    for (const auto& entry : allergen_table) {
        if (is_allergic_to(entry.first)) {
            result.emplace_back(entry.first);
        }
    }
    return result;
}

}  // namespace allergies
