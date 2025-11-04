#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <type_traits>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T               data;
        Node*           prev;
        Node*           next;

        explicit Node(const T& value) :
            data(value),
            prev(nullptr),
            next(nullptr) { }

        explicit Node(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value) :
            data(std::move(value)),
            prev(nullptr),
            next(nullptr) { }
    };

    Node*           head_;
    Node*           tail_;
    std::size_t     size_;

    /* Delete copy operations to avoid accidental slicing / double-free */
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

public:
    List() :
        head_(nullptr),
        tail_(nullptr),
        size_(static_cast<std::size_t>(0U)) { }

    ~List() {
        while (head_ != nullptr) {
            Node* const old_head{ head_ };
            head_ = head_->next;
            delete old_head;
        }
    }

    List(List&& other) noexcept :
        head_(other.head_),
        tail_(other.tail_),
        size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = static_cast<std::size_t>(0U);
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            /* release current resources */
            while (head_ != nullptr) {
                Node* const old_head{ head_ };
                head_ = head_->next;
                delete old_head;
            }

            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = static_cast<std::size_t>(0U);
        }
        return *this;
    }

    void push(const T& value) {
        Node* const new_node{ new Node(value) };

        if (tail_ == nullptr) {
            /* List is empty */
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }

        ++size_;
    }

    void push(T&& value) {
        Node* const new_node{ new Node(std::move(value)) };

        if (tail_ == nullptr) {
            /* List is empty */
            head_ = new_node;
            tail_ = new_node;
        } else {
            tail_->next  = new_node;
            new_node->prev = tail_;
            tail_         = new_node;
        }

        ++size_;
    }

    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty list");
        }

        Node* const old_tail{ tail_ };
        T           value{ std::move(tail_->data) };

        tail_ = tail_->prev;

        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            /* List became empty */
            head_ = nullptr;
        }

        delete old_tail;
        --size_;
        return value;
    }

    void unshift(const T& value) {
        Node* const new_node{ new Node(value) };

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

    void unshift(T&& value) {
        Node* const new_node{ new Node(std::move(value)) };

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

    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty list");
        }

        Node* const old_head{ head_ };
        T           value{ std::move(head_->data) };

        head_ = head_->next;

        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            /* List became empty */
            tail_ = nullptr;
        }

        delete old_head;
        --size_;
        return value;
    }

    bool erase(const T& value) {
        Node* current{ head_ };

        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    /* Removing head */
                    head_ = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    /* Removing tail */
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

    [[nodiscard]] std::size_t count() const noexcept {
        return size_;
    }
};

}  // namespace linked_list
