#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T      data {};
        Node*  previous {nullptr};
        Node*  next {nullptr};

        explicit Node(const T& value) : data(value) {}
    };

    Node*         m_head {nullptr};
    Node*         m_tail {nullptr};
    std::size_t   m_size {0U};

    void copy_from(const List& other)
    {
        for (Node* current = other.m_head; current != nullptr; current = current->next) {
            push(current->data);
        }
    }

    void clear() noexcept
    {
        while (m_head != nullptr) {
            Node* temp = m_head;
            m_head     = m_head->next;
            delete temp;
        }
        m_tail = nullptr;
        m_size = 0U;
    }

public:
    List() = default;

    ~List()
    {
        clear();
    }

    List(const List& other) : List()
    {
        copy_from(other);
    }

    List(List&& other) noexcept :
        m_head(other.m_head),
        m_tail(other.m_tail),
        m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0U;
    }

    List& operator=(const List& other)
    {
        if (this != &other) {
            List temp(other);
            swap(temp);
        }
        return *this;
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
            other.m_size = 0U;
        }
        return *this;
    }

    void swap(List& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }

    std::size_t count() const noexcept
    {
        return m_size;
    }

    void push(const T& value)
    {
        Node* node = new Node(value);
        if (m_tail == nullptr) {
            m_head = node;
            m_tail = node;
        } else {
            node->previous = m_tail;
            m_tail->next   = node;
            m_tail         = node;
        }
        ++m_size;
    }

    void unshift(const T& value)
    {
        Node* node = new Node(value);
        if (m_head == nullptr) {
            m_head = node;
            m_tail = node;
        } else {
            node->next   = m_head;
            m_head->previous = node;
            m_head       = node;
        }
        ++m_size;
    }

    T pop()
    {
        if (m_tail == nullptr) {
            throw std::out_of_range("pop from empty list");
        }

        Node* node = m_tail;
        T     value = node->data;

        m_tail = m_tail->previous;
        if (m_tail != nullptr) {
            m_tail->next = nullptr;
        } else {
            m_head = nullptr;
        }

        delete node;
        --m_size;
        return value;
    }

    T shift()
    {
        if (m_head == nullptr) {
            throw std::out_of_range("shift from empty list");
        }

        Node* node = m_head;
        T     value = node->data;

        m_head = m_head->next;
        if (m_head != nullptr) {
            m_head->previous = nullptr;
        } else {
            m_tail = nullptr;
        }

        delete node;
        --m_size;
        return value;
    }

    bool erase(const T& value)
    {
        for (Node* current = m_head; current != nullptr; current = current->next) {
            if (current->data == value) {
                if (current->previous != nullptr) {
                    current->previous->next = current->next;
                } else {
                    m_head = current->next;
                }

                if (current->next != nullptr) {
                    current->next->previous = current->previous;
                } else {
                    m_tail = current->previous;
                }

                delete current;
                --m_size;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
