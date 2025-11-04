#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {


class phone_number {
public:
    explicit phone_number(const std::string& input);
    std::string number() const noexcept;

private:
    std::string digits_;
};

std::string clean_number(const std::string& input);

}  // namespace phone_number

#endif // PHONE_NUMBER_H
