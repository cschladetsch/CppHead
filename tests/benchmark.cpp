#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

// Simple benchmark routine
void run_benchmark() {
    std::cout << "========================================\n";
    std::cout << "    CppHead Performance Benchmark       \n";
    std::cout << "========================================\n";

    // Create a temporary test file with known data
    const std::string test_filename = "benchmark_temp.txt";
    {
        std::ofstream outfile(test_filename);
        for (int i = 1; i <= 10000; ++i) {
            outfile << "This is benchmark line number " << i << "\n";
        }
    }

    // Benchmark 1: Streaming first 10 lines
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::ifstream file(test_filename);
        std::string line;
        int count = 0;
        while (std::getline(file, line) && count < 10) {
            ++count;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        std::cout << "[Benchmark] Stream first 10 lines:   " << duration << " µs\n";
    }

    // Benchmark 2: Streaming first 1,000 lines
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::ifstream file(test_filename);
        std::string line;
        int count = 0;
        while (std::getline(file, line) && count < 1000) {
            ++count;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        std::cout << "[Benchmark] Stream first 1,000 lines: " << duration << " µs\n";
    }

    // Cleanup temporary file
    std::remove(test_filename.c_str());
    std::cout << "========================================\n";
}

int main() {
    run_benchmark();
    return 0;
}
