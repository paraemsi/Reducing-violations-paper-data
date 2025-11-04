#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace allergies {

using allergy_score_t = std::uint16_t;

class allergy_test
{
public:
    explicit allergy_test(allergy_score_t score_in);

    bool is_allergic_to(const std::string& allergen) const;
    std::vector<std::string> get_allergies() const;

private:
    allergy_score_t score;
    static const std::vector<std::string> allergen_list;
    static allergy_score_t allergen_score(const std::string& allergen);
};

}  // namespace allergies

#endif // ALLERGIES_H
