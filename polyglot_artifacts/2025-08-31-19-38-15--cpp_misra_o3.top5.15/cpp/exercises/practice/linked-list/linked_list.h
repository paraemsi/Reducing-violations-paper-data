#pragma once

#include <cstdint>     // for fixed-width integer types
#include <cstddef>     // for std::size_t
#include <stdexcept>   // for std::out_of_range
#include <utility>     // for std::move

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        template <typename U>
        explicit Node(U&& val)
            : value(std::forward<U>(val)), prev(nullptr), next(nullptr) {}
    };

    Node*       m_head;
    Node*       m_tail;
    std::size_t m_count;

public:
    List() : m_head(nullptr), m_tail(nullptr), m_count(static_cast<std::size_t>(0)) {}

    List(const List&) = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
        : m_head(other.m_head), m_tail(other.m_tail), m_count(other.m_count) {
        other.m_head  = nullptr;
        other.m_tail  = nullptr;
        other.m_count = static_cast<std::size_t>(0);
    }

    List& operator=(List&& other) noexcept {
        if ((this != &other)) {
            clear();
            m_head       = other.m_head;
            m_tail       = other.m_tail;
            m_count      = other.m_count;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_count = static_cast<std::size_t>(0);
        }
        return *this;
    }

    ~List() {
        clear();
    }

    void push(const T& value) {
        Node* new_node = new Node(value);
        if (m_tail == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            new_node->prev = m_tail;
            m_tail->next   = new_node;
            m_tail         = new_node;
        }
        ++m_count;
    }

    void push(T&& value) {
        Node* new_node = new Node(std::move(value));
        if (m_tail == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            new_node->prev = m_tail;
            m_tail->next   = new_node;
            m_tail         = new_node;
        }
        ++m_count;
    }

    T pop() {
        if (m_tail == nullptr) {
            throw std::out_of_range("pop from empty list");
        }
        Node* node = m_tail;
        T     result = std::move(node->value);
        m_tail = node->prev;
        if (m_tail != nullptr) {
            m_tail->next = nullptr;
        } else {
            m_head = nullptr;
        }
        delete node;
        --m_count;
        return result;
    }

    void unshift(const T& value) {
        Node* new_node = new Node(value);
        if (m_head == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            new_node->next = m_head;
            m_head->prev   = new_node;
            m_head         = new_node;
        }
        ++m_count;
    }

    void unshift(T&& value) {
        Node* new_node = new Node(std::move(value));
        if (m_head == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            new_node->next = m_head;
            m_head->prev   = new_node;
            m_head         = new_node;
        }
        ++m_count;
    }

    T shift() {
        if (m_head == nullptr) {
            throw std::out_of_range("shift from empty list");
        }
        Node* node = m_head;
        T     result = std::move(node->value);
        m_head = node->next;
        if (m_head != nullptr) {
            m_head->prev = nullptr;
        } else {
            m_tail = nullptr;
        }
        delete node;
        --m_count;
        return result;
    }

    bool erase(const T& value) {
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
                --m_count;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    std::size_t count() const {
        return m_count;
    }

private:
    void clear() {
        Node* current = m_head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        m_head  = nullptr;
        m_tail  = nullptr;
        m_count = static_cast<std::size_t>(0);
    }
};

}  // namespace linked_list
