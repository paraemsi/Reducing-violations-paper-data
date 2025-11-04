#pragma once

#include <cstdint>
#include <type_traits>
#include <vector>
#include <initializer_list>
#include <string_view>

namespace yacht {

enum class category : std::uint8_t {
    ones,
    twos,
    threes,
    fours,
    fives,
    sixes,
    full_house,
    four_of_a_kind,
    little_straight,
    big_straight,
    choice,
    yacht
};

auto score(const std::vector<std::int32_t>& dice, category cat) -> std::int32_t;
auto score(const std::vector<std::int32_t>& dice, const char* cat) -> std::int32_t;
auto score(std::initializer_list<std::int32_t> dice, category cat) -> std::int32_t;
auto score(std::initializer_list<std::int32_t> dice, const char* cat) -> std::int32_t;
auto score(const std::vector<std::int32_t>& dice, std::string_view cat) -> std::int32_t;
auto score(std::initializer_list<std::int32_t> dice, std::string_view cat) -> std::int32_t;

template <typename T>
inline auto score(const std::vector<T>& dice, category cat) -> std::int32_t
{
    static_assert(std::is_integral<T>::value, "Dice value type must be an integral type");
    static_assert(std::is_signed<T>::value, "Dice value type must be a signed integral type");
    static_assert(
        (sizeof(T) <= sizeof(std::int32_t)),
        "Dice value type must be no wider than std::int32_t");
    static_assert(!std::is_same<T, char>::value, "char type is not allowed");
    static_assert(!std::is_same<T, signed char>::value, "signed char type is not allowed");
    static_assert(!std::is_same<T, unsigned char>::value, "unsigned char type is not allowed");
    static_assert(!std::is_same<T, wchar_t>::value, "wchar_t type is not allowed");
    static_assert(!std::is_same<T, char16_t>::value, "char16_t type is not allowed");
    static_assert(!std::is_same<T, char32_t>::value, "char32_t type is not allowed");

    std::vector<std::int32_t> converted{};
    converted.reserve(dice.size());

    for (const auto& v : dice) {
        converted.push_back(static_cast<std::int32_t>(v));
    }

    return score(converted, cat);
}

template <typename T>
inline auto score(const std::vector<T>& dice, const char* cat) -> std::int32_t
{
    static_assert(std::is_integral<T>::value, "Dice value type must be an integral type");
    static_assert(std::is_signed<T>::value, "Dice value type must be a signed integral type");
    static_assert(
        (sizeof(T) <= sizeof(std::int32_t)),
        "Dice value type must be no wider than std::int32_t");
    static_assert(!std::is_same<T, char>::value, "char type is not allowed");
    static_assert(!std::is_same<T, signed char>::value, "signed char type is not allowed");
    static_assert(!std::is_same<T, unsigned char>::value, "unsigned char type is not allowed");
    static_assert(!std::is_same<T, wchar_t>::value, "wchar_t type is not allowed");
    static_assert(!std::is_same<T, char16_t>::value, "char16_t type is not allowed");
    static_assert(!std::is_same<T, char32_t>::value, "char32_t type is not allowed");

    std::vector<std::int32_t> converted{};
    converted.reserve(dice.size());

    for (const auto& v : dice) {
        converted.push_back(static_cast<std::int32_t>(v));
    }

    return score(converted, cat);
}

template <typename T>
inline auto score(const std::vector<T>& dice, std::string_view cat) -> std::int32_t
{
    static_assert(std::is_integral<T>::value, "Dice value type must be an integral type");
    static_assert(std::is_signed<T>::value, "Dice value type must be a signed integral type");
    static_assert(
        (sizeof(T) <= sizeof(std::int32_t)),
        "Dice value type must be no wider than std::int32_t");
    static_assert(!std::is_same<T, char>::value, "char type is not allowed");
    static_assert(!std::is_same<T, signed char>::value, "signed char type is not allowed");
    static_assert(!std::is_same<T, unsigned char>::value, "unsigned char type is not allowed");
    static_assert(!std::is_same<T, wchar_t>::value, "wchar_t type is not allowed");
    static_assert(!std::is_same<T, char16_t>::value, "char16_t type is not allowed");
    static_assert(!std::is_same<T, char32_t>::value, "char32_t type is not allowed");

    std::vector<std::int32_t> converted{};
    converted.reserve(dice.size());

    for (const auto& v : dice) {
        converted.push_back(static_cast<std::int32_t>(v));
    }

    return score(converted, cat);
}

}  // namespace yacht
