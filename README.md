# CppHead

`CppHead` is a high-performance C++23 command-line utility designed as a fast, local-first alternative for streaming file headers. It features an automated Clang-based build and install pipeline, an integrated GoogleTest unit test suite, and performance benchmarking.

## Features

- **Modern C++23**: Written using modern C++ standards and best practices.
- **Clang Optimization**: Configured to build with Clang for optimal performance and strict compilation standards.
- **Automated Workflow**: Streamlined PowerShell automation scripts for building, testing, benchmarking, and deployment.
- **Integrated Testing**: Unit tests powered by GoogleTest via Git submodule.
- **Performance Benchmarking**: Built-in benchmark suite measuring streaming file throughput and latency.

## Project Structure

```text
CppHead/
├── external/
│   └── gtest/            # GoogleTest submodule
├── tests/
│   ├── benchmark.cpp     # Performance benchmarking suite
│   └── cpphead_tests.cpp # GoogleTest unit tests
├── build.ps1             # Automated build, test, and benchmark script
├── install.ps1           # Full build-and-install pipeline (deploys to $HOME/bin)
├── CMakeLists.txt        # CMake configuration
└── main.cpp              # Application entry point

