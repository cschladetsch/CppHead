#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

void print_help() {
    std::cout << "Usage: head [OPTION]... [FILE]...\n"
              << "Print the first 10 lines of each FILE to standard output.\n"
              << "With more than one FILE, precede each with a header.\n\n"
              << "Mandatory arguments to long options are mandatory for short options too.\n"
              << "  -c, --bytes=[-]NUM       print the first NUM bytes of each file;\n"
              << "                             with the leading '-', print all but the last\n"
              << "                             NUM bytes of each file (not yet implemented)\n"
              << "  -n, --lines=[+]NUM       print the first NUM lines instead of the first 10;\n"
              << "                             with the leading '-', print all but the last\n"
              << "                             NUM lines of each file\n"
              << "  -NUM                     equivalent to -n NUM\n"
              << "  -h, --help               display this help and exit\n"
              << "  -v, --version            output version information and exit\n\n"
              << "Examples:\n"
              << "  head -n 20 file.txt      Print the first 20 lines of file.txt\n"
              << "  head -50 file.txt        Print the first 50 lines of file.txt\n"
              << "  head file1.txt file2.txt Print files with headers\n";
}

void print_version() {
    std::cout << "head version 1.1.0 (C++23 Build, built " << __DATE__ << " " << __TIME__ << ")\n";
}

void stream_lines(std::istream& in, int max_lines) {
    std::string line;
    int count = 0;
    while (count < max_lines && std::getline(in, line)) {
        std::cout << line << '\n';
        ++count;
    }
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int max_lines = 10;
    std::vector<std::string_view> files;

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            print_help();
            return 0;
        }
        if (arg == "-v" || arg == "--version") {
            print_version();
            return 0;
        }
        if (arg == "-n" || arg == "--lines") {
            if (i + 1 < argc) {
                max_lines = std::stoi(argv[++i]);
            } else {
                std::cerr << "head: option requires an argument -- '" << arg << "'\n";
                return 1;
            }
        } else if (arg.rfind("-n", 0) == 0) {
            max_lines = std::stoi(std::string(arg.substr(2)));
        } else if (arg[0] == '-' && arg.length() > 1 && std::isdigit(arg[1])) {
            max_lines = std::stoi(std::string(arg.substr(1)));
        } else if (arg[0] == '-' && arg != "-") {
            std::cerr << "head: invalid option -- '" << arg << "'\n";
            print_help();
            return 1;
        } else {
            files.push_back(arg);
        }
    }

    if (files.empty() || (files.size() == 1 && files[0] == "-")) {
        stream_lines(std::cin, max_lines);
        return 0;
    }

    bool multiple_files = files.size() > 1;
    for (size_t i = 0; i < files.size(); ++i) {
        std::string_view filepath = files[i];

        if (multiple_files) {
            if (i > 0) std::cout << '\n';
            std::cout << "==> " << filepath << " <==\n";
        }

        std::ifstream file(filepath.data(), std::ios::binary);
        if (!file) {
            std::cerr << "head: cannot open '" << filepath << "' for reading: No such file or directory\n";
            continue;
        }

        stream_lines(file, max_lines);
    }

    return 0;
}
