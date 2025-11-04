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
    std::vector<std::string> get_allergies() const;
    std::unordered_set<std::string> get_allergies_set() const;

private:
    unsigned int score_;
    static const std::vector<std::string> allergen_list;
    static const std::vector<unsigned int> allergen_scores;
    std::unordered_set<std::string> allergies_;
    void parse_allergies();
};

}  // namespace allergies

#endif // ALLERGIES_H
