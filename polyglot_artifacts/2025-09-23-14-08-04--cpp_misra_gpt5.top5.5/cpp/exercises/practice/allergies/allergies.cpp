#include "allergies.h"

#include <array>
#include <string>
#include <utility>

namespace allergies {

namespace {
using allergy_pair = std::pair<const char*, std::uint32_t>;
static const std::array<allergy_pair, 8U> kAllergyMap{{
    {"eggs", 1u},
    {"peanuts", 2u},
    {"shellfish", 4u},
    {"strawberries", 8u},
    {"tomatoes", 16u},
    {"chocolate", 32u},
    {"pollen", 64u},
    {"cats", 128u}
}};
static std::uint32_t mask_for(const std::string& item) noexcept
{
    for (const auto& p : kAllergyMap) {
        if (item == p.first) {
            return p.second;
        }
    }
    return static_cast<std::uint32_t>(0u);
}
}  // unnamed namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{score}
{
}

bool allergy_test::is_allergic_to(const std::string& item) const noexcept
{
    const std::uint32_t mask = mask_for(item);
    return ((mask != static_cast<std::uint32_t>(0u)) && ((score_ & mask) != static_cast<std::uint32_t>(0u)));
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};

    for (const auto& p : kAllergyMap) {
        if (((score_ & p.second) != static_cast<std::uint32_t>(0u))) {
            result.emplace(p.first);
        }
    }

    return result;
}

}  // namespace allergies
