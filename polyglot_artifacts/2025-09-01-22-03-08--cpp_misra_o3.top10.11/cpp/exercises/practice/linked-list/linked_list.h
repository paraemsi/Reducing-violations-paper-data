#pragma once

#include <cstddef>      // std::size_t
#include <cstdint>      // fixed-width integer types (MISRA rule compliance)
#include <stdexcept>    // std::runtime_error
#include <utility>      // std::move

namespace linked_list {

// Doubly-linked list implementation that fulfils the Exercism interface
template <typename T>
class List final {
public:
private:

public:
    List() = default;
    ~List()
    {
        clear();
    }

    // Disable copy semantics – keeping ownership simple
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    // Enable move semantics
    List(List&& other) noexcept
    {
        head_         = other.head_;
        tail_         = other.tail_;
        element_count_ = other.element_count_;

        other.head_  = nullptr;
        other.tail_  = nullptr;
        other.element_count_ = static_cast<std::size_t>(0U);
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();

            head_         = other.head_;
            tail_         = other.tail_;
            element_count_ = other.element_count_;

            other.head_  = nullptr;
            other.tail_  = nullptr;
            other.element_count_ = static_cast<std::size_t>(0U);
        }
        return *this;
    }

    // Adds an element to the end of the list.
    void push(const T& value)
    {
        insert_back(value);
    }

    void push(T&& value)
    {
        insert_back(std::move(value));
    }

    // Removes and returns the last element of the list.
    T pop()
    {
        if (head_ == nullptr) {
            throw std::runtime_error("pop on empty list");
        }

        Node* const node_to_remove = tail_;
        T           result         = std::move(node_to_remove->data);

        tail_ = node_to_remove->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;      // List became empty
        }

        delete node_to_remove;
        --element_count_;

        return result;
    }

    // Removes and returns the first element of the list.
    T shift()
    {
        if (head_ == nullptr) {
            throw std::runtime_error("shift on empty list");
        }

        Node* const node_to_remove = head_;
        T           result         = std::move(node_to_remove->data);

        head_ = node_to_remove->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;      // List became empty
        }

        delete node_to_remove;
        --element_count_;

        return result;
    }

    // Adds an element to the start of the list.
    void unshift(const T& value)
    {
        insert_front(value);
    }

    void unshift(T&& value)
    {
        insert_front(std::move(value));
    }

    // Returns the total number of elements currently in the list.
    [[nodiscard]] std::size_t count() const noexcept
    {
        return element_count_;
    }

    // Removes the first occurrence of `value` from the list.
    // Returns true if a node was removed.
    bool erase(const T& value)
    {
        Node* current = head_;
        while (current != nullptr) {
            if (current->data == value) {
                remove_node(current);
                return true;
            }
            current = current->next;
        }
        return false;
    }

private:
    struct Node {
        explicit Node(const T& v) : data(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v)      : data(std::move(v)), prev(nullptr), next(nullptr) {}

        T      data;
        Node*  prev { nullptr };
        Node*  next { nullptr };
    };

    Node*        head_ { nullptr };
    Node*        tail_ { nullptr };
    std::size_t  element_count_ { static_cast<std::size_t>(0U) };

    template <typename U>
    void insert_back(U&& value)
    {
        Node* const new_node = new Node(std::forward<U>(value));
        new_node->prev = tail_;
        new_node->next = nullptr; // explicit initialisation

        if (tail_ != nullptr) {
            tail_->next = new_node;
        } else {
            head_ = new_node; // first element
        }

        tail_ = new_node;
        ++element_count_;
    }

    template <typename U>
    void insert_front(U&& value)
    {
        Node* const new_node = new Node(std::forward<U>(value));
        new_node->next = head_;
        new_node->prev = nullptr; // explicit initialisation

        if (head_ != nullptr) {
            head_->prev = new_node;
        } else {
            tail_ = new_node; // first element
        }

        head_ = new_node;
        ++element_count_;
    }

    void remove_node(Node* node)
    {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;   // removing head
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;   // removing tail
        }

        delete node;
        --element_count_;
    }

    void clear() noexcept
    {
        Node* current = head_;
        while (current != nullptr) {
            Node* const next_node = current->next;
            delete current;
            current = next_node;
        }
        head_ = nullptr;
        tail_ = nullptr;
        element_count_ = static_cast<std::size_t>(0U);
    }
};

} // namespace linked_list
