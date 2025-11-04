#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace allergies {

typedef std::uint16_t score_t;

class allergy_test
{
public:
    explicit allergy_test(score_t score_in);

    bool is_allergic_to(const std::string& allergen) const;
    std::unordered_set<std::string> get_allergies() const;

private:
    score_t score;
};

}  // namespace allergies

#endif // ALLERGIES_H
