#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : m_balance(0), m_is_closed(true) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_closed) {
        throw std::runtime_error("Account already open");
    }
    m_is_closed = false;
    m_balance = 0;
}

void Bankaccount::deposit(balance_t amount) {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_is_closed) {
        throw std::runtime_error("Account closed");
    }
    if ((amount <= 0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(balance_t amount) {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_is_closed) {
        throw std::runtime_error("Account closed");
    }
    if ((amount <= 0)) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if ((amount > m_balance)) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance = (m_balance - amount);
}

balance_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_is_closed) {
        throw std::runtime_error("Account closed");
    }
    return m_balance;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_is_closed) {
        throw std::runtime_error("Account already closed");
    }
    m_is_closed = true;
}

}  // namespace Bankaccount
