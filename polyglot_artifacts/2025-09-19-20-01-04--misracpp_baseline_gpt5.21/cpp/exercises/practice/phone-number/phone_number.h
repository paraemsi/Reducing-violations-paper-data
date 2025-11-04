#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <stdexcept>

namespace phone_number {

// Clean a NANP phone number to a 10-digit string.
// Rules:
// - Remove punctuation and whitespace.
// - Allow an optional leading '+1' or '1' country code; strip it.
// - Validate total digits and NANP constraints (area/exchange cannot start with 0 or 1).
 // - Throw std::domain_error on invalid input.
std::string clean(const std::string& input);

class phone_number {
public:
    explicit phone_number(const std::string& input)
        : digits_(clean(input)) {}

    std::string number() const { return digits_; }
    std::string area_code() const { return digits_.substr(0, 3); }
    std::string pretty() const {
        return "(" + area_code() + ") " + digits_.substr(3, 3) + "-" + digits_.substr(6, 4);
    }

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
