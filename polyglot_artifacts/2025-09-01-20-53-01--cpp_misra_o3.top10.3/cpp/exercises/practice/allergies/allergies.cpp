#include "allergies.h"

#include <array>
#include <string>
#include <unordered_set>
#include <utility>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score_in) noexcept : score_{score_in}
{
}

auto allergy_test::is_allergic_to(const std::string& item) const noexcept -> bool
{
    std::uint32_t mask{0u};

    if (item == "eggs") {
        mask = 1u;
    } else if (item == "peanuts") {
        mask = 2u;
    } else if (item == "shellfish") {
        mask = 4u;
    } else if (item == "strawberries") {
        mask = 8u;
    } else if (item == "tomatoes") {
        mask = 16u;
    } else if (item == "chocolate") {
        mask = 32u;
    } else if (item == "pollen") {
        mask = 64u;
    } else if (item == "cats") {
        mask = 128u;
    } else {
        mask = 0u;
    }

    return ((mask != 0u) && ((score_ & mask) != static_cast<std::uint32_t>(0u)));
}

auto allergy_test::get_allergies() const noexcept -> allergy_set
{
    static constexpr std::array<std::pair<allergen, const char*>, 8U> all_items{{
        { allergen::eggs, "eggs" },
        { allergen::peanuts, "peanuts" },
        { allergen::shellfish, "shellfish" },
        { allergen::strawberries, "strawberries" },
        { allergen::tomatoes, "tomatoes" },
        { allergen::chocolate, "chocolate" },
        { allergen::pollen, "pollen" },
        { allergen::cats, "cats" }
    }};

    allergy_set result{};
    for (const auto& item : all_items) {
        if ((score_ & static_cast<std::uint32_t>(item.first)) != static_cast<std::uint32_t>(0u)) {
            (void)result.emplace(item.second);
        }
    }
    return result;
}

}  // namespace allergies
