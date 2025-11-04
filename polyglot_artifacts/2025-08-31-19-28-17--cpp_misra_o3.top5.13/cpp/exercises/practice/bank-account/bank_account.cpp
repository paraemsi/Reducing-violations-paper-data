#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex_);
    if (m_is_open_) {
        throw std::runtime_error("Account already open");
    } else {
        m_balance_ = static_cast<std::int32_t>(0);
        m_is_open_ = true;
    }
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex_);
    if (!m_is_open_) {
        throw std::runtime_error("Account already closed");
    } else {
        m_is_open_ = false;
    }
}

void Bankaccount::deposit(std::int32_t amount) {
    if (amount < static_cast<std::int32_t>(0)) {
        throw std::runtime_error("Deposit amount must be non-negative");
    }
    std::lock_guard<std::mutex> lock(m_mutex_);
    ensure_open();
    m_balance_ += amount;
}

void Bankaccount::withdraw(std::int32_t amount) {
    if (amount < static_cast<std::int32_t>(0)) {
        throw std::runtime_error("Withdraw amount must be non-negative");
    }
    std::lock_guard<std::mutex> lock(m_mutex_);
    ensure_open();
    if (m_balance_ < amount) {
        throw std::runtime_error("Insufficient funds");
    } else {
        m_balance_ -= amount;
    }
}

std::int32_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex_);
    ensure_open();
    return m_balance_;
}

void Bankaccount::ensure_open() const {
    if (!m_is_open_) {
        throw std::runtime_error("Account is closed");
    }
}

}  // namespace Bankaccount
