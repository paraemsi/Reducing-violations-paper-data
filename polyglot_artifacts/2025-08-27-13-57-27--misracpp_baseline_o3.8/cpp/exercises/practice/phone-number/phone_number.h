#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    // Construct from any user-entered string
    explicit phone_number(const std::string& raw);

    // Return the 10 clean digits (or “0000000000” for an invalid input)
    std::string number() const;

    // First three digits of a valid number
    std::string area_code() const;

    // “(AAA) BBB-CCCC” presentation
    std::string pretty() const;

private:
    std::string digits_;   // always 10 chars
    static bool valid(const std::string& digits);
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
