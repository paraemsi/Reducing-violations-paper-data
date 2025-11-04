#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : opened_(false), bal_(0) {}

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (opened_) {
    throw std::runtime_error("account already open");
  }
  opened_ = true;
  bal_ = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!opened_) {
    throw std::runtime_error("account not open");
  }
  opened_ = false;
  bal_ = 0;
}

void Bankaccount::deposit(int amount) {
  if (amount < 0) {
    throw std::runtime_error("cannot deposit negative amount");
  }
  std::lock_guard<std::mutex> lock(mtx_);
  if (!opened_) {
    throw std::runtime_error("account not open");
  }
  bal_ += amount;
}

void Bankaccount::withdraw(int amount) {
  if (amount < 0) {
    throw std::runtime_error("cannot withdraw negative amount");
  }
  std::lock_guard<std::mutex> lock(mtx_);
  if (!opened_) {
    throw std::runtime_error("account not open");
  }
  if (amount > bal_) {
    throw std::runtime_error("insufficient funds");
  }
  bal_ -= amount;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(mtx_);
  if (!opened_) {
    throw std::runtime_error("account not open");
  }
  return bal_;
}

}  // namespace Bankaccount
