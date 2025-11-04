#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H
#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);

    // Return the cleaned 10-digit phone number, or "0000000000" if invalid.
    std::string number() const;

    // The first three digits (area code) of the cleaned number.
    std::string area_code() const;

    // Pretty formatted version: "(XXX) XXX-XXXX".
    std::string pretty() const;

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
