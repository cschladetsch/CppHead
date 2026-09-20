# CppHead

`CppHead` is a high-performance C++23 command-line utility designed to stream the first lines of files with minimal overhead, closely mirroring the classic Unix `head` command. Built with modern C++23 features and compiled via CMake, it delivers blazing-fast I/O throughput.

## Features

* **Unix-Compatible Flag Parsing**: Supports `-n [NUM]`, `--lines=[NUM]`, and classic shorthand like `-NUM`.
* **Standard Input Support**: Reads directly from `stdin` when no file argument is given or when `-` is passed.
* **Multi-File Handling**: Streams multiple files sequentially, complete with standard Unix headers (`==> filename <==`).
* **High Performance**: Optimized with standard I/O decoupling and stream buffering, processing 1,000 lines in under 400 microseconds.
* **Metadata Embedding**: Embeds compile-time versioning and build timestamps.

## Repository Structure

```text
CppHead/
├── CMakeLists.txt        # Main CMake configuration file
├── build.ps1             # PowerShell automation script for building & benchmarking
├── main.cpp              # Entry point and argument parsing logic
├── benchmark.cpp         # Google Benchmark micro-benchmark definitions
├── cpphead_tests.cpp     # Unit tests for verification
├── docs/
│   └── usage.md          # Comprehensive usage guide and examples
└── external/
    └── gtest/            # Google Test framework integration
```

## Prerequisites

* **Compiler**: A modern C++23 compatible compiler (MSVC 2022+ / Visual Studio 18+, GCC 13+, or Clang 16+).
* **Build System**: CMake 3.20 or higher.
* **Shell**: PowerShell (recommended for Windows-based build automation).

## Building & Testing

### Using the Automation Script
The easiest way to build the project, compile all executables, and run the side-by-side performance comparison against PowerShell's `Get-Content` is via the provided script:

```powershell
.\build.ps1
```

### Manual CMake Build
If you prefer to configure and build manually via CMake:

```powershell
# Configure the project
cmake -B build -S .

# Build in Release mode
cmake --build build --config Release
```

### Running Unit Tests
Google Test suites are compiled alongside the utility. Run the test binary directly to verify core logic:

```powershell
.\build\Release\cpphead_tests.exe
```

Alternatively, run tests via CTest:

```powershell
ctest --test-dir build --output-on-failure -C Release
```

## Benchmarking

To measure raw C++ stream performance without process-spawning overhead, execute the dedicated micro-benchmark binary:

```powershell
.\build\Release\cpphead_benchmark.exe
```

## Usage

```bash
head [OPTION]... [FILE]...
```

For full option breakdowns and advanced usage examples, see the [Usage Guide](docs/usage.md).

## License

This project is distributed under the MIT License. Feel free to use, modify, and distribute as needed.