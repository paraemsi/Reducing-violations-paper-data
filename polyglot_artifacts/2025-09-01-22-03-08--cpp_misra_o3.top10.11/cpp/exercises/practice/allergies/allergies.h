#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs         = static_cast<std::uint32_t>(1U),
    peanuts      = static_cast<std::uint32_t>(2U),
    shellfish    = static_cast<std::uint32_t>(4U),
    strawberries = static_cast<std::uint32_t>(8U),
    tomatoes     = static_cast<std::uint32_t>(16U),
    chocolate    = static_cast<std::uint32_t>(32U),
    pollen       = static_cast<std::uint32_t>(64U),
    cats         = static_cast<std::uint32_t>(128U)
};

class allergy_test final {
public:
    explicit allergy_test(std::uint32_t score_in) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;
    [[nodiscard]] std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score;
};

}  // namespace allergies

#endif // ALLERGIES_H
