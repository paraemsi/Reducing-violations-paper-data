#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() = default;

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_open) {
    throw std::runtime_error("Account already open");
  }
  m_open = true;
  m_balance = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account already closed");
  }
  m_open = false;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account closed");
  }
  return m_balance;
}

void Bankaccount::deposit(int amount) {
  if (amount < 0) {
    throw std::invalid_argument("Cannot deposit negative amount");
  }
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account closed");
  }
  m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
  if (amount < 0) {
    throw std::invalid_argument("Cannot withdraw negative amount");
  }
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account closed");
  }
  if (m_balance < amount) {
    throw std::runtime_error("Insufficient funds");
  }
  m_balance -= amount;
}

}  // namespace Bankaccount
