#include "allergies.h"

#include <vector>
#include <string>
#include <unordered_set>

namespace allergies {

namespace {

// Ordered list of allergens defined by the exercise
struct AllergenInfo final {
    const char*     name;
    std::uint32_t   value;
};

static const std::vector<AllergenInfo> kAllergens{
    {"eggs", 1U},
    {"peanuts", 2U},
    {"shellfish", 4U},
    {"strawberries", 8U},
    {"tomatoes", 16U},
    {"chocolate", 32U},
    {"pollen", 64U},
    {"cats", 128U}
};

} // unnamed namespace

allergy_test::allergy_test(std::uint32_t score_in) noexcept
    : score_{score_in} { }

bool allergy_test::is_allergic_to(const std::string& item) const noexcept
{
    for (const auto& ag : kAllergens) {
        if (item == ag.name) {
            return ((score_ & ag.value) != 0U);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const noexcept
{
    std::unordered_set<std::string> result{};

    for (const auto& ag : kAllergens) {
        if ((score_ & ag.value) != 0U) {
            (void)result.emplace(ag.name);
        }
    }
    return result;
}

}  // namespace allergies
