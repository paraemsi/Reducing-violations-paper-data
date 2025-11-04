#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <cstdint>
#include <string>

namespace phone_number {

class phone_number final {
public:
    explicit phone_number(const std::string& input);
    auto number() const -> std::string;
    auto area_code() const -> std::string;
    auto pretty() const -> std::string;

private:
    std::string digits_;
};

// Clean up a user-entered NANP phone number.
// - Removes all non-digit characters
// - If there are 11 digits and the first is '1' (country code), it is removed
// - Returns the resulting digit string (typically 10 digits for NANP)
std::string clean(const std::string& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H
