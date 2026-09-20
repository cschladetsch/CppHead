#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void run_benchmark(const fs::path& test_file, size_t line_limit) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream file(test_file);
    if (!file.is_open()) {
        std::cerr << "Failed to open benchmark file: " << test_file << "\n";
        return;
    }

    std::string line;
    size_t count = 0;
    while (count < line_limit && std::getline(file, line)) {
        ++count;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << "[Benchmark] Read " << count << " lines in " << duration << " microseconds.\n";
}

int main(int argc, char* argv[]) {
    fs::path temp_file = "benchmark_temp.txt";
    
    // Generate a temporary file with 50,000 lines for benchmarking
    {
        std::ofstream out(temp_file);
        for (int i = 0; i < 50000; ++i) {
            out << "This is benchmark line number " << i << "\n";
        }
    }

    std::cout << "Running C++ Head Benchmark...\n";
    run_benchmark(temp_file, 10);
    run_benchmark(temp_file, 1000);

    // Cleanup
    fs::remove(temp_file);
    return 0;
}
