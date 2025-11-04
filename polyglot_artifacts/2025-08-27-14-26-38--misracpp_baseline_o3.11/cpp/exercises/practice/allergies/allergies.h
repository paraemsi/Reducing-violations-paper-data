#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <type_traits>
#include <functional>

namespace allergies {

    enum class allergen {
        eggs = 1,
        peanuts = 2,
        shellfish = 4,
        strawberries = 8,
        tomatoes = 16,
        chocolate = 32,
        pollen = 64,
        cats = 128
    };
}  // namespace allergies

// Hash specialization for std::unordered_set<allergies::allergen>
namespace std {
    template <>
    struct hash<allergies::allergen> {
        size_t operator()(const allergies::allergen& a) const noexcept {
            using Underlying = std::underlying_type_t<allergies::allergen>;
            return std::hash<Underlying>{}(static_cast<Underlying>(a));
        }
    };
}

namespace allergies {


    class allergy_test {
    public:
        explicit allergy_test(unsigned int score);

        bool is_allergic_to(allergen item) const;

        std::unordered_set<allergen> get_allergies() const;

    private:
        std::unordered_set<allergen> allergies_;
    };

}  // namespace allergies


#endif // ALLERGIES_H
