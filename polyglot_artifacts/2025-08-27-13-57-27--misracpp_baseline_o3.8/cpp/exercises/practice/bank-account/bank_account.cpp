#include "bank_account.h"
#include <stdexcept>
#include <mutex>

namespace Bankaccount {

Bankaccount::Bankaccount() = default;

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_open) {
    throw std::runtime_error("Account already open");
  }
  m_open   = true;
  m_balance = 0;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account already closed");
  }
  m_open   = false;
  m_balance = 0;
}

void Bankaccount::deposit(int amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account is closed");
  }
  if (amount < 0) {
    throw std::runtime_error("Negative deposit not allowed");
  }
  m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account is closed");
  }
  if (amount < 0) {
    throw std::runtime_error("Negative withdrawal not allowed");
  }
  if (amount > m_balance) {
    throw std::runtime_error("Insufficient funds");
  }
  m_balance -= amount;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("Account is closed");
  }
  return m_balance;
}

}  // namespace Bankaccount
