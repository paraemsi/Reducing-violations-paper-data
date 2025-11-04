#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <string>

namespace allergies {

enum class allergen : std::uint8_t
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

class allergy_test final
{
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergen allergen_value) const noexcept;
    bool is_allergic_to(const std::string& allergen_name) const noexcept;
    std::unordered_set<std::string> get_allergies() const noexcept;

private:
    std::uint32_t m_score{0U};
};

}  // namespace allergies

#endif // ALLERGIES_H
