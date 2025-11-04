#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};

struct allergen_hash {
    std::size_t operator()(allergen a) const noexcept;
};

using allergen_set = std::unordered_set<allergen, allergen_hash>;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(allergen item) const noexcept;

    allergen_set get_allergies() const;

    allergen_set list() const;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
