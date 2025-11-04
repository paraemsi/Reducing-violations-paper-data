#include "bank_account.h"
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_is_open) {
    throw std::runtime_error("account already open");
  }
  m_balance = 0;
  m_is_open = true;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account not open");
  }
  m_is_open = false;
}

void Bankaccount::deposit(int amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account not open");
  }
  if (amount < 0) {
    throw std::runtime_error("cannot deposit negative amount");
  }
  m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account not open");
  }
  if (amount < 0) {
    throw std::runtime_error("cannot withdraw negative amount");
  }
  if (amount > m_balance) {
    throw std::runtime_error("insufficient funds");
  }
  m_balance -= amount;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account not open");
  }
  return m_balance;
}

}  // namespace Bankaccount
