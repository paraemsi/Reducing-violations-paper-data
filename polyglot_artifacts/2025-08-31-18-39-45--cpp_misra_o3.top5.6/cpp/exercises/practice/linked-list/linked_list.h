#pragma once

#include <cstdint>
#include <stdexcept>

namespace linked_list {

/*  Alias used for all size related values to avoid direct use of implementation
    defined unsigned long. */
using index_t = std::uint64_t;

/*  A doubly-linked list that supports push, pop, shift, unshift, count and
    erase operations.  The entire implementation is contained in the header so
    that the compiler can instantiate the templates as required. */
template <typename T>
class List {
private:
    struct Node {
        T     value;
        Node* prev;
        Node* next;

        explicit Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
        Node(const Node&)            = delete;
        Node& operator=(const Node&) = delete;
    };

    Node*   m_head;
    Node*   m_tail;
    index_t m_size;

public:
    List() : m_head(nullptr), m_tail(nullptr), m_size(static_cast<index_t>(0)) {}

    ~List() {
        clear();
    }

    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
        : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = static_cast<index_t>(0);
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            m_head      = other.m_head;
            m_tail      = other.m_tail;
            m_size      = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = static_cast<index_t>(0);
        }
        return *this;
    }

    /*  Add an element to the end of the list. */
    void push(const T& element) {
        Node* const new_node = new Node(element);
        if (m_tail == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            new_node->prev = m_tail;
            m_tail->next   = new_node;
            m_tail         = new_node;
        }
        ++m_size;
    }

    /*  Remove and return the element at the end of the list. */
    T pop() {
        if (m_tail == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* const node_to_remove = m_tail;
        T           ret_val        = node_to_remove->value;

        m_tail = node_to_remove->prev;
        if (m_tail != nullptr) {
            m_tail->next = nullptr;
        } else {
            m_head = nullptr;
        }

        delete node_to_remove;
        --m_size;
        return ret_val;
    }

    /*  Add an element to the start of the list. */
    void unshift(const T& element) {
        Node* const new_node = new Node(element);
        if (m_head == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            new_node->next = m_head;
            m_head->prev   = new_node;
            m_head         = new_node;
        }
        ++m_size;
    }

    /*  Remove and return the element at the start of the list. */
    T shift() {
        if (m_head == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* const node_to_remove = m_head;
        T           ret_val        = node_to_remove->value;

        m_head = node_to_remove->next;
        if (m_head != nullptr) {
            m_head->prev = nullptr;
        } else {
            m_tail = nullptr;
        }

        delete node_to_remove;
        --m_size;
        return ret_val;
    }

    /*  Remove the first occurrence of value from the list. */
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
                --m_size;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /*  Return the number of elements currently stored. */
    index_t count() const noexcept {
        return m_size;
    }

private:
    void clear() noexcept {
        Node* current = m_head;
        while (current != nullptr) {
            Node* const to_delete = current;
            current               = current->next;
            delete to_delete;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = static_cast<index_t>(0);
    }
};

}  // namespace linked_list
