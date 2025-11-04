#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
  struct Node {
    T value;
    Node* prev;
    Node* next;

    Node(const T& v, Node* p = nullptr, Node* n = nullptr)
        : value(v), prev(p), next(n) {}
    Node(T&& v, Node* p = nullptr, Node* n = nullptr)
        : value(std::move(v)), prev(p), next(n) {}
  };

public:
  List() = default;
  ~List() { clear(); }

  List(const List& other) { copy_from(other); }
  List& operator=(const List& other) {
    if (this != &other) {
      clear();
      copy_from(other);
    }
    return *this;
  }

  List(List&& other) noexcept { move_from(std::move(other)); }
  List& operator=(List&& other) noexcept {
    if (this != &other) {
      clear();
      move_from(std::move(other));
    }
    return *this;
  }

  // Adds an element to the end of the list
  void push(const T& value) { append_node(new Node(value)); }
  void push(T&& value) { append_node(new Node(std::move(value))); }

  // Removes and returns the last element of the list
  T pop() {
    if (!tail_) {
      throw std::out_of_range("pop from empty list");
    }
    Node* node = tail_;
    T val = std::move(node->value);
    tail_ = node->prev;
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete node;
    --size_;
    return val;
  }

  // Removes and returns the first element of the list
  T shift() {
    if (!head_) {
      throw std::out_of_range("shift from empty list");
    }
    Node* node = head_;
    T val = std::move(node->value);
    head_ = node->next;
    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete node;
    --size_;
    return val;
  }

  // Adds an element to the start of the list
  void unshift(const T& value) { prepend_node(new Node(value)); }
  void unshift(T&& value) { prepend_node(new Node(std::move(value))); }

  // Returns the total number of elements in the list
  std::size_t count() const { return size_; }

  // Removes the first occurrence of value. Returns true if removed.
  bool erase(const T& value) {
    for (Node* cur = head_; cur != nullptr; cur = cur->next) {
      if (cur->value == value) {
        if (cur->prev) {
          cur->prev->next = cur->next;
        } else {
          head_ = cur->next;
        }
        if (cur->next) {
          cur->next->prev = cur->prev;
        } else {
          tail_ = cur->prev;
        }
        delete cur;
        --size_;
        return true;
      }
    }
    return false;
  }

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  std::size_t size_ = 0;

  void append_node(Node* node) {
    node->prev = tail_;
    node->next = nullptr;
    if (tail_) {
      tail_->next = node;
    } else {
      head_ = node;
    }
    tail_ = node;
    ++size_;
  }

  void prepend_node(Node* node) {
    node->next = head_;
    node->prev = nullptr;
    if (head_) {
      head_->prev = node;
    } else {
      tail_ = node;
    }
    head_ = node;
    ++size_;
  }

  void clear() {
    Node* cur = head_;
    while (cur) {
      Node* next = cur->next;
      delete cur;
      cur = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  void copy_from(const List& other) {
    for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
      push(cur->value);
    }
  }

  void move_from(List&& other) noexcept {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
};

}  // namespace linked_list
