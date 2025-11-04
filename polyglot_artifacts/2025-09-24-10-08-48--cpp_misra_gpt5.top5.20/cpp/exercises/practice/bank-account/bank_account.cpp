#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() = default;

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (is_open_) {
    throw std::runtime_error("account already open");
  }
  balance_ = static_cast<std::int64_t>(0);
  is_open_ = true;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account already closed");
  }
  is_open_ = false;
}

void Bankaccount::deposit(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  if (amount < static_cast<std::int64_t>(0)) {
    throw std::runtime_error("amount must be non-negative");
  }
  balance_ = (balance_ + amount);
}

void Bankaccount::withdraw(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  if (amount < static_cast<std::int64_t>(0)) {
    throw std::runtime_error("amount must be non-negative");
  }
  if (balance_ < amount) {
    throw std::runtime_error("insufficient funds");
  }
  balance_ = (balance_ - amount);
}

std::int64_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!is_open_) {
    throw std::runtime_error("account not open");
  }
  return balance_;
}

}  // namespace Bankaccount
