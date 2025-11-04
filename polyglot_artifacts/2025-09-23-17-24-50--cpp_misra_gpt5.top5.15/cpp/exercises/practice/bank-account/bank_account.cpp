#include "bank_account.h"

#include <limits>
#include <stdexcept>

namespace Bankaccount {


void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (is_open_ == true) {
    throw std::runtime_error("Account already open");
  } else {
    is_open_ = true;
    balance_ = static_cast<std::int64_t>(0);
  }
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (is_open_ == false) {
    throw std::runtime_error("Account already closed");
  } else {
    is_open_ = false;
  }
}

void Bankaccount::deposit(std::int64_t amount) {
  if (amount < static_cast<std::int64_t>(0)) {
    throw std::invalid_argument("Negative deposit");
  }
  std::lock_guard<std::mutex> lock(mtx_);
  if (is_open_ == false) {
    throw std::runtime_error("Account is closed");
  }
  if ((amount > static_cast<std::int64_t>(0)) &&
      (balance_ > (std::numeric_limits<std::int64_t>::max() - amount))) {
    throw std::overflow_error("Balance overflow");
  }
  balance_ = balance_ + amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
  if (amount < static_cast<std::int64_t>(0)) {
    throw std::invalid_argument("Negative withdrawal");
  }
  std::lock_guard<std::mutex> lock(mtx_);
  if (is_open_ == false) {
    throw std::runtime_error("Account is closed");
  }
  if (balance_ < amount) {
    throw std::runtime_error("Insufficient funds");
  }
  balance_ = balance_ - amount;
}

std::int64_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mtx_);
  if (is_open_ == false) {
    throw std::runtime_error("Account is closed");
  } else {
    return balance_;
  }
}

}  // namespace Bankaccount
