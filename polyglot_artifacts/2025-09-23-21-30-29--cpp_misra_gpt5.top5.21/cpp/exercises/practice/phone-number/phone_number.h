#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

// Clean a NANP phone number by removing punctuation and an optional leading
// country code '1'. Returns a 10-digit string or throws std::domain_error
// if the resulting number is not exactly 10 digits or fails NANP rules.
auto clean(const std::string& raw) -> std::string;

class phone_number {
public:
    explicit phone_number(const std::string& raw);
    auto number() const -> std::string;
    auto area_code() const -> std::string;
    auto pretty() const -> std::string;
private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
