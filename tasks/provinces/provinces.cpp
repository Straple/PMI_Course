#include "provinces.h"
#include <queue>

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t result = 0;
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> provinces_set;
    for (int people_count : provinces) {
        provinces_set.push(people_count);
    }
    while (provinces_set.size() > 1) {
        int64_t first = provinces_set.top();
        provinces_set.pop();
        int64_t second = provinces_set.top();
        provinces_set.pop();
        int64_t new_provinces = first + second;
        result += new_provinces;
        provinces_set.push(new_provinces);
    }
    return result;
}
