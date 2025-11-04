#pragma once

#include <cstddef>      // std::size_t
#include <cstdint>      // fixed-width integer types (MISRA)
#include <stdexcept>    // std::out_of_range
#include <utility>      // std::move

namespace linked_list {

template<typename T>
class List final {
private:
    struct Node {
        T              value;
        Node*          prev;
        Node*          next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v) : value(std::forward<T>(v)), prev(nullptr), next(nullptr) {}
    };

    Node*       m_head;
    Node*       m_tail;
    std::size_t m_size;

    void clear() noexcept
    {
        Node* current = m_head;
        while (current != nullptr) {
            Node* const next_node = current->next;
            delete current;
            current = next_node;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = std::size_t{0};
    }

public:
    List() : m_head(nullptr), m_tail(nullptr), m_size(std::size_t{0}) {}

    List(const List& other) = delete;
    List& operator=(const List& other) = delete;

    List(List&& other) noexcept :
        m_head(other.m_head),
        m_tail(other.m_tail),
        m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = std::size_t{0};
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            m_head      = other.m_head;
            m_tail      = other.m_tail;
            m_size      = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = std::size_t{0};
        }
        return *this;
    }

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* const node = new Node(value);
        if (m_tail == nullptr) {
            m_head = node;
            m_tail = node;
        } else {
            node->prev = m_tail;
            m_tail->next = node;
            m_tail = node;
        }
        ++m_size;
    }

    void push(T&& value)
    {
        Node* const node = new Node(std::move(value));
        if (m_tail == nullptr) {
            m_head = node;
            m_tail = node;
        } else {
            node->prev = m_tail;
            m_tail->next = node;
            m_tail = node;
        }
        ++m_size;
    }

    void unshift(const T& value)
    {
        Node* const node = new Node(value);
        if (m_head == nullptr) {
            m_head = node;
            m_tail = node;
        } else {
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }
        ++m_size;
    }

    void unshift(T&& value)
    {
        Node* const node = new Node(std::move(value));
        if (m_head == nullptr) {
            m_head = node;
            m_tail = node;
        } else {
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }
        ++m_size;
    }

    T pop()
    {
        if (m_tail == nullptr) {
            throw std::out_of_range("pop on empty list");
        }
        Node* const node = m_tail;
        T           val  = std::move(node->value);

        m_tail = node->prev;
        if (m_tail != nullptr) {
            m_tail->next = nullptr;
        } else {
            m_head = nullptr;
        }
        delete node;
        --m_size;
        return val;
    }

    T shift()
    {
        if (m_head == nullptr) {
            throw std::out_of_range("shift on empty list");
        }
        Node* const node = m_head;
        T           val  = std::move(node->value);

        m_head = node->next;
        if (m_head != nullptr) {
            m_head->prev = nullptr;
        } else {
            m_tail = nullptr;
        }
        delete node;
        --m_size;
        return val;
    }

    bool erase(const T& value)
    {
        Node* current = m_head;
        while (current != nullptr) {
            if (current->value == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    m_head = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    m_tail = current->prev;
                }

                delete current;
                --m_size;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    [[nodiscard]] std::size_t count() const noexcept
    {
        return m_size;
    }
};

}  // namespace linked_list
