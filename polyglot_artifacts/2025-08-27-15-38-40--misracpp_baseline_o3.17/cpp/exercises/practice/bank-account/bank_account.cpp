#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (is_open_) {
    return;
  }
  is_open_ = true;
  balance_ = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("Account already closed");
  }
  is_open_ = false;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("Account closed");
  }
  return balance_;
}

void Bankaccount::deposit(int amount) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("Account closed");
  }
  if (amount <= 0) {
    throw std::runtime_error("Deposit of non-positive amount");
  }
  balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("Account closed");
  }
  if (amount <= 0) {
    throw std::runtime_error("Withdrawal of non-positive amount");
  }
  if (balance_ < amount) {
    throw std::runtime_error("Insufficient funds");
  }
  balance_ -= amount;
}

}  // namespace Bankaccount
