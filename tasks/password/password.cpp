#include "password.h"

// val ∈ [min, max]
template <typename T>
bool IsBetween(const T& val, const T& min, const T& max) {
    return std::clamp(val, min, max) == val;
}

bool ValidatePassword(const std::string& password) {
    static const std::size_t MIN_PASSWORD_SIZE = 8;
    static const std::size_t MAX_PASSWORD_SIZE = 14;

    if (!IsBetween(password.size(), MIN_PASSWORD_SIZE, MAX_PASSWORD_SIZE)) {
        return false;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_other = false;
    for (char symbol : password) {
        static const char MIN_ASCII_SYMBOL = 33;
        static const char MAX_ASCII_SYMBOL = 126;
        if (!IsBetween(symbol, MIN_ASCII_SYMBOL, MAX_ASCII_SYMBOL)) {
            return false;
        }
        if (std::isupper(symbol)) {
            has_upper = true;
        } else if (std::islower(symbol)) {
            has_lower = true;
        } else if (std::isdigit(symbol)) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }
    return has_upper + has_lower + has_digit + has_other >= 3;
}
