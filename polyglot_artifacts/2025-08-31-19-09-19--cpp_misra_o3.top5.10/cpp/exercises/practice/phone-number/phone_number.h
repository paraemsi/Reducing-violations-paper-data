#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

/* Class representing a sanitized phone number. */
class phone_number
{
public:
    explicit phone_number(const std::string &input);

    auto number() const -> std::string;
    auto area_code() const -> std::string;
    auto pretty_print() const -> std::string;

private:
    std::string cleaned_number_;
};


}  // namespace phone_number

#endif // PHONE_NUMBER_H
