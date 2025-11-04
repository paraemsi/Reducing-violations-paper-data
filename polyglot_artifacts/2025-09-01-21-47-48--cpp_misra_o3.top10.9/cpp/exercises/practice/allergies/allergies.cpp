#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(std::uint32_t score_in) noexcept
    : score_{score_in}
{
}

namespace
{
struct allergen_mapping {
    allergies::allergen id;
    const char* name;
};

constexpr allergen_mapping mappings[]{
    { allergies::allergen::eggs, "eggs" },
    { allergies::allergen::peanuts, "peanuts" },
    { allergies::allergen::shellfish, "shellfish" },
    { allergies::allergen::strawberries, "strawberries" },
    { allergies::allergen::tomatoes, "tomatoes" },
    { allergies::allergen::chocolate, "chocolate" },
    { allergies::allergen::pollen, "pollen" },
    { allergies::allergen::cats, "cats" }
};
} // unnamed namespace

bool allergy_test::is_allergic_to(const std::string& item) const noexcept
{
    for (const auto& m : mappings) {
        if (item == m.name) {
            const std::uint32_t mask{static_cast<std::uint32_t>(m.id)};
            return ((score_ & mask) != static_cast<std::uint32_t>(0));
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};

    for (const auto& m : mappings) {
        if (is_allergic_to(std::string{m.name})) {
            result.emplace(std::string{m.name});
        }
    }

    return result;
}

}  // namespace allergies
