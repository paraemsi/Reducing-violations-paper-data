#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : m_balance(0), m_is_open(false) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    }
    m_is_open = true;
    m_balance = 0;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid deposit amount");
    }
    m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid withdrawal amount");
    }
    if ((amount > m_balance)) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance = (m_balance - amount);
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    m_is_open = false;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
