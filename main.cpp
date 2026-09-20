#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <print>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;

void print_head(std::istream& in, size_t n, const std::string& label = "") {
    if (!label.empty()) {
        std::println("==> {} <==", label);
    }
    
    std::string line;
    size_t count = 0;
    while (count < n && std::getline(in, line)) {
        std::println("{}", line);
        ++count;
    }
}

int main(int argc, char* argv[]) {
    // Fast I/O sync decoupling
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t num_lines = 10;
    std::vector<fs::path> files;

    // Lightweight argument parsing for -n [lines] and files
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-n" && i + 1 < argc) {
            try {
                num_lines = std::stoul(argv[++i]);
            } catch (const std::exception&) {
                std::println(stderr, "head: invalid line count: {}", argv[i]);
                return 1;
            }
        } else if (arg.starts_with("-n") && arg.length() > 2) {
            try {
                num_lines = std::stoul(arg.substr(2));
            } catch (const std::exception&) {
                std::println(stderr, "head: invalid line count: {}", arg);
                return 1;
            }
        } else if (!arg.starts_with("-")) {
            files.push_back(argv[i]);
        }
    }

    // Process standard input if no files are supplied
    if (files.empty()) {
        print_head(std::cin, num_lines);
        return 0;
    }

    // Process one or more files with standard formatting headers if multiple
    bool multiple = files.size() > 1;
    for (size_t i = 0; i < files.size(); ++i) {
        if (multiple && i > 0) {
            std::println("");
        }

        std::ifstream file(files[i], std::ios::in);
        if (!file) {
            std::println(stderr, "head: cannot open '{}' for reading", files[i].string());
            continue;
        }

        print_head(file, num_lines, multiple ? files[i].string() : "");
    }

    return 0;
}

