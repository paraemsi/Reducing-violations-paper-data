#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>

namespace allergies {

    class allergy_test {
    public:
        explicit allergy_test(unsigned int score);

        bool is_allergic_to(const std::string& allergen) const;
        std::unordered_set<std::string> get_allergies() const;

    private:
        unsigned int score_;
        static const std::vector<std::pair<std::string, unsigned int> > allergen_list_;
    };

}  // namespace allergies

#endif // ALLERGIES_H
