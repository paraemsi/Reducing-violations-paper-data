#include "bank_account.h"

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount()
    : m_mutex(),
      m_open(false),
      m_balance(static_cast<Bankaccount::amount_type>(0)) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("Account is already open");
    }
    m_open = true;
    m_balance = static_cast<Bankaccount::amount_type>(0);
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is not open");
    }
    m_open = false;
    m_balance = static_cast<Bankaccount::amount_type>(0);
}

void Bankaccount::deposit(Bankaccount::amount_type amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Cannot deposit to a closed account");
    }
    if (amount < static_cast<Bankaccount::amount_type>(0)) {
        throw std::runtime_error("Deposit amount must be non-negative");
    }
    m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(Bankaccount::amount_type amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Cannot withdraw from a closed account");
    }
    if (amount < static_cast<Bankaccount::amount_type>(0)) {
        throw std::runtime_error("Withdraw amount must be non-negative");
    }
    if (amount > m_balance) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance = (m_balance - amount);
}

Bankaccount::amount_type Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
