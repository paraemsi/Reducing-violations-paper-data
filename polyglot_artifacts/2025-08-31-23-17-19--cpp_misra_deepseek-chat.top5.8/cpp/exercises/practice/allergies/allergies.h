#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace allergies {

using score_t = std::uint32_t;

class allergy_test {
private:
    score_t score_;
public:
    explicit allergy_test(score_t score);
    bool is_allergic_to(const std::string& item) const;
    std::unordered_set<std::string> get_allergies() const;
};

}  // namespace allergies

#endif // ALLERGIES_H
