#include "image/image.hpp"
#include "filters/filters.hpp"
#include "interpreter.hpp"
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Missing arguments\n";
        return 1;
    }

    try {
        Interpreter interpreter(argc, argv);
    } catch (const ImageException &exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    } catch (const FilterException &exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    } catch (const InterpreterException &exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    } catch (const std::bad_array_new_length &) {
        std::cerr << "Insufficient memory" << std::endl;
        return 1;
    } catch (const std::length_error &) {
        std::cerr << "Insufficient memory" << std::endl;
        return 1;
    } catch (const std::bad_alloc &) {
        std::cerr << "Insufficient memory" << std::endl;
        return 1;
    }
}
