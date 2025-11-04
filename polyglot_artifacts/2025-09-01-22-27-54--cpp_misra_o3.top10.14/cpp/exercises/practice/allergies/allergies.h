#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <vector>

namespace allergies {

/* Enumeration of the recognised allergens */
enum class allergen : std::uint8_t
{
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};

/* Hash functor so that allergen can be stored in an unordered_set */
struct allergen_hash
{
    std::size_t operator()(const allergen& a) const noexcept
    {
        return static_cast<std::size_t>(a);
    }
};

using score_t = std::uint32_t;

class allergy_test
{
public:
    explicit allergy_test(score_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;

    [[nodiscard]] std::vector<allergen> get_allergies() const;

private:
    std::unordered_set<allergen, allergen_hash> allergies_;
};

}  // namespace allergies

#endif // ALLERGIES_H
