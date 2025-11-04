#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input);
    std::string number() const;
    std::string area_code() const;
private:
    std::string cleaned_;
};

// Clean a NANP phone number by removing punctuation and optional country code (1 or +1).
// Returns a 10-digit string on success; throws std::domain_error on invalid input.
std::string clean(const std::string& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H
