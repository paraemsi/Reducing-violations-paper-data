#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : current_balance(0), is_open(false) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open) {
        throw std::runtime_error("Account already open");
    }
    is_open = true;
    current_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account not open");
    }
    is_open = false;
}

void Bankaccount::deposit(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid deposit amount");
    }
    current_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Invalid withdrawal amount");
    }
    if (amount > current_balance) {
        throw std::runtime_error("Insufficient balance");
    }
    current_balance -= amount;
}

std::int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account closed");
    }
    return current_balance;
}

}  // namespace Bankaccount
