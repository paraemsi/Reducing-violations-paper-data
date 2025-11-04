#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_set>

namespace allergies {

// MISRA-compliant fixed-width enumeration of allergens
enum class Allergen : std::uint8_t
{
    eggs        = 1U,
    peanuts     = 2U,
    shellfish   = 4U,
    strawberries= 8U,
    tomatoes    = 16U,
    chocolate   = 32U,
    pollen      = 64U,
    cats        = 128U
};

class Allergies
{
public:
    explicit Allergies(std::uint32_t score_in) noexcept;

    bool is_allergic_to(Allergen allergen) const noexcept;
    bool is_allergic_to(const std::string& allergen_name) const noexcept;
    std::vector<Allergen> list() const noexcept;
    std::unordered_set<std::string> get_allergies() const noexcept;

private:
    std::uint32_t m_score;   // stored raw score (ignore bits > 128)
};

// factory helper expected by the tests
Allergies allergy_test(std::uint32_t score_in) noexcept;

}  // namespace allergies

#endif // ALLERGIES_H
