#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);
    const std::string& number() const;
    std::string area_code() const;
    std::string to_string() const;

private:
    std::string digits_;
};

// Clean up a user-entered phone number.
// - remove all non-digit characters
// - if it has 11 digits and starts with '1', drop the leading '1'
// - resulting number must be exactly 10 digits, otherwise std::invalid_argument is thrown by the implementation
std::string clean(const std::string& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H
