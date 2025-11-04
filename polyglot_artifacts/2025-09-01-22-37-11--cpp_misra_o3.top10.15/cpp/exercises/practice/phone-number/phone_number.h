#if !defined(PHONE_NUMBER_H)
#define PHONE_NUMBER_H

#include <string>
#include <cstdint>

namespace phone_number {

class phone_number {
public:
    explicit phone_number(const std::string& input_number);

    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string pretty() const;

private:
    [[nodiscard]] static bool is_valid_length(const std::string& digits) noexcept;
    [[nodiscard]] static bool is_valid_area_and_exchange(const std::string& digits) noexcept;

    std::string digits_{};
};

}  // namespace phone_number

#endif // PHONE_NUMBER_H
