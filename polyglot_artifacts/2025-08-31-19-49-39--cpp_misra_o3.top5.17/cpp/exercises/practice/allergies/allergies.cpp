#include "allergies.h"
#include <array>
#include <string>
#include <unordered_set>

namespace allergies {

namespace {

/* Table mapping allergen names to their corresponding score values */
static const std::array<std::pair<const char*, std::uint32_t>, 8U> allergen_table{{
    {"eggs", 1U},
    {"peanuts", 2U},
    {"shellfish", 4U},
    {"strawberries", 8U},
    {"tomatoes", 16U},
    {"chocolate", 32U},
    {"pollen", 64U},
    {"cats", 128U}
}};

}  // unnamed namespace

allergy_test::allergy_test(const std::uint32_t score) : score_(score) { }

bool allergy_test::is_allergic_to(const std::string& allergen_name) const
{
    for (const auto& entry : allergen_table) {
        if (allergen_name == entry.first) {
            return ((score_ & entry.second) != 0U);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};
    for (const auto& entry : allergen_table) {
        if ((score_ & entry.second) != 0U) {
            static_cast<void>(result.emplace(entry.first));
        }
    }
    return result;
}

}  // namespace allergies
