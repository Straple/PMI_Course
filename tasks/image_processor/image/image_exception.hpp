#pragma once

#include <stdexcept>

struct ImageException : std::runtime_error {
    explicit ImageException(const std::string &message);
};

struct UnableToOpenFileException : ImageException {
    explicit UnableToOpenFileException(const std::string &filename);
};

struct InvalidBmpFormatException : ImageException {
    explicit InvalidBmpFormatException(const std::string &message);
};
