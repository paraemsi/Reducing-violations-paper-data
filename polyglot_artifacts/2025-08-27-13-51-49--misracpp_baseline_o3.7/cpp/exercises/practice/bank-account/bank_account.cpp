#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_open) {
    throw std::runtime_error("account already open");
  }
  m_balance = 0;
  m_open = true;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account already closed");
  }
  m_open = false;
}

int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account closed");
  }
  return m_balance;
}

void Bankaccount::deposit(int amount) {
  if (amount < 0) {
    throw std::runtime_error("negative deposit");
  }
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account closed");
  }
  m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
  if (amount < 0) {
    throw std::runtime_error("negative withdrawal");
  }
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account closed");
  }
  if (m_balance < amount) {
    throw std::runtime_error("insufficient funds");
  }
  m_balance -= amount;
}

}  // namespace Bankaccount
