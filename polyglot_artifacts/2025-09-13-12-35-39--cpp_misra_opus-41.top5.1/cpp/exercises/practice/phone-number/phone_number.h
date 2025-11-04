#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <stdexcept>

namespace phone_number {

class PhoneNumber {
public:
    explicit PhoneNumber(const std::string& input);
    std::string number() const;

private:
    std::string cleaned_number;
};

// Alias for backward compatibility with tests
using phone_number = PhoneNumber;

}  // namespace phone_number

#endif // PHONE_NUMBER_H
