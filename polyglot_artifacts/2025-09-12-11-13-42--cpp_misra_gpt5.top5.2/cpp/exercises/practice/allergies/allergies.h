#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <functional>

namespace allergies {

enum class allergy : std::uint8_t {
    eggs = 0U,
    peanuts = 1U,
    shellfish = 2U,
    strawberries = 3U,
    tomatoes = 4U,
    chocolate = 5U,
    pollen = 6U,
    cats = 7U
};

using allergen = allergy;

struct allergy_hash {
    std::size_t operator()(allergy a) const noexcept {
        return static_cast<std::size_t>(static_cast<std::uint32_t>(a));
    }
};

using allergy_set = std::unordered_set<allergy, allergy_hash>;
using allergen_set = allergy_set;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergy item) const noexcept;
    allergy_set get_allergies() const;
private:
    std::uint32_t m_score;
};

}  // namespace allergies


#endif // ALLERGIES_H
