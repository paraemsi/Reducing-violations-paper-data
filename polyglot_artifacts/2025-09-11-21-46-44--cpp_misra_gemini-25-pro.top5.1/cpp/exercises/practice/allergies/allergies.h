#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

class allergy_test {
  public:
    explicit allergy_test(std::uint32_t score);

    bool is_allergic_to(const std::string& item) const;

    std::unordered_set<std::string> get_allergies() const;

  private:
    const std::uint32_t score_;
    static const std::unordered_map<std::string, std::uint32_t> ALLERGEN_SCORES;
};

}  // namespace allergies

#endif // ALLERGIES_H
