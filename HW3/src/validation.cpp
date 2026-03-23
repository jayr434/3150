#include "../include/validation.h"
#include <cctype>

bool is_valid_password(std::string password) {
    if (password.length() < 8) {
        return false;
    }

    bool has_upper = false;
    bool has_non_alnum = false;

    for (char c : password) {
        if (std::isupper(c)) {
            has_upper = true;
        }
        if (!std::isalnum(c)) {
            has_non_alnum = true;
        }
    }

    return has_upper && has_non_alnum;
}
