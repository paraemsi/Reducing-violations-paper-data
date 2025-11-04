#pragma once

#include <cstddef>      // for std::size_t
#include <stdexcept>    // for std::out_of_range
#include <utility>      // for std::move

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T         data;
        Node*     next {nullptr};
        Node*     prev {nullptr};

        explicit Node(const T& value) : data(value) {}
        explicit Node(T&& value) : data(std::move(value)) {}
        Node(const Node&)            = delete;
        Node(Node&&)                 = delete;
        Node& operator=(const Node&) = delete;
        Node& operator=(Node&&)      = delete;
    };

    Node*       m_head {nullptr};
    Node*       m_tail {nullptr};
    std::size_t m_size {0U};

public:
    List() = default;

    /* Rule of five */
    List(const List&)            = delete;
    List& operator=(const List&) = delete;
    List(List&& other) noexcept  : m_head(other.m_head),
                                   m_tail(other.m_tail),
                                   m_size(other.m_size) {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0U;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            m_head       = other.m_head;
            m_tail       = other.m_tail;
            m_size       = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0U;
        }
        return *this;
    }

    ~List() { clear(); }

    void push(const T& value) {
        Node* const new_node = new Node(value);
        if (m_tail == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        ++m_size;
    }

    void push(T&& value) {
        Node* const new_node = new Node(std::move(value));
        if (m_tail == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        ++m_size;
    }

    T pop() {
        if (m_tail == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* const old_tail = m_tail;
        T           value    = std::move(old_tail->data);

        m_tail = m_tail->prev;
        if (m_tail != nullptr) {
            m_tail->next = nullptr;
        } else {
            m_head = nullptr;
        }

        delete old_tail;
        --m_size;
        return value;
    }

    void unshift(const T& value) {
        Node* const new_node = new Node(value);
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

    void unshift(T&& value) {
        Node* const new_node = new Node(std::move(value));
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

    T shift() {
        if (m_head == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* const old_head = m_head;
        T           value    = std::move(old_head->data);

        m_head = m_head->next;
        if (m_head != nullptr) {
            m_head->prev = nullptr;
        } else {
            m_tail = nullptr;
        }

        delete old_head;
        --m_size;
        return value;
    }

    std::size_t count() const noexcept { return m_size; }

    bool erase(const T& value) {
        Node* current = m_head;
        while ((current != nullptr) && (!(current->data == value))) {
            current = current->next;
        }

        if (current == nullptr) {
            return false;
        }

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

private:
    void clear() noexcept {
        Node* iter = m_head;
        while (iter != nullptr) {
            Node* const next_node = iter->next;
            delete iter;
            iter = next_node;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0U;
    }
};

}  // namespace linked_list
