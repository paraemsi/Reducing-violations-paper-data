#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>

namespace allergies {

    enum class Allergen {
        eggs = 1,
        peanuts = 2,
        shellfish = 4,
        strawberries = 8,
        tomatoes = 16,
        chocolate = 32,
        pollen = 64,
        cats = 128
    };

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
