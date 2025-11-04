#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {


void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (is_open_) {
    throw std::runtime_error("account already open");
  }
  is_open_ = true;
  balance_ = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  is_open_ = false;
}

void Bankaccount::deposit(int amount) {
  if (amount < 0) {
    throw std::runtime_error("invalid deposit amount");
  }
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
  if (amount < 0) {
    throw std::runtime_error("invalid withdraw amount");
  }
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  if (balance_ < amount) {
    throw std::runtime_error("insufficient funds");
  }
  balance_ -= amount;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  return balance_;
}

}  // namespace Bankaccount
