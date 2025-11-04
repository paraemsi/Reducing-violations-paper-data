#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : balance_(static_cast<money_t>(0)), open_(false) {}

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (open_) {
    throw std::runtime_error("Account already open");
  }
  balance_ = static_cast<money_t>(0);
  open_ = true;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("Account already closed");
  }
  /* Reset balance to zero when closing the account */
  balance_ = static_cast<money_t>(0);
  open_ = false;
}

void Bankaccount::deposit(money_t amount) {
  if ((amount <= static_cast<money_t>(0))) {
    throw std::runtime_error("Deposit amount must be positive");
  }
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("Account is closed");
  }
  balance_ += amount;
}

void Bankaccount::withdraw(money_t amount) {
  if ((amount <= static_cast<money_t>(0))) {
    throw std::runtime_error("Withdrawal amount must be positive");
  }
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("Account is closed");
  }
  if (balance_ < amount) {
    throw std::runtime_error("Insufficient funds");
  }
  balance_ -= amount;
}

money_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("Account is closed");
  }
  return balance_;
}

bool Bankaccount::is_open() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return open_;
}

}  // namespace Bankaccount
