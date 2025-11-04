#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>
#include <cstddef>   /* for std::size_t */

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& raw);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    std::string cleaned_number_;
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
