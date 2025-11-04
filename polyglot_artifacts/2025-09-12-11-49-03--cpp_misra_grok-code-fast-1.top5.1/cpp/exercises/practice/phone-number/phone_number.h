#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
private:
    std::string cleaned_number_;

public:
    explicit phone_number(const std::string& number);
    std::string number() const;
};

}  // namespace phone_number

#endif  // PHONE_NUMBER_H
