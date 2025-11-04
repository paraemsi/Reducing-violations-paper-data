#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>

namespace phone_number {

class phone_number {
public:
    phone_number(const std::string& number);
    std::string number() const;

private:
    std::string cleaned;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
