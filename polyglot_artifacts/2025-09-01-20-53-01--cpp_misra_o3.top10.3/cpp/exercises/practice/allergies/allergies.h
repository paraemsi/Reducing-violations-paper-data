#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs = 1u,
    peanuts = 2u,
    shellfish = 4u,
    strawberries = 8u,
    tomatoes = 16u,
    chocolate = 32u,
    pollen = 64u,
    cats = 128u
};

using allergy_set = std::unordered_set<std::string>;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score_in) noexcept;

    [[nodiscard]] auto is_allergic_to(const std::string& item) const noexcept -> bool;

    [[nodiscard]] auto get_allergies() const noexcept -> allergy_set;

private:
    std::uint32_t score_{0u};
};

}  // namespace allergies

#endif // ALLERGIES_H
