#include "allergies.h"

#include <unordered_map>
#include <unordered_set>

namespace allergies {

namespace {
    using map_t = std::unordered_map<std::string, score_t>;

    static map_t const allergen_map{
        {"eggs", static_cast<score_t>(1U)},
        {"peanuts", static_cast<score_t>(2U)},
        {"shellfish", static_cast<score_t>(4U)},
        {"strawberries", static_cast<score_t>(8U)},
        {"tomatoes", static_cast<score_t>(16U)},
        {"chocolate", static_cast<score_t>(32U)},
        {"pollen", static_cast<score_t>(64U)},
        {"cats", static_cast<score_t>(128U)}
    };
} // unnamed namespace

allergy_test::allergy_test(score_t score_value) noexcept
    : m_score(score_value) { }

auto allergy_test::allergen_value(const std::string &item) -> score_t
{
    auto const it = allergen_map.find(item);
    if (it != allergen_map.end()) {
        return it->second;
    } else {
        return static_cast<score_t>(0U);
    }
}

bool allergy_test::is_allergic_to(const std::string &item) const
{
    score_t const value = allergen_value(item);
    if (value == static_cast<score_t>(0U)) {
        return false;
    } else {
        return ((m_score & value) != static_cast<score_t>(0U));
    }
}

std::unordered_set<std::string> allergy_test::get_allergies() const
{
    std::unordered_set<std::string> result{};
    for (auto const &pair : allergen_map) {
        if (is_allergic_to(pair.first)) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
