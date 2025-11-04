#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string &input);

    // Return the cleaned 10-digit phone number or "0000000000" when invalid
    std::string number() const;

    // Return the 3-digit area code part of the phone number
    std::string area_code() const;

    // Return the number in human-readable form: "(XXX) XXX-XXXX"
    std::string pretty() const;

private:
    std::string digits_;

    // Validate NANP rules on the already-cleaned digits
    static bool is_valid(const std::string &digits);
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
