#include "bank_account.h"

#include <limits>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() {}

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (open_) {
    throw std::runtime_error("account already open");
  }
  open_ = true;
  account_balance_ = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("account is closed");
  }
  open_ = false;
}

void Bankaccount::deposit(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("account is closed");
  }
  if (amount < 0) {
    throw std::runtime_error("cannot deposit negative amount");
  }
  if (account_balance_ > (std::numeric_limits<std::int64_t>::max() - amount)) {
    throw std::runtime_error("deposit would cause overflow");
  }
  account_balance_ += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("account is closed");
  }
  if (amount < 0) {
    throw std::runtime_error("cannot withdraw negative amount");
  }
  if (account_balance_ < amount) {
    throw std::runtime_error("insufficient funds");
  }
  account_balance_ -= amount;
}

std::int64_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mutex_);
  if (!open_) {
    throw std::runtime_error("account is closed");
  }
  return account_balance_;
}

}  // namespace Bankaccount
