#include "bank_account.h"

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_is_open(false),
      m_balance(static_cast<amount_t>(0)) {}

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_is_open) {
    throw std::runtime_error("account already open");
  }
  m_is_open = true;
  m_balance = static_cast<amount_t>(0);
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account already closed");
  }
  m_is_open = false;
}

void Bankaccount::deposit(amount_t amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account is closed");
  }
  if (amount < static_cast<amount_t>(0)) {
    throw std::runtime_error("deposit amount must be non-negative");
  }
  m_balance = static_cast<amount_t>((m_balance + amount));
}

void Bankaccount::withdraw(amount_t amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account is closed");
  }
  if (amount < static_cast<amount_t>(0)) {
    throw std::runtime_error("withdraw amount must be non-negative");
  }
  if (m_balance < amount) {
    throw std::runtime_error("insufficient funds");
  }
  m_balance = static_cast<amount_t>((m_balance - amount));
}

amount_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if (!m_is_open) {
    throw std::runtime_error("account is closed");
  }
  return m_balance;
}

}  // namespace Bankaccount
