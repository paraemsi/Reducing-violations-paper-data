#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>

namespace allergies {

    // List of allergens in order, matching their bit positions
    extern const std::vector<std::string> allergen_list;

    class allergy_test {
    public:
        explicit allergy_test(unsigned int score);

        bool is_allergic_to(const std::string& allergen) const;
        std::unordered_set<std::string> get_allergies() const;

    private:
        unsigned int score_;
    };

}  // namespace allergies

#endif // ALLERGIES_H
