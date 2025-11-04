#pragma once

#include <cstddef>      // for std::size_t
#include <stdexcept>    // for std::out_of_range
#include <utility>      // for std::move

namespace linked_list {

/*
 * A doubly-linked list implemented as a single header-only
 * templated class.  Operations have the following complexity:
 *  - push / pop        : O(1)
 *  - unshift / shift   : O(1)
 *  - erase (first hit) : O(n)
 *
 * The class intentionally disallows copy construction / assignment
 * to avoid accidental deep copies.  Move operations are provided.
 */
template <typename T>
class List {
public:
    List() = default;
    ~List() { clear(); }

    /* non-copyable */
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    /* movable */
    List(List&& other) noexcept : head_{other.head_}, tail_{other.tail_}, count_{other.count_} {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.count_ = static_cast<std::size_t>(0U);
    }

    List& operator=(List&& other) noexcept {
        if (this != &other) {
            clear();
            head_  = other.head_;
            tail_  = other.tail_;
            count_ = other.count_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.count_ = static_cast<std::size_t>(0U);
        }
        return *this;
    }

    /* Adds an element to the end of the list. */
    void push(const T& value) {
        Node* const new_node = new Node{value, tail_, nullptr};
        if (tail_ != nullptr) {
            tail_->next = new_node;
        } else {
            head_ = new_node;
        }
        tail_ = new_node;
        ++count_;
    }

    /* Removes and returns the last element. */
    T pop() {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop from empty list");
        }
        Node* const node = tail_;
        T data           = node->data;

        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr; /* list became empty */
        }
        delete node;
        --count_;
        return data;
    }

    /* Adds an element to the start of the list. */
    void unshift(const T& value) {
        Node* const new_node = new Node{value, nullptr, head_};
        if (head_ != nullptr) {
            head_->prev = new_node;
        } else {
            tail_ = new_node;
        }
        head_ = new_node;
        ++count_;
    }

    /* Removes and returns the first element. */
    T shift() {
        if (head_ == nullptr) {
            throw std::out_of_range("shift from empty list");
        }
        Node* const node = head_;
        T data           = node->data;

        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr; /* list became empty */
        }
        delete node;
        --count_;
        return data;
    }

    /* Removes the first occurrence of `value`.  Returns true on success. */
    bool erase(const T& value) {
        for (Node* current = head_; current != nullptr; current = current->next) {
            if (current->data == value) {
                unlink_node(current);
                delete current;
                --count_;
                return true;
            }
        }
        return false;
    }

    /* Returns the total number of elements in the list. */
    [[nodiscard]] std::size_t count() const noexcept { return count_; }

private:
    struct Node {
        T     data;
        Node* prev;
        Node* next;
    };

    Node*       head_  = nullptr;
    Node*       tail_  = nullptr;
    std::size_t count_ = static_cast<std::size_t>(0U);

    void unlink_node(Node* node) noexcept {
        /* (node->prev) and (node->next) adjustments are performed
         * with appropriate null-checks. */
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }

        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }
    }

    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* const next = current->next;
            delete current;
            current = next;
        }
        head_  = nullptr;
        tail_  = nullptr;
        count_ = static_cast<std::size_t>(0U);
    }
};

}  // namespace linked_list
