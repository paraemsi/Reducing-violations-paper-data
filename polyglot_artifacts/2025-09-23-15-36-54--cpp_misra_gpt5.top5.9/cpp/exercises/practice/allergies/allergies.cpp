#include "allergies.h"

#include <array>
#include <string>

namespace allergies {

namespace {
std::uint32_t value_for_name(const std::string& name) noexcept {
    if ((name == "eggs")) {
        return static_cast<std::uint32_t>(1);
    } else if ((name == "peanuts")) {
        return static_cast<std::uint32_t>(2);
    } else if ((name == "shellfish")) {
        return static_cast<std::uint32_t>(4);
    } else if ((name == "strawberries")) {
        return static_cast<std::uint32_t>(8);
    } else if ((name == "tomatoes")) {
        return static_cast<std::uint32_t>(16);
    } else if ((name == "chocolate")) {
        return static_cast<std::uint32_t>(32);
    } else if ((name == "pollen")) {
        return static_cast<std::uint32_t>(64);
    } else if ((name == "cats")) {
        return static_cast<std::uint32_t>(128);
    } else {
        return static_cast<std::uint32_t>(0);
    }
}
}  // namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_masked_{(score & kKnownMask)} {
}

bool allergy_test::is_allergic_to(const std::string& item) const noexcept {
    const std::uint32_t mask = value_for_name(item);
    return ((score_masked_ & mask) != static_cast<std::uint32_t>(0));
}

allergen_set allergy_test::get_allergies() const {
    allergen_set result{};

    constexpr std::array<const char*, 8> all = {
        "eggs",
        "peanuts",
        "shellfish",
        "strawberries",
        "tomatoes",
        "chocolate",
        "pollen",
        "cats"
    };

    for (const char* name : all) {
        const std::string s{name};
        if (is_allergic_to(s)) {
            result.emplace(s);
        }
    }

    return result;
}

}  // namespace allergies
