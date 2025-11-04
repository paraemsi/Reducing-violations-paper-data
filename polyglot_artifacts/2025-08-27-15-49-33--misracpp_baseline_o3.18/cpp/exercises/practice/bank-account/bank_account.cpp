#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

// Open the account.
void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_open) {
    throw std::runtime_error("account already open");
  }
  m_open = true;
  m_balance = 0;
}

// Close the account.
void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account already closed");
  }
  m_open = false;
  m_balance = 0;
}

// Get current balance.
int Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account closed");
  }
  return m_balance;
}

// Deposit funds.
void Bankaccount::deposit(int amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account closed");
  }
  if (amount < 0) {
    throw std::runtime_error("negative deposit");
  }
  m_balance += amount;
}

// Withdraw funds.
void Bankaccount::withdraw(int amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_open) {
    throw std::runtime_error("account closed");
  }
  if (amount < 0) {
    throw std::runtime_error("negative withdraw");
  }
  if (amount > m_balance) {
    throw std::runtime_error("insufficient funds");
  }
  m_balance -= amount;
}

}  // namespace Bankaccount
