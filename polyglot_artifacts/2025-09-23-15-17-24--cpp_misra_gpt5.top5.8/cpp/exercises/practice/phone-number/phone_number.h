#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);

    // Returns the cleaned digits. For NANP inputs this will typically be 10 digits.
    std::string number() const;

    // First three digits of the cleaned number, or empty string if unavailable.
    std::string area_code() const;

    // Pretty-printed form: "(NXX) NXX-XXXX" when at least 10 digits are available;
    // otherwise returns the cleaned digits as-is.
    std::string to_string() const;

    // Alias of to_string() for convenience in some code bases.
    std::string pretty() const;

private:
    std::string digits_;
};

// Free function to clean a phone number string according to the rules:
// - Remove all non-digit characters
// - If there are 11 digits and the first is '1', remove the leading '1'
std::string clean_number(const std::string& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H
