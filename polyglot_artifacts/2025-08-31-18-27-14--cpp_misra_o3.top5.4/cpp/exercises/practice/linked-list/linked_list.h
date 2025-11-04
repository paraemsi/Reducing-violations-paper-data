#pragma once

#include <cstdint>
#include <stdexcept>

namespace linked_list {

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
template <typename T>
class List {
private:
    struct Node {
        T       data;
        Node*   prev;
        Node*   next;

        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node*         head_;
    Node*         tail_;
    std::uint32_t size_;

    void clear() noexcept
    {
        Node* current { head_ };
        while (current != nullptr) {
            Node* const next_node { current->next };
            delete current;
            current = next_node;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

public:
    List() : head_(nullptr), tail_(nullptr), size_(0U) {}

    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept :
        head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            head_       = other.head_;
            tail_       = other.tail_;
            size_       = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* const new_node { new Node(value) };
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            new_node->prev = tail_;
            tail_->next    = new_node;
            tail_          = new_node;
        }
        ++size_;
    }

    void unshift(const T& value)
    {
        Node* const new_node { new Node(value) };
        if (head_ == nullptr) {
            head_ = new_node;
            tail_ = new_node;
        } else {
            new_node->next = head_;
            head_->prev    = new_node;
            head_          = new_node;
        }
        ++size_;
    }

    T pop()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("pop from empty list");
        }

        Node* const node_to_remove { tail_ };
        const T     value { node_to_remove->data };

        tail_ = node_to_remove->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }

        delete node_to_remove;
        --size_;
        return value;
    }

    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift from empty list");
        }

        Node* const node_to_remove { head_ };
        const T     value { node_to_remove->data };

        head_ = node_to_remove->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }

        delete node_to_remove;
        --size_;
        return value;
    }

    bool erase(const T& value)
    {
        Node* current { head_ };
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail_ = current->prev;
                }

                delete current;
                --size_;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    std::uint32_t count() const noexcept
    {
        return size_;
    }
};

}  // namespace linked_list
