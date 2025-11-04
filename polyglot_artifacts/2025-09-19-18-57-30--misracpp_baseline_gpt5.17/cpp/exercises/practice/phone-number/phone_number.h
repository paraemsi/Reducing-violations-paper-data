#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);

    // Returns the cleaned 10-digit number.
    std::string number() const;

    // Returns the 3-digit area code.
    std::string area_code() const;

    // Returns the number formatted as "(NXX) NXX-XXXX".
    std::string pretty() const;

private:
    std::string digits_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
