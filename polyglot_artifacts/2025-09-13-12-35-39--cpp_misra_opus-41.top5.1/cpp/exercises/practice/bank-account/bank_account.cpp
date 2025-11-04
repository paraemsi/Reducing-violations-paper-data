#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : account_balance(0), is_open(false) {
}

Bankaccount::~Bankaccount() {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (is_open) {
        throw std::runtime_error("Account already open");
    }
    is_open = true;
    account_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account already closed");
    }
    is_open = false;
}

void Bankaccount::deposit(std::int32_t amount) {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot deposit negative amount");
    }
    account_balance = account_balance + amount;
}

void Bankaccount::withdraw(std::int32_t amount) {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot withdraw negative amount");
    }
    if (amount > account_balance) {
        throw std::runtime_error("Insufficient funds");
    }
    account_balance = account_balance - amount;
}

std::int32_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account is closed");
    }
    return account_balance;
}

}  // namespace Bankaccount
