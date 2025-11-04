#if !defined(ALLERGIES_H)
#define ALLERGIES_H
#include <cstdint>
#include <cstddef>          // for std::size_t
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
    std::size_t operator()(allergen value) const noexcept
    {
        return static_cast<std::size_t>(value);
    }
};

using allergen_set = std::unordered_set<allergen, allergen_hash>;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;
    [[nodiscard]] allergen_set get_allergies() const noexcept;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
