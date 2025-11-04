#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstddef>
#include <cstdint>

namespace phone_number {

class phone_number final {
public:
    explicit phone_number(const std::string& input);
    std::string number() const;
    std::string area_code() const;
    std::string to_string() const;

private:
    std::string cleaned_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
