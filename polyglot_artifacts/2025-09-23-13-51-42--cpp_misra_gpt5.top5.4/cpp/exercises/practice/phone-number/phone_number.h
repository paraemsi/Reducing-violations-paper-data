#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

class phone_number final {
public:
    explicit phone_number(const std::string& input);
    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string digits_;
};

// Clean a user-entered NANP phone number by:
// - removing all non-digit characters
// - stripping a leading country code '1' when the result has 11 digits
// Returns the digits-only phone number (typically 10 digits).
[[nodiscard]] std::string clean(const std::string& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H
