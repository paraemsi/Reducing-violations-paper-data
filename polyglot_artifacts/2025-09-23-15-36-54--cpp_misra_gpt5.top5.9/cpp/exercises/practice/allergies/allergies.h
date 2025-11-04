#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <functional>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint8_t {
    eggs,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats
};

using allergen_set = std::unordered_set<std::string>;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(const std::string& item) const noexcept;

    allergen_set get_allergies() const;

private:
    static constexpr std::uint32_t kKnownMask = static_cast<std::uint32_t>(255);
    std::uint32_t score_masked_;
};

}  // namespace allergies

#endif // ALLERGIES_H
