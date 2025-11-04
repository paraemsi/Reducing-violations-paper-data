#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>

namespace allergies {

// Strongly-typed bit-flags for each allergen
enum class allergen : std::uint32_t
{
    eggs         = 1U,
    peanuts      = 2U,
    shellfish    = 4U,
    strawberries = 8U,
    tomatoes     = 16U,
    chocolate    = 32U,
    pollen       = 64U,
    cats         = 128U
};

// Encapsulates an allergy test result
class allergy_test
{
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;
    [[nodiscard]] std::unordered_set<allergen> get_allergies() const noexcept;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
