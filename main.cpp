#include <iostream>
#include <string_view>

void print_help() {
    std::cout << "Usage: head [OPTIONS] [FILE]\n"
              << "A high-performance C++23 utility to stream the first lines of a file.\n\n"
              << "Options:\n"
              << "  -h, --help     Display this help message and exit\n"
              << "  -v, --version  Output version information and exit\n";
}

void print_version() {
    std::cout << "head version 1.0.0 (C++23 Clang Build)\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string_view arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            print_help();
            return 0;
        }
        if (arg == "-v" || arg == "--version") {
            print_version();
            return 0;
        }
    }

    // Existing core logic for file streaming goes here...
    std::cout << "head: running utility...\n";
    return 0;
}
