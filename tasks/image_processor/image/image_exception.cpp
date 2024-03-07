
#include "image_exception.hpp"

ImageException::ImageException(const std::string &message) : std::runtime_error(message) {
}

UnableToOpenFileException::UnableToOpenFileException(const std::string &filename)
    : ImageException("Unable to open file \"" + filename + "\"") {
}

InvalidBmpFormatException::InvalidBmpFormatException(const std::string &message) : ImageException(message) {
}