#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : is_open_(false), balance_(0) {}

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (is_open_) {
    throw std::runtime_error("account already open");
  }
  balance_ = 0;
  is_open_ = true;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account already closed");
  }
  is_open_ = false;
}

void Bankaccount::deposit(int amount) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account is closed");
  }
  if (amount < 0) {
    throw std::runtime_error("cannot deposit negative amount");
  }
  balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account is closed");
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
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account is closed");
  }
  return balance_;
}

}  // namespace Bankaccount
