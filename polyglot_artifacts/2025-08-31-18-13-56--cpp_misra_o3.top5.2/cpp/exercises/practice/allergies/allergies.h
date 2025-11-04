#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <cstdint>
#include <cstddef>
#include <functional>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs = 1u,
    peanuts = 2u,
    shellfish = 4u,
    strawberries = 8u,
    tomatoes = 16u,
    chocolate = 32u,
    pollen = 64u,
    cats = 128u
};
using score_type = std::uint32_t;

class allergy_test {
public:
    explicit allergy_test(score_type score_in);

    bool is_allergic_to(allergen item) const;

    std::unordered_set<allergen> get_allergies() const;

private:
    score_type m_score;
};

}  // namespace allergies

namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept
    {
        return std::hash<std::uint32_t>{}(static_cast<std::uint32_t>(a));
    }
};
} // namespace std

#endif // ALLERGIES_H
