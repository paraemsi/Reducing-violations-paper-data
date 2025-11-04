#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : bal(0), is_open(false) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open) {
        throw std::runtime_error("Account is already open");
    }
    is_open = true;
    bal = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is not open");
    }
    is_open = false;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    bal += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if (amount > bal) {
        throw std::runtime_error("Insufficient funds");
    }
    bal -= amount;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    return bal;
}

}  // namespace Bankaccount
