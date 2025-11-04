#include "knapsack.h"

#include <functional>
#include <unordered_map>

namespace knapsack
{

namespace
{
struct Key
{
    std::int64_t index;
    std::int64_t capacity;
};

struct KeyHash
{
    std::size_t operator()(const Key& k) const noexcept
    {
        const std::size_t h1 = std::hash<std::int64_t>{}(k.index);
        const std::size_t h2 = std::hash<std::int64_t>{}(k.capacity);
        return (h1 ^ (h2 + static_cast<std::size_t>(0x9e3779b97f4a7c15ULL) + (h1 << 6U) + (h1 >> 2U)));
    }
};

struct KeyEq
{
    bool operator()(const Key& a, const Key& b) const noexcept
    {
        return ((a.index == b.index) && (a.capacity == b.capacity));
    }
};

static std::int64_t maximum_value_impl(
    std::int64_t index,
    std::int64_t capacity,
    const std::vector<Item>& items,
    std::unordered_map<Key, std::int64_t, KeyHash, KeyEq>& memo)
{
    if ((capacity <= static_cast<std::int64_t>(0)) || (index >= static_cast<std::int64_t>(items.size())))
    {
        return static_cast<std::int64_t>(0);
    }

    const Key key{index, capacity};
    const auto it = memo.find(key);
    if (it != memo.end())
    {
        return it->second;
    }

    const Item& item = items.at(static_cast<std::size_t>(index));
    const std::int64_t weight = static_cast<std::int64_t>(item.weight);
    const std::int64_t value = static_cast<std::int64_t>(item.value);

    const std::int64_t best_without = maximum_value_impl((index + static_cast<std::int64_t>(1)), capacity, items, memo);

    std::int64_t best_with = best_without;
    if (weight <= capacity)
    {
        const std::int64_t with_val =
            (value + maximum_value_impl((index + static_cast<std::int64_t>(1)), (capacity - weight), items, memo));
        if (with_val > best_with)
        {
            best_with = with_val;
        }
    }

    const std::int64_t result = ((best_without > best_with) ? best_without : best_with);
    memo.emplace(key, result);
    return result;
}
} // namespace

std::int64_t maximum_value(std::int64_t capacity, const std::vector<Item>& items)
{
    std::unordered_map<Key, std::int64_t, KeyHash, KeyEq> memo{};
    return maximum_value_impl(static_cast<std::int64_t>(0), capacity, items, memo);
}

} // namespace knapsack

