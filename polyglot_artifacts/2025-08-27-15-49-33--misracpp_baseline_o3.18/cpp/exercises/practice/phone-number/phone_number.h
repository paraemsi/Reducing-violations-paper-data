#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);

    // Return the cleaned 10-digit telephone number.
    std::string number() const;

    // Return the 3-digit area code.
    std::string area_code() const;

    // Return a user-friendly representation: "(XXX) XXX-XXXX".
    std::string pretty() const;

private:
    std::string digits_;     // always holds exactly 10 digits
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
