#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_);
  if (open_) {
    throw std::runtime_error("Account already open");
  }
  open_ = true;
  balance_ = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_);
  if (!open_) {
    throw std::runtime_error("Account already closed");
  }
  open_ = false;
}

int64_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_);
  if (!open_) {
    throw std::runtime_error("Account is closed");
  }
  return balance_;
}

void Bankaccount::deposit(int64_t amount) {
  std::lock_guard<std::mutex> lock(m_);
  if (!open_) {
    throw std::runtime_error("Account is closed");
  }
  if (amount < 0) {
    throw std::runtime_error("Negative deposit");
  }
  balance_ += amount;
}

void Bankaccount::withdraw(int64_t amount) {
  std::lock_guard<std::mutex> lock(m_);
  if (!open_) {
    throw std::runtime_error("Account is closed");
  }
  if (amount < 0) {
    throw std::runtime_error("Negative withdrawal");
  }
  if (balance_ < amount) {
    throw std::runtime_error("Insufficient funds");
  }
  balance_ -= amount;
}

}  // namespace Bankaccount
