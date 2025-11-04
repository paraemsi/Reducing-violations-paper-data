#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance_(0), is_open_(false) {}

void Bankaccount::open() {
    // Atomically check and set is_open_ to true
    if (__sync_lock_test_and_set(&is_open_, true)) {
        throw std::runtime_error("Account is already open");
    }
    // Reset balance to 0
    __sync_lock_test_and_set(&balance_, 0);
}

void Bankaccount::close() {
    // Atomically check and set is_open_ to false
    if (!__sync_lock_test_and_set(&is_open_, false)) {
        // If it was already false, set it back to false and throw
        __sync_lock_test_and_set(&is_open_, false);
        throw std::runtime_error("Account is not open");
    }
}

int Bankaccount::balance() const {
    // Read is_open_ atomically
    if (!__sync_fetch_and_add(&is_open_, 0)) {
        throw std::runtime_error("Account is closed");
    }
    // Read balance_ atomically
    return __sync_fetch_and_add(&balance_, 0);
}

void Bankaccount::deposit(int amount) {
    // Check if account is open atomically
    if (!__sync_fetch_and_add(&is_open_, 0)) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Cannot deposit non-positive amount");
    }
    __sync_fetch_and_add(&balance_, amount);
}

void Bankaccount::withdraw(int amount) {
    // Check if account is open atomically
    if (!__sync_fetch_and_add(&is_open_, 0)) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Cannot withdraw non-positive amount");
    }
    // Use a loop to atomically check and update balance
    int old_balance;
    int new_balance;
    do {
        old_balance = __sync_fetch_and_add(&balance_, 0);
        if (old_balance < amount) {
            throw std::runtime_error("Insufficient funds");
        }
        new_balance = old_balance - amount;
    } while (!__sync_bool_compare_and_swap(&balance_, old_balance, new_balance));
}

}  // namespace Bankaccount
