#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
public:
    List() noexcept
        : m_head(nullptr), m_tail(nullptr), m_count(static_cast<std::size_t>(0)) {
    }

    List(const List& other)
        : m_head(nullptr), m_tail(nullptr), m_count(static_cast<std::size_t>(0)) {
        const Node* current = other.m_head;
        while (current != nullptr) {
            this->push(current->value);
            current = current->next;
        }
    }

    List(List&& other) noexcept
        : m_head(other.m_head), m_tail(other.m_tail), m_count(other.m_count) {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_count = static_cast<std::size_t>(0);
    }

    List& operator=(const List& other) {
        if (this != &other) {
            this->destroy_all();
            const Node* current = other.m_head;
            while (current != nullptr) {
                this->push(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            this->destroy_all();
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_count = other.m_count;

            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_count = static_cast<std::size_t>(0);
        }
        return *this;
    }

    ~List() {
        this->destroy_all();
    }

    void push(const T& value) {
        Node* node = new Node(value);
        this->push_node(node);
    }

    void push(T&& value) {
        Node* node = new Node(std::move(value));
        this->push_node(node);
    }

    T pop() {
        if (m_tail == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* node = m_tail;
        T result = std::move(node->value);

        if (node->prev != nullptr) {
            m_tail = node->prev;
            m_tail->next = nullptr;
        } else {
            // Removing the last remaining element
            m_head = nullptr;
            m_tail = nullptr;
        }

        delete node;
        m_count = (m_count - static_cast<std::size_t>(1));
        return result;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        this->unshift_node(node);
    }

    void unshift(T&& value) {
        Node* node = new Node(std::move(value));
        this->unshift_node(node);
    }

    T shift() {
        if (m_head == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* node = m_head;
        T result = std::move(node->value);

        if (node->next != nullptr) {
            m_head = node->next;
            m_head->prev = nullptr;
        } else {
            // Removing the last remaining element
            m_head = nullptr;
            m_tail = nullptr;
        }

        delete node;
        m_count = (m_count - static_cast<std::size_t>(1));
        return result;
    }

    std::size_t count() const noexcept {
        return m_count;
    }

    bool erase(const T& value) {
        Node* current = m_head;
        while (current != nullptr) {
            if (current->value == value) {
                Node* const prev = current->prev;
                Node* const next = current->next;

                if (prev != nullptr) {
                    prev->next = next;
                } else {
                    m_head = next;
                }

                if (next != nullptr) {
                    next->prev = prev;
                } else {
                    m_tail = prev;
                }

                delete current;
                m_count = (m_count - static_cast<std::size_t>(1));
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v)
            : value(v), prev(nullptr), next(nullptr) {
        }

        explicit Node(T&& v)
            : value(std::move(v)), prev(nullptr), next(nullptr) {
        }
    };

    Node* m_head;
    Node* m_tail;
    std::size_t m_count;

    void destroy_all() noexcept {
        Node* current = m_head;
        while (current != nullptr) {
            Node* const next = current->next;
            delete current;
            current = next;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_count = static_cast<std::size_t>(0);
    }

    void push_node(Node* node) noexcept {
        node->next = nullptr;
        node->prev = m_tail;

        if (m_tail == nullptr) {
            // Empty list
            m_head = node;
            m_tail = node;
        } else {
            m_tail->next = node;
            m_tail = node;
        }

        m_count = (m_count + static_cast<std::size_t>(1));
    }

    void unshift_node(Node* node) noexcept {
        node->prev = nullptr;
        node->next = m_head;

        if (m_head == nullptr) {
            // Empty list
            m_head = node;
            m_tail = node;
        } else {
            m_head->prev = node;
            m_head = node;
        }

        m_count = (m_count + static_cast<std::size_t>(1));
    }
};

}  // namespace linked_list
