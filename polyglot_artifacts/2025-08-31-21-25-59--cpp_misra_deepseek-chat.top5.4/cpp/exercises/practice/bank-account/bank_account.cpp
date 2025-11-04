#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : m_balance(static_cast<BalanceType>(0)), m_is_open(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    }
    m_is_open = true;
    m_balance = static_cast<BalanceType>(0);
}

void Bankaccount::deposit(BalanceType amount) {
    if ((amount <= static_cast<BalanceType>(0))) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(BalanceType amount) {
    if ((amount <= static_cast<BalanceType>(0))) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    if ((amount > m_balance)) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

BalanceType Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    return m_balance;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    m_is_open = false;
}

}  // namespace Bankaccount
