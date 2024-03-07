#pragma once

#include <stdexcept>

struct InterpreterException : std::runtime_error {
    explicit InterpreterException(const std::string &message);
};

struct UnknownCommandException : InterpreterException {
    explicit UnknownCommandException(const std::string &message);
};

struct InvalidCommandFormatException : InterpreterException {
    explicit InvalidCommandFormatException(const std::string &message);
};

class Interpreter {
public:
    Interpreter(int argc, char **argv);
};