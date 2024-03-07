#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string result;
    if (!path.empty() && path[0] == '/') {
        // path is absolute
    } else {
        result = {current_working_dir.begin(), current_working_dir.end()};
    }
    for (auto symbol : path) {
        if (!result.empty() && result.back() == '.' && symbol != '.') {
            result.pop_back();  // remove one '.'
        }

        // compress '//' -> '/'
        if (!result.empty() && result.back() == '/' && symbol == '/') {
            result.pop_back();
        }

        // ".." -> go to parent directory
        if (!result.empty() && result.back() == '.' && symbol == '.') {
            result.pop_back();  // remove '.'
            if (result.size() != 1) {
                result.pop_back();  // remove '/'
                while (!result.empty() && result.back() != '/') {
                    result.pop_back();
                }
            }
            continue;
        }

        result += symbol;
    }
    // remove "/." in the end
    if (!result.empty() && result.back() == '.') {
        result.pop_back();
    }
    if (result.size() >= 2 && result.back() == '/') {
        result.pop_back();
    }
    return result;
}
