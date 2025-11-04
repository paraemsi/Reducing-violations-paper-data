#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T> class List {
private:
  struct Node {
    T data;
    Node *prev{nullptr};
    Node *next{nullptr};

    Node(T val) : data{std::move(val)} {}
  };

  Node *head_{nullptr};
  Node *tail_{nullptr};
  size_t size_{0};

private:
  void link_as_head(Node *node) {
    if (head_ == nullptr) {
      head_ = tail_ = node;
    } else {
      node->next = head_;
      head_->prev = node;
      head_ = node;
    }
    size_++;
  }

  void link_as_tail(Node *node) {
    if (tail_ == nullptr) {
      head_ = tail_ = node;
    } else {
      node->prev = tail_;
      tail_->next = node;
      tail_ = node;
    }
    size_++;
  }

public:
  List() = default;

  List(const List &) = delete;
  List &operator=(const List &) = delete;
  List(List &&) = delete;
  List &operator=(List &&) = delete;

  ~List() {
    while (head_ != nullptr) {
      Node *current = head_;
      head_ = head_->next;
      delete current;
    }
  }

  size_t count() const { return size_; }

  void push(const T &value) { link_as_tail(new Node(value)); }

  void push(T &&value) { link_as_tail(new Node(std::move(value))); }

  T pop() {
    if (tail_ == nullptr) {
      throw std::runtime_error("List is empty");
    }
    T popped_data = std::move(tail_->data);
    Node *temp = tail_;
    tail_ = tail_->prev;
    if (tail_ != nullptr) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete temp;
    size_--;
    return popped_data;
  }

  void unshift(const T &value) { link_as_head(new Node(value)); }

  void unshift(T &&value) { link_as_head(new Node(std::move(value))); }

  T shift() {
    if (head_ == nullptr) {
      throw std::runtime_error("List is empty");
    }
    T shifted_data = std::move(head_->data);
    Node *temp = head_;
    head_ = head_->next;
    if (head_ != nullptr) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete temp;
    size_--;
    return shifted_data;
  }

  bool erase(const T& value) {
    Node *current = head_;
    while (current != nullptr) {
      if (current->data == value) {
        if (current->prev) {
          current->prev->next = current->next;
        } else {
          head_ = current->next;
        }
        if (current->next) {
          current->next->prev = current->prev;
        } else {
          tail_ = current->prev;
        }
        delete current;
        size_--;
        return true;
      }
      current = current->next;
    }
    return false;
  }
};

} // namespace linked_list
