#pragma once

#include <cstdint>     // fixed-width integer types
#include <cstddef>     // std::size_t
#include <stdexcept>   // std::out_of_range

namespace linked_list {

template <typename T>
class List {
public:
    List() noexcept : m_head(nullptr), m_tail(nullptr), m_size(0U) {}
    List(const List&)            = delete;
    List(List&&)                 = delete;
    List& operator=(const List&) = delete;
    List& operator=(List&&)      = delete;

    ~List() noexcept { clear(); }

    // adds an element to the end of the list
    void push(const T& value);

    // removes and returns the last element of the list
    T pop();

    // removes and returns the first element of the list
    T shift();

    // adds an element to the start of the list
    void unshift(const T& value);

    // returns the total number of elements in the current list
    std::uint32_t count() const noexcept { return m_size; }

    // removes the first occurrence of 'value'
    // returns true if an element was removed, false otherwise
    bool erase(const T& value);

private:
    struct Node {
        explicit Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
        T       value;
        Node*   prev;
        Node*   next;
    };

    Node*         m_head;
    Node*         m_tail;
    std::uint32_t m_size;

    void clear() noexcept;
};

}  // namespace linked_list
