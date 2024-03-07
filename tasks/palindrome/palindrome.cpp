#include "palindrome.h"

bool IsPalindrome(const std::string &str) {
    std::size_t left = 0;
    std::size_t right = str.size();
    auto next_no_spaces = [&]() {
        while (left < str.size() && str[left] == ' ') {
            left++;
        }
        while (right > 0 && str[right - 1] == ' ') {
            right--;
        }
        return left + 1 < right;
    };
    for (; next_no_spaces() && str[left] == str[right - 1]; left++, right--) {
    }
    return left + 1 >= right;
}