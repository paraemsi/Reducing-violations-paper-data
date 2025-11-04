#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <unordered_set>
#include <functional>
#include <string>

namespace allergies {

// Enumeration representing each allergen with its associated score value.
enum class allergen : int {
    eggs        = 1,
    peanuts     = 2,
    shellfish   = 4,
    strawberries= 8,
    tomatoes    = 16,
    chocolate   = 32,
    pollen      = 64,
    cats        = 128
};

// Class modelling a person's allergy information derived from a score.
class allergies {
public:
    explicit allergies(int score);

    // Return true if the person is allergic to the requested allergen.
    bool is_allergic_to(const std::string& item) const;

    // Return an unordered_set containing all allergens the person is allergic to.
    std::unordered_set<std::string> get_allergies() const;

private:
    int score_; // Only the low-order 8 bits are relevant (0-255).
};

using allergy_test = allergies;

}  // namespace allergies

// Provide a hash so allergen can be used in unordered containers.
namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        return std::hash<int>{}(static_cast<int>(a));
    }
};
}  // namespace std


#endif // ALLERGIES_H
