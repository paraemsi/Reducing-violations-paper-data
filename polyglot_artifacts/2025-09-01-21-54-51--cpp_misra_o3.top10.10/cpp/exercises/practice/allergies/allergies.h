#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs         = 1U,
    peanuts      = 2U,
    shellfish    = 4U,
    strawberries = 8U,
    tomatoes     = 16U,
    chocolate    = 32U,
    pollen       = 64U,
    cats         = 128U
};

struct allergen_hash {
    [[nodiscard]] std::size_t operator()(allergen a) const noexcept
    {
        return static_cast<std::size_t>(a);
    }
};

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score_in);

    [[nodiscard]] bool is_allergic_to(allergen item) const;

    [[nodiscard]] std::unordered_set<allergen, allergen_hash> get_allergies() const;

private:
    std::unordered_set<allergen, allergen_hash> allergies_;
};

}  // namespace allergies

#endif // ALLERGIES_H
