#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& phone_number_string);
    std::string number() const;

private:
    std::string cleaned_number;
    std::string clean_and_validate(const std::string& input) const;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
