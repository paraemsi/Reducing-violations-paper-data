#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : is_open_(false), balance_(0) {}

// move constructor
Bankaccount::Bankaccount(Bankaccount&& other) noexcept {
  // Safely read other's state
  std::lock_guard<std::mutex> lock(other.mtx_);
  is_open_ = other.is_open_;
  balance_ = other.balance_;
  // Leave moved-from in a safe, closed, zero-balance state
  other.is_open_ = false;
  other.balance_ = 0;
}

// move assignment
Bankaccount& Bankaccount::operator=(Bankaccount&& other) noexcept {
  if (this != &other) {
    // Lock both mutexes without deadlock
    std::unique_lock<std::mutex> lk1(mtx_, std::defer_lock);
    std::unique_lock<std::mutex> lk2(other.mtx_, std::defer_lock);
    std::lock(lk1, lk2);

    is_open_ = other.is_open_;
    balance_ = other.balance_;
    other.is_open_ = false;
    other.balance_ = 0;
  }
  return *this;
}

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (is_open_) {
    throw std::runtime_error("account already open");
  }
  is_open_ = true;
  balance_ = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  is_open_ = false;
}

void Bankaccount::deposit(int amount) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account closed");
  }
  if (amount < 0) {
    throw std::runtime_error("cannot deposit negative amount");
  }
  balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account closed");
  }
  if (amount < 0) {
    throw std::runtime_error("cannot withdraw negative amount");
  }
  if (amount > balance_) {
    throw std::runtime_error("insufficient funds");
  }
  balance_ -= amount;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account closed");
  }
  return balance_;
}

}  // namespace Bankaccount
