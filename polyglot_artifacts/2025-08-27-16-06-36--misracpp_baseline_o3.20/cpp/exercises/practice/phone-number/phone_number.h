#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

// Return the cleaned 10-digit telephone number or "0000000000" if invalid.
std::string number(const std::string& input);

// Return the area code (first three digits) of a cleaned number.
// If the input is invalid, returns "000".
std::string area_code(const std::string& input);

// Return the phone number in the standard pretty format:
// "(AAA) BBB-CCCC".  If the input is invalid it returns
// "(000) 000-0000".
std::string pretty(const std::string& input);

// Object-oriented interface expected by the tests.
class phone_number {
public:
    explicit phone_number(const std::string& input);

    std::string number() const;
    std::string area_code() const;
    std::string pretty() const;

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
