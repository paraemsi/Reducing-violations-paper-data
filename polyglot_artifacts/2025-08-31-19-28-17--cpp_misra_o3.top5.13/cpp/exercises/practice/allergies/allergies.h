#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <array>
#include <string>
#include <vector>

namespace allergies {

enum class Allergen : std::uint32_t {
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};


class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const noexcept;

    [[nodiscard]] std::vector<std::string> get_allergies() const;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
