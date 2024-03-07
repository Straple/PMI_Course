#include "interpreter.hpp"
#include "filters/filters.hpp"
#include <cmath>

InterpreterException::InterpreterException(const std::string &message)
    : std::runtime_error("Interpreter exception: " + message) {
}

UnknownCommandException::UnknownCommandException(const std::string &message)
    : InterpreterException("Unknown command, got \"" + message + "\"") {
}

InvalidCommandFormatException::InvalidCommandFormatException(const std::string &message)
    : InterpreterException("Invalid command format: \"" + message + "\"") {
}

int ReadInt(const std::string &string) {
    try {
        size_t pos = 0;
        const int val = std::stoi(string, &pos);
        if (pos != string.size()) {
            throw std::invalid_argument("isn't int");  // "123a" != 123
        }
        return val;
    } catch (const std::invalid_argument &error) {
        throw InvalidCommandFormatException(string + ", error message: " + error.what());
    } catch (const std::out_of_range &) {
        throw InvalidCommandFormatException(string + ", error message: out of range");
    }
}

double ReadDouble(const std::string &string) {
    try {
        size_t pos = 0;
        const double val = std::stod(string, &pos);
        if (pos != string.size()) {
            throw std::invalid_argument("isn't double");
        }
        if (std::isnan(val) || std::isinf(val)) {
            throw std::invalid_argument("is nan or inf");
        }
        return val;
    } catch (const std::invalid_argument &error) {
        throw InvalidCommandFormatException(string + ", error message: " + error.what());
    } catch (const std::out_of_range &) {
        throw InvalidCommandFormatException(string + ", error message: out of range");
    }
}

int ReadImageSize(const std::string &string) {
    int size = ReadInt(string);
    if (size <= 0) {
        throw InvalidCommandFormatException(string);
    }
    return size;
}

Interpreter::Interpreter(int argc, char **argv) {
    auto get_argv = [&](int index) {
        if (0 <= index && index < argc) {
            return argv[index];
        } else {
            throw InvalidCommandFormatException("not a complete command");
        }
    };

    std::string input_filename = get_argv(1);
    std::string output_filename = get_argv(2);

    Image image;
    image.Read(input_filename);

    for (int index = 3; index < argc; index++) {
        std::string filter_name = get_argv(index);
        if (filter_name == "-crop") {
            int width = ReadImageSize(get_argv(index + 1));
            int height = ReadImageSize(get_argv(index + 2));
            index += 2;

            image = image.Crop(0, 0, height, width);
        } else if (filter_name == "-gs") {
            GrayScaleFilter()(image);
        } else if (filter_name == "-neg") {
            NegativeFilter()(image);
        } else if (filter_name == "-sharp") {
            SharpeningFilter()(image);
        } else if (filter_name == "-edge") {
            std::string threshold_str = get_argv(index + 1);
            index++;

            double threshold = ReadDouble(threshold_str);
            if (!(0 <= threshold && threshold <= 1)) {
                throw InvalidCommandFormatException("threshold is invalid = " + threshold_str);
            }

            EdgeDetectionFilter filter(threshold);
            filter(image);
        } else if (filter_name == "-blur") {
            std::string sigma_str = get_argv(index + 1);
            index++;

            double sigma = ReadDouble(sigma_str);
            if (sigma < 0) {
                throw InvalidCommandFormatException("sigma is invalid = " + sigma_str);
            }

            GaussianBlurFilter filter(sigma);
            filter(image);
        } else if (filter_name == "-my_filter") {
            std::string blur_sigma_str = get_argv(index + 1);
            std::string max_dist_str = get_argv(index + 2);
            std::string max_diff_str = get_argv(index + 3);
            index += 3;

            double blur_sigma = ReadDouble(blur_sigma_str);
            double max_dist = ReadDouble(max_dist_str);
            double max_diff = ReadDouble(max_diff_str);

            if (blur_sigma < 0) {
                throw InvalidCommandFormatException("blur sigma is invalid = " + blur_sigma_str);
            }

            MyFilter filter(blur_sigma, max_dist, max_diff);
            filter(image);
        } else {
            throw UnknownCommandException(filter_name);
        }
    }

    image.Write(output_filename);
}