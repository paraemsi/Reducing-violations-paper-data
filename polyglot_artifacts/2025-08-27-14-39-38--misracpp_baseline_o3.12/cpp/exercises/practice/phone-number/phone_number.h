#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string &input);

    // 10–digit cleaned phone number or "0000000000" if invalid
    std::string number() const;

    // First three digits of the cleaned number
    std::string area_code() const;

    // Pretty-printed representation: "(AAA) BBB-CCCC"
    std::string pretty() const;

private:
    std::string number_{};

    // Validate 10-digit NANP number
    static bool is_valid(const std::string &digits);
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
